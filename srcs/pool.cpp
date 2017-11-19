
#include "pool.hpp"

using namespace mod1;

Pool::Pool() {}

Pool::~Pool() {
	m_ready = false;

	ImgData *img;
	for (int i = 0; i < m_actives.size; i++) {
		img = m_actives.dequeue();
		delete img;
	}

	for (int i = 0; i < m_inactives.size; i++) {
		img = m_inactives.dequeue();
		delete img;
	}
}

bool Pool::Init(int size) {
	for (int i = 0; i < size; i++)
		m_actives.push(new ImgData); // TODO FAIL ALLOC
	m_ready = true;
}

bool Pool::GetRawImage(ref ImgData image) {
	if (m_ready == false)
		return false;

	if (inactives.size > 0) {
		*image = m_inactives.pop();
		m_actives.push(*image);
		image->isReady = false;
		return true;
	}
	return false;
}

bool Pool::GetRenderedImage(ref ImgData image) {
	if (m_ready == false)
		return false;

	if (m_actives.size > 0 && m_actives.front.isReady == true) {
		image = m_actives.pop();
		image.isReady = false;
		m_inactives.push(image);
		return true;
	}
	return false;
}

private:
	std::queue<ImgData> m_actives;
	std::queue<ImgData> m_inactives;
	bool m_ready;
}
