#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    void freeMemory(Sector* node);

    Sector* helper(Sector* node, Sector* parent , int x, int y, int z);

    Sector* findSector(Sector* node, const std::string& sector_code);


    // Red-Black Tree helper functions
    bool isRed(Sector* x);
    Sector* rotateLeft(Sector* node);
    Sector* rotateRight(Sector* node);
    void flipColors(Sector* node);

    // Traversal helper functions
    void inOrderTraversal(Sector* node);
    void preOrderTraversal(Sector* node);
    void postOrderTraversal(Sector* node);

};

#endif // SPACESECTORLLRBT_H
