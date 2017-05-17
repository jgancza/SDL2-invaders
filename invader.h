#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Invader{
	public:
		int xPos;
		int yPos;
		int height;
		int width;
		SDL_Rect object;
		bool destroyed;
		Invader(int h=20, int w=20, int ox=320, int oy=240);
		~Invader();
		int increaseX();
		int decreaseX();
		int increaseY();
		void free();
};
