# BBM203 - Software Laboratory I

This project was developed for the BBM203 Software Lab I course at Hacettepe University. It is written in C++ and demonstrates the use of data structures such as KD-Trees, k-Nearest Neighbors, and Binary Search Trees to organize and query spatial sector data.

## 🚀 Project Summary

The project models space sectors and enables operations such as insertion, deletion, and nearest neighbor queries using:

- **KD-Tree** for spatial indexing and fast search.
- **k-NN** algorithm for finding the nearest sectors.
- **Binary Search Tree (BST)** and **Left-Leaning Red-Black Tree (LLRBT)** implementations for efficient sector management.

## 📂 File Descriptions

| File | Description |
|------|-------------|
| `KD_Tree.cpp/h` | Implementation of a KD-Tree data structure |
| `KDT_Node.h` | Node structure used in the KD-Tree |
| `kNN.cpp/h` | k-Nearest Neighbor algorithm implementation |
| `kNN_Data.h`, `kNN_DAT_Parser.h` | Utilities for handling kNN datasets |
| `Sector.cpp/h` | Definition of a sector in space (coordinates, ID, etc.) |
| `SpaceSectorBST.cpp/h` | BST-based sector storage |
| `SpaceSectorLLRBT.cpp/h` | LLRBT-based sector storage |

## 🛠️ Compilation

To compile the project, use any standard C++ compiler. Example with g++:

```bash
g++ -std=c++11 *.cpp -o sector_project