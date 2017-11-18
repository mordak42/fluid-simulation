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

#include "mlx.hpp"

/*
#ifdef __cplusplus
extern "C" {
#endif
#include "mlx.h"
#ifdef __cplusplus
}
#endif

namespace mod1
{
	class Mlx
	{
		public:

			Mlx () {
			};

			~Mlx () {
			};

			void put_pixel(int x, int y) {
				(void)x;
				(void)y;
			};

			bool init(std::string window_name, int width, int height) {
				if (!(mlx = mlx_init()))
					return (false);
				if (!(win = mlx_new_window(mlx, width, height, (char *)window_name.c_str())))
					return (false);
				return (true);
			}

			void exit() {
				mlx_destroy_window(mlx, win);
			}

			void *mlx;
			void *win;
	};

}
*/
using namespace mod1;

int main(void)
{
	MlxWrapper *mlx = new MlxWrapper();
	mlx->init("ma fenetre", 100, 100);
	sleep(5);
	delete mlx;
//	mlx.init(std::string("mod1"), 1920, 1080);
//	sleep(5);
//	mlx.exit();
	return 0;
}
