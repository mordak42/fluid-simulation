#include "particleMap.hpp"

using namespace mod1;

int main(int c, char **v)
{
    try {
        ParticleMap *map = new ParticleMap(atoi(v[1]), atoi(v[2]), atoi(v[3]));
        map->m_map[atoi(v[4])][atoi(v[5])][atoi(v[6])] = atoi(v[7]);
        std::cout << "map[]: " << map->m_map[atoi(v[4])][atoi(v[5])][atoi(v[6])] << std::endl;
        map->fill(23);
        std::cout << "map[]: " << map->m_map[atoi(v[4])][atoi(v[5])][atoi(v[6])] << std::endl;
        map->print();
    } catch (const std::exception& e) {
        std::cout << "Fail! " << e.what() << "\n";
        return (-1);
    }
}
