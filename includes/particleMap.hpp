/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particleMap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 22:37:40 by mbeilles          #+#    #+#             */
/*   Updated: 2017/11/29 03:57:51 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARTICLEMAP_HPP__
# define __PARTICLEMAP_HPP__

# include <cstdint>
# include <iostream>

namespace mod1
{

typedef int32_t particleMapValue_t;

class ParticleMap {
public:
    ParticleMap(uint32_t height, uint32_t width, uint32_t depth);
    ~ParticleMap();
    void                fill(particleMapValue_t data);
    void                fill_in(particleMapValue_t start);
    void                increase(particleMapValue_t data);
    void                print();
    uint32_t            m_height;
    uint32_t            m_width;
    uint32_t            m_depth;
    particleMapValue_t  ***m_map;

protected:

private:
    particleMapValue_t  ***m_ptr = nullptr;
};

}

#endif
