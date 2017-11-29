/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particleMap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:53:55 by mbeilles          #+#    #+#             */
/*   Updated: 2017/11/29 04:11:59 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particleMap.hpp"

using namespace mod1;

/*  _______________________________________________________________________
 *  |                                                                     |
 *  |              This is the layout of the memory structure             |
 *  |                                                                     |
 *  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *  _______________________________________________________________________
 *  | Stack 1 | ... | Stack 2 | ... | Stack 3 | ... ... ... ... | Stack 3 |
 *  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *      Stack 1 : int *** | Primary layer           | Height related
 *      Stack 2 : int **  | Secondary layer         | Width related
 *      Stack 3 : int *   | Last layer              | Depth related
 *
 *  _______________________________________________________________________
 *  |                    Memory adrress corresspondances                  |
 *  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *  m_map[ i ][ j ][ k ] --------> index value of particle
 *         |    |    |
 *         |    |    +-> Stack 3 | (m_map + heigth + width * heigth
 *         |    |                         + i * width * depth + j * depth + k)
 *         |    |
 *         |    +------> Stack 2 | (m_map + heigth + width * heigth
 *         |                              + i * width * depth + j * depth)
 *         |
 *         +-----------> Stack 1 | (m_map + heigth + i * width)
 *
 *                   _____________________________________
 *                  /!\ Upon constructing use try:catch /!\
 *                  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 */

ParticleMap::ParticleMap(uint32_t height, uint32_t width, uint32_t depth) :
    m_height(height), m_width(width), m_depth(depth)
{
    uint32_t                    i = 0;
    uint32_t                    j = 0;

    if (!(m_ptr = (particleMapValue_t***)calloc(
        (sizeof(particleMapValue_t***) * (m_height + (m_height * m_width)))
      + (sizeof(particleMapValue_t) * (m_height * m_width * m_depth)), 1)))
        return;
    m_map = m_ptr;
    i = 0;
    while (i < m_height)
    {
        m_map[i] = (particleMapValue_t**)((uint8_t*)(m_map + m_height + i * m_width));
        j = 0;
        while (j < m_width)
        {
            m_map[i][j] = (particleMapValue_t*)((uint8_t*)((m_map + m_height + m_width * m_height
                + i * m_width * m_depth + j * m_depth));
            j++;
        }
        i++;
    }
}

ParticleMap::~ParticleMap()
{
    free(m_ptr);
}

/*
 * Fill     -> fills map with the data
 *
 * Increase -> Add the data to all of the data of the map
 *
 * Print    -> Usefull thingy that displays the content of the map in output
 */

void ParticleMap::fill(particleMapValue_t data)
{
    for (uint32_t i = 0; i < m_height; i++)
        for (uint32_t j = 0; j < m_width; j++)
            for (uint32_t k = 0; k < m_depth; k++)
                m_map[i][j][k] = data;
}

void ParticleMap::fill_in(particleMapValue_t start)
{
    for (uint32_t i = 0; i < m_height; i++)
        for (uint32_t j = 0; j < m_width; j++)
            for (uint32_t k = 0; k < m_depth; k++)
                m_map[i][j][k] = start++;
}

void ParticleMap::increase(particleMapValue_t data)
{
    for (uint32_t i = 0; i < m_height; i++)
        for (uint32_t j = 0; j < m_width; j++)
            for (uint32_t k = 0; k < m_depth; k++)
                m_map[i][j][k] += data;
}

void ParticleMap::print()
{
    for (uint32_t i = 0; i < m_height; i++) {
        for (uint32_t j = 0; j < m_width; j++) {
            for (uint32_t k = 0; k < m_depth; k++)
                printf (" %5.5d", m_map[i][j][k]);
            printf (" |");
        }
    printf("\n");
    }
}
