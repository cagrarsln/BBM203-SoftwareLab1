#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* helper(Sector* node, int x, int y, int z);
    void addPointers(Sector* node, Sector* parent);
    void inOrderTraversal(Sector* node);
    void preOrderTraversal(Sector* node);
    void postOrderTraversal(Sector* node);
    Sector* findSector(Sector* node, const std::string& sector_code);
    bool findPath(Sector* current, Sector* target, std::vector<Sector*>& path);
    void freeMemory(Sector* node);

    bool isGreater(Sector* current, Sector* target);

    Sector* deleteNode(Sector* root, const std::string& sector_cod);


    };

#endif // SPACESECTORBST_H
