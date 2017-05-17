#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Bullet{
	public:
		int xPos;
		int yPos;
		int height;
		int width;
		Bullet(int x, int y, int h, int w);
		~Bullet();
		void free();
};
