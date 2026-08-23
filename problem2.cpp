#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;


// ============================================================
// NODE CLASS
// ============================================================

class Node {
public:
    string name;
    int year;

    Node* parent;

    // set keeps children sorted alphabetically
    set<Node*> children;

    Node(string n, int y) {
        name = n;
        year = y;
        parent = nullptr;
    }
};


// ============================================================
// PHD TREE CLASS
// ============================================================

class PhDTree {

private:

    Node* root;

    // Find a node recursively
    Node* findNode(Node* current, const string& name) const {

        if (current == nullptr)
            return nullptr;

        if (current->name == name)
            return current;

        for (Node* child : current->children) {

            Node* result = findNode(child, name);

            if (result != nullptr)
                return result;
        }

        return nullptr;
    }


    // Delete entire subtree
    void deleteTree(Node* node) {

        if (node == nullptr)
            return;

        for (Node* child : node->children) {
            deleteTree(child);
        }

        delete node;
    }


    // Count nodes in subtree
    int size(Node* node) const {

        if (node == nullptr)
            return 0;

        int count = 1;

        for (Node* child : node->children) {
            count += size(child);
        }

        return count;
    }


    // Count leaves
    int numLeaves(Node* node) const {

        if (node == nullptr)
            return 0;

        // If no children, this is a leaf
        if (node->children.empty())
            return 1;

        int count = 0;

        for (Node* child : node->children) {
            count += numLeaves(child);
        }

        return count;
    }


    // Preorder traversal
    void preorder(Node* node) const {

        if (node == nullptr)
            return;

        cout << node->name
             << " (" << node->year << ")"
             << endl;

        for (Node* child : node->children) {
            preorder(child);
        }
    }


    // Find professor with maximum number of direct advisees
    void findProlificMentor(Node* node,
                            Node*& best,
                            int& maxChildren) const {

        if (node == nullptr)
            return;

        int numberOfChildren = node->children.size();

        if (numberOfChildren > maxChildren) {
            maxChildren = numberOfChildren;
            best = node;
        }

        for (Node* child : node->children) {
            findProlificMentor(child, best, maxChildren);
        }
    }


    // Find lineage from root to node
    void buildLineage(Node* node,
                      vector<Node*>& lineage) const {

        if (node == nullptr)
            return;

        buildLineage(node->parent, lineage);

        lineage.push_back(node);
    }


public:

    // Constructor
    PhDTree() {
        root = nullptr;
    }


    // Destructor
    ~PhDTree() {
        deleteTree(root);
    }


    // ========================================================
    // ADD PROFESSOR
    // ========================================================

    void addProfessor(string name,
                      int year,
                      string advisor) {

        // If tree is empty, first professor becomes root
        if (root == nullptr) {

            root = new Node(name, year);

            cout << "Root professor added: "
                 << name << endl;

            return;
        }


        // Check if professor already exists
        if (contains(name)) {

            cout << "Professor already exists.\n";

            return;
        }


        // Find advisor
        Node* advisorNode = findNode(root, advisor);

        if (advisorNode == nullptr) {

            cout << "Advisor not found: "
                 << advisor << endl;

            return;
        }


        // Create new professor
        Node* newNode = new Node(name, year);

        newNode->parent = advisorNode;

        advisorNode->children.insert(newNode);

        cout << "Professor added successfully.\n";
    }


    // ========================================================
    // CONTAINS
    // ========================================================

    bool contains(const string& name) const {

        return findNode(root, name) != nullptr;
    }


    // ========================================================
    // SIZE
    // ========================================================

    int size() const {

        return size(root);
    }


    int size(const string& name) const {

        Node* node = findNode(root, name);

        if (node == nullptr)
            return 0;

        return size(node);
    }


    // ========================================================
    // FIND ADVISOR
    // ========================================================

    string findAdvisor(const string& name) const {

        Node* node = findNode(root, name);

        if (node == nullptr) {

            return "Professor not found.";
        }

        if (node->parent == nullptr) {

            return name + " is the root and has no advisor in the tree.";
        }

        return node->parent->name;
    }


    // ========================================================
    // NUMBER OF LEAVES
    // ========================================================

    int numLeaves() const {

        return numLeaves(root);
    }


    int numLeaves(const string& name) const {

        Node* node = findNode(root, name);

        if (node == nullptr)
            return 0;

        return numLeaves(node);
    }


    // ========================================================
    // FIND PROLIFIC MENTOR
    // ========================================================

    string findProlificMentor() const {

        if (root == nullptr)
            return "Tree is empty.";

        Node* best = root;

        int maxChildren = root->children.size();

        findProlificMentor(root, best, maxChildren);

        return best->name;
    }


    // ========================================================
    // FIND ACADEMIC LINEAGE
    // ========================================================

    void findAcademicLineage(const string& name) const {

        Node* node = findNode(root, name);

        if (node == nullptr) {

            cout << "Professor not found.\n";
            return;
        }


        vector<Node*> lineage;

        buildLineage(node, lineage);


        cout << "\nAcademic Lineage:\n";

        for (int i = 0; i < lineage.size(); i++) {

            cout << lineage[i]->name
                 << " (" << lineage[i]->year << ")";

            if (i != lineage.size() - 1)
                cout << " -> ";

        }

        cout << endl;
    }


    // ========================================================
    // COMMON ANCESTOR
    // ========================================================

    string commonAncestor(const string& name1,
                          const string& name2) const {

        Node* node1 = findNode(root, name1);
        Node* node2 = findNode(root, name2);


        if (node1 == nullptr || node2 == nullptr) {

            return "One or both professors not found.";
        }


        vector<Node*> lineage1;
        vector<Node*> lineage2;


        buildLineage(node1, lineage1);
        buildLineage(node2, lineage2);


        Node* common = nullptr;


        int n = min(lineage1.size(), lineage2.size());


        for (int i = 0; i < n; i++) {

            if (lineage1[i] == lineage2[i]) {

                common = lineage1[i];
            }
            else {

                break;
            }
        }


        if (common == nullptr)
            return "No common ancestor found.";

        return common->name;
    }


    // ========================================================
    // DISPLAY TREE
    // ========================================================

    void display() const {

        if (root == nullptr) {

            cout << "Tree is empty.\n";
            return;
        }

        cout << "\n========== PHD GENEALOGY TREE ==========\n";

        preorder(root);

        cout << "=========================================\n";
    }


    // ========================================================
    // DISPLAY TREE WITH RELATIONSHIPS
    // ========================================================

    void displayDetailed(Node* node, int level) const {

        if (node == nullptr)
            return;


        for (int i = 0; i < level; i++)
            cout << "    ";


        cout << node->name
             << " (" << node->year << ")";


        if (node->parent != nullptr) {

            cout << " [Advisor: "
                 << node->parent->name
                 << "]";
        }

        cout << endl;


        for (Node* child : node->children) {

            displayDetailed(child, level + 1);
        }
    }


    void displayDetailed() const {

        if (root == nullptr) {

            cout << "Tree is empty.\n";
            return;
        }

        cout << "\n========== GENEALOGY TREE ==========\n";

        displayDetailed(root, 0);

        cout << "=====================================\n";
    }
};


// ============================================================
// LOAD DATA FROM CSV
// ============================================================

void loadCSV(PhDTree& tree, string filename) {

    ifstream file(filename);

    if (!file.is_open()) {

        cout << "Unable to open file: "
             << filename << endl;

        return;
    }


    string line;

    // Skip header
    getline(file, line);


    while (getline(file, line)) {

        if (line.empty())
            continue;


        stringstream ss(line);

        string name;
        string yearString;
        string advisor;


        getline(ss, name, ',');
        getline(ss, yearString, ',');
        getline(ss, advisor, ',');


        // Remove possible spaces
        if (!name.empty() && name[0] == ' ')
            name.erase(0, 1);

        if (!advisor.empty() && advisor[0] == ' ')
            advisor.erase(0, 1);


        int year = stoi(yearString);


        tree.addProfessor(name, year, advisor);
    }


    file.close();


    cout << "\nCSV file loaded successfully.\n";
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {

    PhDTree tree;

    int choice;

    string name;
    string name1;
    string name2;
    string filename;
    int year;


    do {

        cout << "\n\n";
        cout << "============================================\n";
        cout << "        PhD GENEALOGY TREE MENU\n";
        cout << "============================================\n";

        cout << "1. Load tree from CSV file\n";
        cout << "2. Add professor\n";
        cout << "3. Check if professor exists (contains)\n";
        cout << "4. Find size of tree/subtree\n";
        cout << "5. Find advisor\n";
        cout << "6. Count leaves\n";
        cout << "7. Find prolific mentor\n";
        cout << "8. Find academic lineage\n";
        cout << "9. Find common ancestor\n";
        cout << "10. Display tree (Preorder)\n";
        cout << "11. Display detailed tree\n";
        cout << "12. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();


        switch (choice) {


            // ------------------------------------------------
            // LOAD CSV
            // ------------------------------------------------

            case 1:

                cout << "Enter CSV filename: ";

                getline(cin, filename);

                loadCSV(tree, filename);

                break;


            // ------------------------------------------------
            // ADD PROFESSOR
            // ------------------------------------------------

            case 2:

                cout << "Enter professor name: ";

                getline(cin, name);

                cout << "Enter PhD year: ";

                cin >> year;

                cin.ignore();


                cout << "Enter advisor name: ";

                getline(cin, name1);


                tree.addProfessor(name, year, name1);

                break;


            // ------------------------------------------------
            // CONTAINS
            // ------------------------------------------------

            case 3:

                cout << "Enter professor name: ";

                getline(cin, name);


                if (tree.contains(name)) {

                    cout << name
                         << " is contained in the tree.\n";
                }
                else {

                    cout << name
                         << " is not contained in the tree.\n";
                }

                break;


            // ------------------------------------------------
            // SIZE
            // ------------------------------------------------

            case 4:

                cout << "Enter professor name "
                        "(enter ROOT for complete tree): ";

                getline(cin, name);


                if (name == "ROOT") {

                    cout << "Total professors: "
                         << tree.size()
                         << endl;
                }
                else {

                    cout << "Subtree size: "
                         << tree.size(name)
                         << endl;
                }

                break;


            // ------------------------------------------------
            // FIND ADVISOR
            // ------------------------------------------------

            case 5:

                cout << "Enter professor name: ";

                getline(cin, name);


                cout << "Advisor: "
                     << tree.findAdvisor(name)
                     << endl;

                break;


            // ------------------------------------------------
            // NUMBER OF LEAVES
            // ------------------------------------------------

            case 6:

                cout << "Enter professor name "
                        "(enter ROOT for complete tree): ";

                getline(cin, name);


                if (name == "ROOT") {

                    cout << "Number of leaves: "
                         << tree.numLeaves()
                         << endl;
                }
                else {

                    cout << "Number of leaves in subtree: "
                         << tree.numLeaves(name)
                         << endl;
                }

                break;


            // ------------------------------------------------
            // PROLIFIC MENTOR
            // ------------------------------------------------

            case 7:

                cout << "Most prolific mentor: "
                     << tree.findProlificMentor()
                     << endl;

                break;


            // ------------------------------------------------
            // ACADEMIC LINEAGE
            // ------------------------------------------------

            case 8:

                cout << "Enter professor name: ";

                getline(cin, name);


                tree.findAcademicLineage(name);

                break;


            // ------------------------------------------------
            // COMMON ANCESTOR
            // ------------------------------------------------

            case 9:

                cout << "Enter first professor: ";

                getline(cin, name1);


                cout << "Enter second professor: ";

                getline(cin, name2);


                cout << "Most recent common academic ancestor: "
                     << tree.commonAncestor(name1, name2)
                     << endl;

                break;


            // ------------------------------------------------
            // PREORDER DISPLAY
            // ------------------------------------------------

            case 10:

                tree.display();

                break;


            // ------------------------------------------------
            // DETAILED DISPLAY
            // ------------------------------------------------

            case 11:

                tree.displayDetailed();

                break;


            // ------------------------------------------------
            // EXIT
            // ------------------------------------------------

            case 12:

                cout << "Exiting program...\n";

                break;


            default:

                cout << "Invalid choice! Try again.\n";
        }


    } while (choice != 12);


    return 0;
}