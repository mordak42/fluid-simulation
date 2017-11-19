/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:52:33 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/18 22:52:35 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.hpp"

using namespace mod1;

Draw::Draw () {
};

Draw::~Draw () {
};

bool Draw::drawInit(const std::string &windowName, int width, int height) {
	int ret = mlxInit(windowName, width, height);
	if (ret == false) {
		std::cerr << "Cannot intialize mlx" << std::endl;
	}
	return true;
}

void Draw::clearScreen(Pixel color) {
	int pixelNb = m_width * m_height;
	while (pixelNb--) {
		std::cout << pixelNb << std::endl;
		m_imgString[pixelNb] = color;
	}
	mlxMakeRender();
}
