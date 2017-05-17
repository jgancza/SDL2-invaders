#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class LTexture{
	private:
		int mWidth;
		int mHeight;

	public:
		SDL_Texture* mTexture;
		LTexture();
		~LTexture();
		bool loadFromFile(std::string path, SDL_Renderer* rnd);
		void free();
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void render(int x, int y, SDL_Renderer* rnd, SDL_Rect* clip=NULL);
		int getWidth();
		int getHeight();
};
