#include <iostream>

namespace mod1
{
class MlxWrapper
{
public:
	MlxWrapper ();
	~MlxWrapper ();
	bool init(std::string windowName, int width, int height);
	void putPixel(int x, int y);

private:
	void *mlx = NULL;
	void *win = NULL;
	bool initilised = false;
};
}
