#ifndef __COMMON_HPP__
# define __COMMON_HPP__

# define MATH_WIDTH 1000
# define MATH_HEIGHT 2000
# define MATH_SIZE (MATH_WIDTH) * (MATH_HEIGHT)

/* Correspond au nombre de metres */
#define REAL_SIZE 10

#define DX REAL_SIZE / MATH_WIDTH           // TODO ne fonctionnerait pas, une macro ne peut etre flotamte.
#define DY DX

#endif
