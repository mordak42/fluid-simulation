
#ifndef __RENDERER_HPP__
# define __RENDERER_HPP__

#include <memory>

#include "renderer/renderedFrame.hpp"
#include "physician/physicItems.hpp"

namespace mod1
{
class Renderer
{
public:
    Renderer(const std::shared_ptr<PhysicItems> &physicItems);
    ~Renderer();
    void raytrace(RenderedFrame *img);
private:
    const std::shared_ptr<PhysicItems> &m_physicItems;
};
}

#endif
