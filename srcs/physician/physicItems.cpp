
#include "physician/physicItems.hpp"

#include <unistd.h>
#define FILE_MAX_SIZE 65536

using namespace mod1;

PhysicItems::PhysicItems() {}

PhysicItems::~PhysicItems() {}

std::string PhysicItems::parseClFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == nullptr) {
        std::cerr << "The file " << filename << " is not so good !" << std::endl;
        exit(EXIT_FAILURE);
    }

    char buf[FILE_MAX_SIZE + 1];
    size_t readenSize = fread(buf, FILE_MAX_SIZE + 1, 1, file);

    if (readenSize > FILE_MAX_SIZE) {
        std::cerr << "The file " << filename << " seams too huge !" << std::endl;
        return nullptr;
    }
    return std::string(buf);
}

void PhysicItems::serializeGridV(
        struct velocity_field (&dst)[GRID_WIDTH * (GRID_HEIGHT + 1)],
        struct velocity_field (&grid_v)[GRID_WIDTH][GRID_HEIGHT + 1])
{
    for (int y = 0; y < (GRID_HEIGHT + 1); y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            dst[x * (GRID_HEIGHT + 1) + y] = grid_v[x][y];
        }
    }
}

void PhysicItems::unserializeGridV(
        struct velocity_field (&grid_v)[GRID_WIDTH][GRID_HEIGHT + 1],
        struct velocity_field (&src)[GRID_WIDTH * (GRID_HEIGHT + 1)])
{
    for (int i = 0; i < (GRID_WIDTH * (GRID_HEIGHT + 1)); i++)
        grid_v[i / (GRID_HEIGHT + 1)][i % (GRID_HEIGHT + 1)] = src[i];
}
