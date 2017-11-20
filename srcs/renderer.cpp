#include "renderer.hpp"

using namespace mod1;

Renderer::Renderer(const std::shared_ptr<mod1::Pool> &pool) : m_pool(pool) {
}

Renderer::~Renderer() {}

void Renderer::pushImage() {
		ImgData *frame;
		m_pool->DrawOnRawImage(&frame);
}
