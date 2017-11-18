
#ifdef __cplusplus
extern "C" {
#endif
#include "mlx.h"
#ifdef __cplusplus
}
#endif

#include "mlx.hpp"

using namespace mod1;

MlxWrapper::MlxWrapper () {
	std::cout << "mlx initialisation sequence launched" << std::endl;
	mlx = mlx_init();
};

MlxWrapper::~MlxWrapper () {
	std::cout << "mlx sequence is ending" << std::endl;
	mlx_destroy_window(mlx, win);
};

bool MlxWrapper::init(std::string windowName, int width, int height) {
	if (mlx == NULL) {
		std::cout << "mlx_init failed" << std::endl;
		return false;
	}
	win = mlx_new_window(mlx, width, height, (char *)windowName.c_str());
	if (win == NULL) {
		std::cout << "Cannot make window" << std::endl;
		return false;
	}
	initilised = true;
	return true;
}

void MlxWrapper::putPixel(int x, int y) {
	if (!initilised) {
		std::cout << "mlx not initialised" << std::endl;
		return ;
	}
	(void)x;
	(void)y;
};
