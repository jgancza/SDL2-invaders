#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "texture.h"
#include "invader.h"

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer=NULL;
LTexture gTexture;

bool init(){
	bool success=true;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		std::cout << "Could not initialize! SDL Error: %s\n" << SDL_GetError();
		success=false;
	}
	else{
		gWindow=SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow==NULL){
			std::cout << "Could not create window! SDL Error: %s\n" << SDL_GetError();
			success=false;
		}
		else{
			gRenderer=SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer==NULL){
				std::cout << "Could not create renderer! SDL Error: %s\n" << SDL_GetError();
				success=false;
			}
			else{
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				int imgFlags=IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					std::cout << "SDL_Image could not initialize! SDL_Image Error: %S\n" << IMG_GetError();
					success=false;
				}
			}
		}
	}
	return success;
}

bool loadMedia(std::string path){
	bool success=true;
	if(!gTexture.loadFromFile(path.c_str(), gRenderer)){
		std::cout << "Could not load texture!\n";
		success=false;
	}
	return success;
}

void render(SDL_Renderer* rnd, SDL_Rect object, int yPos, int xPos){
	object.y=yPos;
	object.x=xPos;
	object.h=20;
	object.w=20;
	SDL_RenderSetViewport(rnd, &object);
	SDL_RenderCopy(rnd, gTexture.mTexture, NULL, NULL);
}

void close(){
	gTexture.free();
	SDL_DestroyWindow(gWindow);
	gWindow=NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer=NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]){
	if(!init()){
		std::cout << "Could not initialize\n";
	}
	else{
		if(!loadMedia("texture.png")){
			std::cout << "Failed to load texture\n";
		}
		else{
			int row=5;
			int yPosPlayer=400;
			int xPosPlayer=320;
			Invader invader[row][row];
			for(int i=0; i<row; i++){
				for(int j=0; j<row; j++){
					invader[i][j].yPos-=(25*i);
					invader[i][j].xPos-=(25*j);
				}
			}
			bool quit=false;
			bool endOfGame=false;
			bool stepDown=false;
			int distPlayer=8;
			int frames=0;
			SDL_Event e;
			while(!quit){
				while(SDL_PollEvent(&e)!=0){
					if(e.type==SDL_QUIT){
						quit=true;
					}
					else if(e.type==SDL_KEYDOWN){
						switch(e.key.keysym.sym){
                        /*case SDLK_UP:
                            break;*/
                        case SDLK_LEFT:
                            if(xPosPlayer <= 20) {
                                xPosPlayer=20;
                            }
                            else {
                                xPosPlayer-=distPlayer;
                            }
                            break;
                        case SDLK_RIGHT:
                            if(xPosPlayer>=600) {
                                xPosPlayer=600;
                            }
                            else{
                                xPosPlayer+=distPlayer;
                            }
                            break;
						}
					}
				}
				SDL_Delay(10);
				gTexture.render(xPosPlayer, yPosPlayer, gRenderer);
				SDL_RenderClear(gRenderer);
				frames++;
				if(frames%10==0){
					if(!stepDown){
						if(invader[0][0].xPos>=600){
							stepDown=true;
							for(int i=0; i<row; i++){
								for(int j=0; j<row; j++){
									invader[i][j].increaseY();
								}
							}
						}
						else{
							for(int i=0; i<row; i++){
								for(int j=0; j<row; j++){
									invader[i][j].increaseX();
								}
							}
						}
					}
					else{
						if(invader[0][4].xPos<=40){
							stepDown=false;
							for(int i=0; i<row; i++){
								for(int j=0; j<row; j++){
									invader[i][j].increaseY();
								}
							}
						}
						else{
							for(int i=0; i<row; i++){
								for(int j=0; j<row; j++){
									invader[i][j].decreaseX();
								}
							}
						}
					}
					if(invader[0][0].yPos>=yPosPlayer){
						endOfGame=true;
					}
					if(!endOfGame){
						for(int i=0; i<row; i++){
							for(int j=0; j<row; j++){
								render(gRenderer, invader[i][j].object, invader[i][j].yPos, invader[i][j].xPos);
							}
						}
						SDL_Rect player;
						render(gRenderer, player, yPosPlayer,xPosPlayer);
						SDL_RenderCopy(gRenderer, gTexture.mTexture, NULL, NULL);

						SDL_RenderPresent(gRenderer);
					}
				}
				else{
					/*for(int i=0; i<3; i++){
						invader[i].free();
					}*/
					//your score, show 10 best
					SDL_RenderClear(gRenderer);
				}
			}
		}
	}
	close();
	return 0;
}
