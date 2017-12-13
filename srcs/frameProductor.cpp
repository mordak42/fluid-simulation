
#include "frameProductor.hpp"

#include "utils/chronometric.hpp"

#include <thread>

using namespace mod1;

FrameProductor::FrameProductor(const std::shared_ptr<lib::Pool<RenderedFrame>> &pool) :
                                                                    PhysicItems(),
                                                                    Renderer(),
                                                                    Physician(),
                                                                    m_pool(pool)
{
}

FrameProductor::~FrameProductor() {}

void FrameProductor::start() {
     m_keepGoing = true;
     std::thread instance(&FrameProductor::threadHandler, this);
     instance.detach();
}

void FrameProductor::stop() {
    m_keepGoing = false;
    /* Send a artificial token to quit */
    m_pool->sendToken();
    /* Unlocked only  when the frameProductor thread has finished his works ! */
    std::lock_guard<std::mutex> lock(m_threadProtection);
}

#define SIZE_EXEMPLE 4

static void    debug_poly(Polynom poly)
{
    for (int i = poly.m_nb_coefs - 1; i >= 0; i--) {
        std::cout << ' ' << poly.m_coefs[i];
        std::cout << "*x^" << i << " + ";
    }
    std::cout << '\n';
    (void)poly;
}

/*
 * google example:
 * 3.77604e-08*x^4 +  -6.61458e-05*x^3 +  0.0316146*x^2 +  -3.22917*x^1 +  0
*/

//bool FrameProductor::parseFile(const char &buff) {
bool FrameProductor::parseFile() {
    struct point p[SIZE_EXEMPLE];
    p[0].x = 0;
    p[0].y = 0;
    p[1].x = 0.2 * real_width;
    p[1].y = 0.4 * real_height;
    p[2].x = 0.8 * real_width;
    p[2].y = -0.4 * real_height;
    p[3].x = real_width;
    p[3].y = 0;
    m_groundLevel = lagrange(p, SIZE_EXEMPLE);
    debug_poly(m_groundLevel);
    for (int i = 0 ; i < GRID_WIDTH; i++) {
        for (int j = -GRID_HEIGHT / 2 ; j < GRID_HEIGHT / 2; j++)
            GRID[i][j + GRID_HEIGHT / 2].type = m_groundLevel.eval(i * DX) - j *DY > 0 ? SOLID : AIR;
        }
    //return m_physician->init_particules(100, 140, 80, 40, true) > 0 ? true : false;
    return true;
}

void FrameProductor::threadHandler() {
    std::lock_guard<std::mutex> lock(m_threadProtection);
    int i = 0;
    bzeroVelocity();
    lib::Chronometric timeCounter;
    while (true) {
        if (i % 100 == 0)
            init_particules(110, 100, 20, 20, true);
        timeCounter.reset();
        put_velocity_on_grid();
		extrapolateVelocity();
        applyGravity();
  //     solvePressure();
        get_velocity_from_the_grid();
//		saveVelocity();
        advect();
        RenderedFrame *img = m_pool->popOutdatedItem();
        if (m_keepGoing == false)
            break;
        if (img == NULL)
            continue;
        img->cleanFrame();
        raytrace(img);
        img->solvedTime = timeCounter.getTime();
        m_pool->pushRenderedItem(img);
        i++;
    }
}
