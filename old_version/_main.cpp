/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:46:19 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/18 13:46:24 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>

#include "draw.hpp"

using namespace mod1;

int main(void)
{
	Draw *mlx = new Draw();
	mlx->drawInit("ma fenetre", 1024, 768);

	Pixel a;

	a.c.r = 200;
	a.c.g = 144;
	a.c.b = 33;
	a.c.a = 127;

	mlx->clearScreen(a);
	delete mlx;
//	mlx.init(std::string("mod1"), 1920, 1080);
//	sleep(5);
//	mlx.exit();
	while (1);
	return 0;
}
