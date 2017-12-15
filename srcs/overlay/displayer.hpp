
#ifndef __DISPLAYER_HPP__
# define __DISPLAYER_HPP__

#include "overlay/sdlContext.hpp"

namespace mod1
{
class Displayer : public virtual SdlContext
{

public:
    Displayer();
    ~Displayer();

protected:
    bool initFont(const char *pathname, int fontSize);
    bool displayMsg(int originWidth, int originHeight, unsigned int color, const char *fmt, ...);

private:
    TTF_Font *m_font = nullptr;
    bool m_ready = false;
};
}

#endif
