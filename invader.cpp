#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "invader.h"

Invader::Invader(int h, int w, int ox, int oy){
	height=h;
	width=w;
	xPos=ox;
	yPos=oy;
	destroyed=false;
}

Invader::~Invader(){
	free();
}

int Invader::increaseX(){
	xPos+=5;
	return xPos;
}

int Invader::decreaseX(){
	xPos-=5;
	return xPos;
}

int Invader::increaseY(){
	yPos+=20;
	return yPos;
}

void Invader::free(){
	height=0;
	width=0;
	xPos=0;
	yPos=0;
}

