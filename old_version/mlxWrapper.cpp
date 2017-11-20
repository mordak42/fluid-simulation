/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxWrapper.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:39:42 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/18 22:39:45 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif
#include "mlx.h"
#ifdef __cplusplus
}
#endif

#include "mlxWrapper.hpp"

using namespace mod1;

MlxWrapper::MlxWrapper () {
	std::cout << "mlx initialisation sequence launched" << std::endl;
	m_mlx = mlx_init();
}

MlxWrapper::~MlxWrapper () {
	std::cout << "mlx sequence is ending" << std::endl;
	if (!m_isInitialized) {
		std::cout << "mlx not initialized" << std::endl;
		return ;
	}
	mlx_destroy_window(m_mlx, m_win);
}

bool MlxWrapper::mlxInit(const std::string &windowName, int width, int height) {
	if (m_isInitialized) {
		std::cout << "mlx already initialized" << std::endl;
		return false;
	}
	if (m_mlx == NULL) {
		std::cout << "mlx_init failed" << std::endl;
		return false;
	}
	m_win = mlx_new_window(m_mlx, width, height, (char *)windowName.c_str());
	if (m_win == NULL) {
		std::cout << "Cannot make window" << std::endl;
		return false;
	}

	m_image = mlx_new_image(m_mlx, width, height);
	if (m_image == NULL) {
		std::cout << "Cannot make mlx image" << std::endl;
		return false;
	}

	int bitsPerPixel = BPP;
	int endian = ENDIAN;
	int bytesPerLine = width * bitsPerPixel / 8;
	m_imgString = (Pixel *)mlx_get_data_addr(
		m_image,
		&bitsPerPixel,
		&bytesPerLine,
		&endian);

	if (m_imgString == NULL) {
		std::cout << "Cannot create imgSring" << std::endl;
		return false;
	}

	m_width = width;
	m_height = height;
	m_isInitialized = true;
	return true;
}

void MlxWrapper::mlxMakeRender() {
	mlx_put_image_to_window(m_mlx, m_win, m_image, 0, 0);
	mlx_loop(m_mlx);
}

void MlxWrapper::mlxPutPixel(int x, int y) {
	if (!m_isInitialized) {
		std::cout << "mlx not initialized" << std::endl;
		return ;
	}
	(void)x;
	(void)y;
}
