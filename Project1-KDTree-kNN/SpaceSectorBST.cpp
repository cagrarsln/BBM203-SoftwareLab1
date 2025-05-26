#include "SpaceSectorBST.h"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
    freeMemory(root);
}

void SpaceSectorBST::freeMemory(Sector* node) {
    if (node != nullptr) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }

}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        bool isFirstLine = true;
        while (getline(file, line)) {
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }

            stringstream ss(line);
            string data;
            int x, y, z;

            if (getline(ss, data, ',')){
                x = stoi(data);
            }
            if (getline(ss, data, ',')){
                y = stoi(data);
            }
            if (getline(ss, data, ',')){
                z = stoi(data);
            }
            insertSectorByCoordinates(x, y, z);
        }
        file.close();
    }
    else {
        std::cout << "File is not open!" << std::endl;
    }
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
    root = helper(root, x, y, z);
    addPointers(root, nullptr);
}

Sector* SpaceSectorBST::helper(Sector* node, int x, int y, int z) {
    if (node == nullptr) {
        return new Sector(x, y, z);
    }
    if (node->x > x) {
        node->left = helper(node->left, x, y, z);
    }
    else if (node->x < x) {
        node->right = helper(node->right, x, y, z);
    }
    else if (node->y > y) {
        node->left = helper(node->left, x, y, z);
    }
    else if (node->y < y) {
        node->right = helper(node->right, x, y, z);
    }
    else if (node->z > z) {
        node->left = helper(node->left, x, y, z);
    }
    else if (node->z < z) {
        node->right = helper(node->right, x, y, z);
    }
    return node;

}

void SpaceSectorBST::addPointers(Sector* node, Sector* parent) {
    if (node == nullptr) {
        return;
    }
    node->parent = parent;
    addPointers(node->left, node);
    addPointers(node->right, node);
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    Sector* target = findSector(root, sector_code);
    if (target != nullptr) {
        root = deleteNode(root, sector_code);
    }
    else {
        cout << "Sector not found!" << endl;
    }
}

bool SpaceSectorBST::isGreater(Sector* current, Sector* target){
    if (current->x > target->x){
        return true;
    }
    else if (current->x == target->x){
        if (current->y > target->y){
            return true;
        }
        else if (current->y == target->y){
            if (current->z > target->z){
                return true;
            }
        }
    }
    return false;
}

Sector* SpaceSectorBST::deleteNode(Sector* root, const std::string& sector_code)
{
    if (root == nullptr)
        return root;


    if (isGreater(root, findSector(root, sector_code))) {
        root->left = deleteNode(root->left, sector_code);
        return root;
    }
    else if (isGreater(findSector(root, sector_code), root)) {
        root->right = deleteNode(root->right, sector_code);
        return root;
    }




    if (root->left == NULL) {
        Sector* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Sector* temp = root->left;
        delete root;
        return temp;
    }

    else {

        Sector* succParent = root;

        Sector* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        root->sector_code = succ->sector_code;

        delete succ;
        return root;
    }
}


void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors
    // to STDOUT in the given format.
    cout << "Space sectors inorder traversal:" << endl;
    inOrderTraversal(root);
    cout << endl;
}

void SpaceSectorBST::inOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left);
    cout << node->sector_code << endl;
    inOrderTraversal(node->right);
}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors preorder traversal:" << endl;
    preOrderTraversal(root);
    cout << endl;
}

void SpaceSectorBST::preOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->sector_code << endl;
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void SpaceSectorBST::displaySectorsPostOrder() {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    postOrderTraversal(root);
    cout << endl;

}

void SpaceSectorBST::postOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->sector_code << endl;
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    // TODO: Find the path from the Earth to the destination sector given by its

    std::vector<Sector*> path;
    Sector* start = root;
    Sector* target = findSector(root, sector_code);
    if (start != nullptr && target != nullptr) {
        findPath(start, target, path);
    }
    return path;
}
Sector* SpaceSectorBST::findSector(Sector* node, const std::string& sector_code) {
    if (node == nullptr || node->sector_code == sector_code) {
        return node;
    }

    Sector* left = findSector(node->left, sector_code);
    if (left != nullptr) {
        return left;
    }

    return findSector(node->right, sector_code);
}

bool SpaceSectorBST::findPath(Sector* current, Sector* target, std::vector<Sector*>& path) {
    if (current == nullptr) {
        return false;
    }

    path.push_back(current);

    if (current == target) {
        return true;
    }

    if ((current->left != nullptr && findPath(current->left, target, path)) ||
        (current->right != nullptr && findPath(current->right, target, path))) {
        return true;
    }

    path.pop_back();
    return false;
}



void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
    if (path.empty()) {
        std::cout << "A path to Dr. Elara could not be found." << std::endl;
        return;
    }

    std::cout << "The stellar path to Dr. Elara: ";

    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->sector_code;
        if (i != path.size() - 1) {
            std::cout << "->";
        }
    }

    std::cout << std::endl;
}