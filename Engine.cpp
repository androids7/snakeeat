#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>


#include "HomeStatge.h"

SDL_Window *window = NULL;
SDL_Renderer *ren= NULL;

bool gameOver = false;

HomeStatge *home = new HomeStatge();

void Init(void) {
  //图形的初始化

  SDL_Init(SDL_INIT_EVERYTHING);
  window =
      SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 480, 600, SDL_WINDOW_RESIZABLE);
  ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  TTF_Init();

  IMG_Init(IMG_INIT_PNG);
  IMG_Init(IMG_INIT_JPG);
}




Uint32 callback(Uint32 interval, void *param)//回调函数 
{

SDL_Event gameEvent;       






while ( SDL_PollEvent(&gameEvent) != 0 ){  /*　SDL_PollEvent(&gameEvent);  if(&gameEvent != 0 ){　*/

  if (gameEvent.type == SDL_QUIT) {

  	gameOver = true;

   
  }

  home->logic();
  printf("he\n");
}

//   gameOver = true;
	return interval;
}



int main(int argc,char* argv[])
{
  Init();
  
  
  GraphicsFrameWork *g = new GraphicsFrameWork(ren,window);

  
  
//SDL_TimerID timer = SDL_AddTimer(100, callback, NULL);//创立定时器timer 

 	
 	
  
  while (gameOver == false) {




SDL_Event gameEvent;       






while ( SDL_PollEvent(&gameEvent) != 0 ){  /*　SDL_PollEvent(&gameEvent);  if(&gameEvent != 0 ){　*/

  if (gameEvent.type == SDL_QUIT) {

    gameOver = true;
  }

  
}

home->logic();
home->update(g);


  }


  
	return 0;
}