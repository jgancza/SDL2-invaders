#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "bullet.h"


Bullet::Bullet(int x, int y, int h, int w){
	xPos=x;
	yPos=y;
}

Bullet::~Bullet(){
}

void Bullet::free(){
}
