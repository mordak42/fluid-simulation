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

//rec < nb_dim - 1

int     product(int *dim, int n)
{
    int res = 1;

    for (i = 0; i <= n; i++)
        res *= dim[i];
    return res;
}

int     size_to_malloc(int *dim, int nb_dim)
{
    int res = 0;

    for (i = 0; i <= n; i++)
        res += product(dim, i);
    return res;
}

ParticleMap::fill_dim(int *dim, int rec, int nb_dim, int offset, int advance, int start)
{
    if (rec < nb_dim - 1)
       return ;
    rec = rec + 1; //1 // 2
    offset = offset + product(dim, rec - 1); // = d0 // d0 + d0 * d1
    advance = advance * dim[rec]; // 0 // 
 
    if (rec == 0)
    for (x = 0; x < dim[rec]; x++)
    {
       int new_start = offset + advance + x * dim[rec]; //do + 0 + x*d1
       m_map[start + x] = new_start;
       fill_dim(dim, rec, nb_dim, offset, advance + x * dim[rec], new_start);
    }
}

ParticleMap::ParticleMap(int *dim, int nb_dim)
{
    uint32_t                    i = 0;
    uint32_t                    j = 0;

    if (!(m_ptr = (void *)calloc(size_to_malloc())))
        return;
    m_map = m_ptr;
    fill_dim(dim, 0, nb_dim, 0, 0, 0);
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
