#include "Bmickael.hpp"

using namespace mod1;

Bmickael::Bmickael(std::shared_ptr<Pool>pool) : m_pool(pool) {
}

Bmickael::~Bmickael() {}

void Bmickael::pushImage() {
		ImgData *frame;
		m_pool->DrawOnRawImage(&frame);
}
