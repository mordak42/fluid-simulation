
#ifndef __RENDERER_HPP__
# define __RENDERER_HPP__

#include "renderer/renderedFrame.hpp"
#include <mod1.hpp>

namespace mod1
{
class Renderer
{
public:
    Renderer(struct particle *particles, struct cell **grid);
    ~Renderer();
    void raytrace(RenderedFrame *img);
private:
    struct particle *m_particles;
    struct cell **m_grid;
};
}

#endif
