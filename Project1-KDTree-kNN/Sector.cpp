#include "Sector.h"
#include <cmath>
// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
        // TODO: Calculate the distance to the Earth, and generate the sector code
    distance_from_earth = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    std::string x_str;
    std::string y_str;
    std::string z_str;

    if (x < 0) {
        x_str = "L";
    }
    else if (x == 0) {
        x_str = "S";
    }
    else {
        x_str = "R";
    }

    if (y < 0) {
        y_str = "D";
    }
    else if (y == 0) {
        y_str = "S";
    }
    else {
        y_str = "U";
    }
    if (z < 0) {
        z_str = "B";
    }
    else if (z == 0) {
        z_str = "S";
    }
    else {
        z_str = "F";
    }

    sector_code = std::to_string(int(distance_from_earth));
    sector_code += x_str + y_str + z_str;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary

}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}