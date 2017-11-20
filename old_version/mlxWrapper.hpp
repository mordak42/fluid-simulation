/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxWrapper.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:43:31 by bmickael          #+#    #+#             */
/*   Updated: 2017/11/18 22:43:36 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define BPP 32
#define ENDIAN 0

union Pixel
{
	unsigned int		i;
	struct				s_c
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	} c;
};

namespace mod1
{
class MlxWrapper
{
public:
	MlxWrapper ();
	~MlxWrapper ();

protected:
	void mlxPutPixel(int x, int y);
	bool mlxInit(const std::string &windowName, int width, int height);
	void mlxMakeRender();

	Pixel *m_imgString = NULL;
	int m_width = 0;
	int m_height = 0;

private:
	void *m_mlx = NULL;
	void *m_win = NULL;
	void *m_image = NULL;
	bool m_isInitialized = false;
};
}
