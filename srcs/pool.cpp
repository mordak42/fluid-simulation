
#include "pool.hpp"

using namespace mod1;

Pool::Pool(unsigned long nbFrames) :
        m_availabilitySem(nbFrames),
        m_nbFrames(nbFrames) {
    std::cout << "Pool initialisation" << std::endl;
}

Pool::~Pool() {
    m_ready = false;

    size_t tmp;

    tmp = m_actives.size();
    for (size_t i = 0; i < tmp; i++)
        m_actives.pop();

    tmp = m_inactives.size();
    for (size_t i = 0; i < tmp; i++)
        m_inactives.pop();

    std::cout << "Pool terminated" << std::endl;
}

/* TODO Out of memory case:
* It's difficult to reproduce in OSX, but we have to manage this exeption
* imperatively */

bool Pool::init() {
    if (m_ready == true) {
        std::cerr << __func__ << " : Pool already initialized" << std::endl;
        return false;
    }
    try {
        for (unsigned long i = 0; i < m_nbFrames; i++)
            m_inactives.emplace();
        m_ready = true;
        return true;
    }
    catch (const std::bad_alloc &) {
        std::cerr << __func__ << " : Out of memory" << std::endl;
        return false;
    }
}

/* Productor side */
ImgData *Pool::popOutdatedFrame(void) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
	m_availabilitySem.wait();
//    return (&m_inactives.front());


	while (1) {
	ImgData *img = new ImgData();
	ImgData *a2 = img;
	printf("%p %p\n", img, a2);
	a2->img[10] = 123;

	img->img[10] = 21;
	m_inactives.push(*img);
	img = &m_inactives.back();
	printf("%i\n", img->img[10]);
	img->img[10] = 42;
	img = &m_inactives.back();
	printf("%i\n", img->img[10]);
	m_inactives.pop();
	printf("%i\n", img->img[10]);
	m_actives.push(*img);
	printf("%i\n", (&m_actives.back())->img[10]);
	m_actives.push(*a2);
	m_actives.push(*a2);
	m_actives.push(*a2);
	printf("%i\n", (&m_actives.back())->img[10]);

	while (1);


	printf("ref = %p %p\n", img, &m_inactives.front());

	printf("ref = %p %p\n", img, &m_inactives.front());
	std::cout << "inactive size -> "<< m_inactives.size() << std::endl;
	img->img[0] = 0;
	m_actives.push(*img);
	printf("ref = %p %p\n", img, &m_actives.back());
	std::cout << "active size -> "<< m_actives.size() << std::endl;
	}
	return nullptr;
}

void Pool::pushRenderedFrame(ImgData *frame) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    m_actives.push(*frame);
	(void)frame;
}

/* Consumer side */
ImgData *Pool::popRenderedFrame(void) {
	if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return nullptr;
    }
    //if (m_actives.size() == 0)
        return nullptr;
	//return (&m_actives.front());
}

void Pool::pushOutdatedFrame(ImgData *frame) {
    if (m_ready == false) {
        std::cerr << __func__ << " : Pool not initialized" << std::endl;
        return;
    }
    //m_inactives.push(*frame);
	(void)frame;
    //m_availabilitySem.notify();
}
