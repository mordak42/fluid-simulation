
#ifndef __RENDERER_HPP__
# define __RENDERER_HPP__

#include <memory>

#include "renderer/renderedFrame.hpp"
#include "physician/physicItems.hpp"

namespace mod1
{
class Renderer: public virtual PhysicItems
{
public:
    Renderer();
    ~Renderer();
    void raytrace(RenderedFrame *img);
private:
};
}

#endif
