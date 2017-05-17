#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "texture.h"

LTexture::LTexture(){
	mTexture=NULL;
	mWidth=0;
	mHeight=0;
}

LTexture::~LTexture(){
	free();
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* rnd){
	free();
	SDL_Texture* newTexture=NULL;
	SDL_Surface* loadedSurface=IMG_Load(path.c_str());
	if(loadedSurface==NULL){
		std::cout << "Could not load image %s! SDL_Image Error: %s\n" << IMG_GetError();
	}
	else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture=SDL_CreateTextureFromSurface(rnd, loadedSurface);
		if(newTexture==NULL){
			std::cout << "Could not create texture! SDL Error: %s\n" << SDL_GetError();
		}
		else{
			mWidth=loadedSurface->w;
			mHeight=loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture=newTexture;
	return mTexture!=NULL;
}

void LTexture::free(){
	if(mTexture!=NULL){
		SDL_DestroyTexture(mTexture);
		mTexture=NULL;
		mWidth=0;
		mHeight=0;
	}
}

void LTexture::render(int x, int y, SDL_Renderer* rnd, SDL_Rect* clip){
	SDL_Rect renderQuad={x, y, mWidth, mHeight};
	if(clip!=NULL){
		renderQuad.w=clip->w;
		renderQuad.h=clip->h;
	}
	SDL_RenderCopy(rnd, mTexture, clip, &renderQuad);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight(){
	return mHeight;
}
