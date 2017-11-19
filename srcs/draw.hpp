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

#include "mlxWrapper.hpp"

namespace mod1
{
class Draw : public MlxWrapper
{
public:
	Draw ();
	~Draw ();

	bool drawInit(const std::string &windowName, int width, int height);
	void clearScreen(Pixel color);
};
}
