#include "SpaceSectorLLRBT.h"
#include <cassert>
#include <algorithm>

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
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

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.
    freeMemory(root);
}
void SpaceSectorLLRBT::freeMemory(Sector* node) {
    if (node != nullptr) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }

}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    root = helper(root, nullptr, x, y, z);
    if (root != nullptr) {
        root->color = BLACK;
    }
}

Sector* SpaceSectorLLRBT::helper(Sector* node, Sector* parent, int x, int y, int z) {
    if (node == nullptr) {
        Sector* newNode = new Sector(x, y, z);
        newNode->parent = parent;
        newNode->color = RED;
        return newNode;
    }

    if (node == nullptr) {
        return new Sector(x, y, z);
    }
    if (node->x > x) {
        node->left = helper(node->left, node, x, y, z);
    }
    else if (node->x < x) {
        node->right = helper(node->right, node, x, y, z);
    }
    else if (node->y > y) {
        node->left = helper(node->left, node, x, y, z);
    }
    else if (node->y < y) {
        node->right = helper(node->right, node, x, y, z);
    }
    else if (node->z > z) {
        node->left = helper(node->left, node, x, y, z);
    }
    else if (node->z < z) {
        node->right = helper(node->right, node, x, y, z);
    }

    if (isRed(node->right) && !isRed(node->left)) {
        node = rotateLeft(node);
    }
    if (isRed(node->left) && isRed(node->left->left)) {
        node = rotateRight(node);
    }
    if (isRed(node->left) && isRed(node->right)) {
        flipColors(node);
    }

    return node;
}

bool SpaceSectorLLRBT::isRed(Sector* x) {
    if (x == nullptr) {
        return false;
    }
    return x->color == RED;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* node) {
    assert(isRed(node->right));
    Sector* x = node->right;
    x->parent = node->parent;
    node->parent = x;
    if (x->left != nullptr) {
        x->left->parent = node;
    }
    node->right = x->left;

    x->left = node;

    x->color = node->color;
    node->color = RED;
    return x;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* node) {
    assert(isRed(node->left));
    Sector* x = node->left;
    x->parent = node->parent;
    node->parent = x;
    if (x->right != nullptr) {
        x->right->parent = node;
    }
    node->left = x->right;

    x->right = node;

    x->color = node->color;
    node->color = RED;
    return x;
}

void SpaceSectorLLRBT::flipColors(Sector* node) {
    assert(!isRed(node));
    assert(isRed(node->left));
    assert(isRed(node->right));
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}



void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
    cout << "Space sectors inorder traversal:" << endl;
    inOrderTraversal(root);
    cout << endl;
}

void SpaceSectorLLRBT::inOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    string color = (node->color == BLACK) ? "BLACK sector: " : "RED sector: ";
    inOrderTraversal(node->left);

    cout << color << node->sector_code << endl;
    inOrderTraversal(node->right);
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors preorder traversal:" << endl;
    preOrderTraversal(root);
    cout << endl;

}

void SpaceSectorLLRBT::preOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    string color = (node->color == BLACK) ? "BLACK sector: " : "RED sector: ";
    cout << color << node->sector_code << endl;
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    cout << "Space sectors postorder traversal:" << endl;
    postOrderTraversal(root);
    cout << endl;
}

void SpaceSectorLLRBT::postOrderTraversal(Sector* node) {
    if (node == nullptr) {
        return;
    }
    string color = (node->color == BLACK) ? "BLACK sector: " : "RED sector: ";
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << color << node->sector_code << endl;
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> pathHead;
    std::vector<Sector*> pathTail;

    Sector* start = findSector(root, "0SSS");
    Sector* target = findSector(root, sector_code);

    if (start == nullptr || target == nullptr) {
        return path;
    }

    while (start != nullptr) {
        pathHead.push_back(start);
        start = start->parent;
    }

    while (target != nullptr) {
        pathTail.push_back(target);
        target = target->parent;
    }

    int intersectionHead = 0;
    int intersectionTail = 0;
    for (int i = 0; i < pathHead.size(); i++) {
        for (int j = pathTail.size() - 1; j >= 0; j--) {
            if (pathHead[i] == pathTail[j]) {
                intersectionHead = i;
                intersectionTail = j;
                break;
            }
        }
        if (intersectionHead != 0 || intersectionTail != 0) {
            break;
        }
    }
    for (int i = 0; i <= intersectionHead; i++) {
        path.push_back(pathHead[i]);
    }
    if (intersectionTail != 0) {
        for (int i = intersectionTail - 1; i >= 0; i--) {
            path.push_back(pathTail[i]);
        }

    }

    return path;
}

Sector* SpaceSectorLLRBT::findSector(Sector* node, const std::string& sector_code) {

    if (node == nullptr || node->sector_code == sector_code) {
        return node;
    }

    Sector* left = findSector(node->left, sector_code);
    if (left != nullptr) {
        return left;
    }

    return findSector(node->right, sector_code);
}



void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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


