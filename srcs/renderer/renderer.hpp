
#ifndef __RENDERER_HPP__
# define __RENDERER_HPP__

//#define LITTLE_RAIN
#define HUGE_RAIN
#define HUGE_BLOCK
#define FEMME_FONTAINE

#define BORDER
#define BORDER_LENGTH 4.

#define GRID_DEBUG

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
