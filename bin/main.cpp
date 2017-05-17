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

void renderPlayer(SDL_Renderer* rnd, SDL_Rect object, int yPos, int xPos){
	object.y=yPos;
	object.x=xPos;
	object.h=20;
	object.w=20;
	SDL_RenderSetViewport(rnd, &object);
	SDL_RenderCopy(rnd, gTexture.mTexture, NULL, NULL);
}

void close(){
	gTexture.free();
	/*for(int i=0; i<sizeof(obj); i++){
		obj[i].free();
	}*/
	SDL_DestroyWindow(gWindow);
	gWindow=NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer=NULL;
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]){
	int yPosPlayer=SCREEN_HEIGHT-80;
	int xPosPlayer=SCREEN_WIDTH/2;
	if(!init()){
		std::cout << "Could not initialize\n";
	}
	else{
		if(!loadMedia("texture.png")){
			std::cout << "Failed to load texture\n";
		}
		else{
			Invader invader[3];
			bool quit=false;
			bool endOfProgram=false;
			bool stepDown=false;
			int distPlayer=10;
			int frames=0;
			SDL_Event e;
			/*Uint8 r=255;
			Uint8 g=255;
			Uint8 b=255;*/
			while(!quit){
				while(SDL_PollEvent(&e)!=0){
					if(e.type==SDL_QUIT){
						quit=true;
					}
					else if(e.type==SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							case SDLK_UP:
								/*if(r!=255){
									r+=32;
								}
								else{
									r=0;
								}*/

								break;
							/*case SDLK_DOWN:
								/if(r!=255 & g!=255 && b!=255){
									r+=32;
									g+=32;
									b+=32;
								}
								else{
									r=0;
									g=0;
									b=0;
								}
								height+=dist;
								break;*/
							case SDLK_LEFT:
								/*if(g!=255){
									g+=32;
								}
								else{
									g=0;
								}*/
								if(xPosPlayer<=20){
									xPosPlayer=20;
								}
								else{
									xPosPlayer-=distPlayer;
								}
								break;
							case SDLK_RIGHT:
								/*if(b!=255){
									b+=32;
								}
								else{
									b=0;
								}*/
								if(xPosPlayer>=600){
									xPosPlayer=600;
								}
								else{
									xPosPlayer+=distPlayer;
								}
								break;
							/*default:
								//height=SCREEN_HEIGHT/2;
								width=SCREEN_WIDTH/2;
								break;*/
						}
					}
				}
				//SDL_Delay(1000);
				SDL_RenderClear(gRenderer);
				//gTexture.setColor(r, g, b);
				//gTexture.render(widthPlayer, heightPlayer, gRenderer);
				frames++;
				if(frames%10==0){
					for(int i=0; i<3; i++){
						if(!stepDown){
							if(invader[i].yPos<=95){
								stepDown=true;
								invader[i].xPos+=20;
							}
							else{
								invader[i].yPos-=invader[i].distance;
							}
						}
						else{
							if(invader[i].yPos>=545){
								stepDown=false;
								invader[i].xPos+=20;
							}
							else{
								invader[i].yPos+=invader[i].distance;
							}
						}
						if(invader[i].xPos>=xPosPlayer){
							endOfProgram=true;
						}
					}
				}
				SDL_Delay(10);
				if(!endOfProgram){
					/*SDL_Rect viewportBootom1;
					renderViewport(gRenderer, viewportBootom1, height-25, width-50);
					SDL_Rect viewportBootom2;
					renderViewport(gRenderer, viewportBootom2, height-25, width-25);
					SDL_Rect viewportBootom3;
					renderViewport(gRenderer, viewportBootom3, height-25, width);
					SDL_Rect viewportBootom4;
					renderViewport(gRenderer, viewportBootom4, height-25, width+25);
					SDL_Rect viewportBootom5;
					renderViewport(gRenderer, viewportBootom5, height-25, width+50);

					SDL_Rect viewportMiddle1;
					renderViewport(gRenderer, viewportMiddle1, height, width-50);
					SDL_Rect viewportMiddle2;
					renderViewport(gRenderer, viewportMiddle2, height, width-25);
					SDL_Rect viewportMiddle3;
					renderViewport(gRenderer, viewportMiddle3, height, width);
					SDL_Rect viewportMiddle4;
					renderViewport(gRenderer, viewportMiddle4, height, width+25);
					SDL_Rect viewportMiddle5;
					renderViewport(gRenderer, viewportMiddle5, height, width+50);

					SDL_Rect viewportUpper1;
					renderViewport(gRenderer, viewportUpper1, height+25, width-50);
					SDL_Rect viewportUpper2;
					renderViewport(gRenderer, viewportUpper2, height+25, width-25);
					SDL_Rect viewportUpper3;
					renderViewport(gRenderer, viewportUpper3, height+25, width);
					SDL_Rect viewportUpper4;
					renderViewport(gRenderer, viewportUpper4, height+25, width+25);
					SDL_Rect viewportUpper5;
					renderViewport(gRenderer, viewportUpper5, height+25, width+50);*/

					for(int i=0; i<3; i++){
						invader[i].render(gRenderer, gTexture);
					}

					SDL_Rect player;
					renderPlayer(gRenderer, player, yPosPlayer, xPosPlayer);

					SDL_RenderPresent(gRenderer);
				}
				else{
					for(int i=0; i<3; i++){
						invader[i].free();
					}
					//your score, show 10 best
					SDL_RenderClear(gRenderer);
				}
			}
		}
	}
	close();
	return 0;
}
