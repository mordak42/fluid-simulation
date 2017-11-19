
#include "pool.hpp"

using namespace mod1;

Pool::Pool(std::function<bool(ImgData &)> fn) {}

Pool::~Pool() {
	m_ready = false;

	for (size_t i = 0; i < m_actives.size(); i++) {
		m_actives.pop();
	}

	for (size_t i = 0; i < m_inactives.size(); i++) {
		m_inactives.pop();
	}
}

bool Pool::Init(int size) {
	for (int i = 0; i < size; i++) {
		ImgData *image = new ImgData();
		m_actives.push(*image);													// TODO FAIL ALLOC
	}
	m_ready = true;
	return true;
}

bool Pool::DrawOnRawImage(void) {
	if (m_ready == false)
		return false;

	if (m_inactives.size() > 0) {
		ImgData &image = m_inactives.front();
		image.isReady = false;
//		draw(image);
		image.isReady = true;
		m_actives.push(image);
		return true;
	}
	return false;
}

bool Pool::GetRenderedImage(std::function<bool(ImgData &img)>draw) {
	if (m_ready == false)
		return false;

	if (m_actives.size() > 0 && m_actives.front().isReady == true) {
		ImgData &image = m_actives.front();
		image.isReady = false;
		draw(image);
		image.isReady = true;
		m_inactives.push(image);
		return true;
	}
	return false;
}
