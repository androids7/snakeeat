
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class GraphicsFrameWork{
  	
  	public :
          GraphicsFrameWork(SDL_Renderer *ren,SDL_Window * win);

          void Cls(int r, int g, int b);
          void Clear();
          
          
          void Show();
          void Text(char *t, int x, int y, int size, int r, int g, int b);
          void DrawPoint(int x1, int y1, int r, int g, int b);

          void DrawLines(SDL_Point *point,int count, int r, int g, int b);




          void gr_point(int x, int y, int color);

          void DrawCir(int x0, int y0, int r, int color);
          void FillCir(int x0, int y0, int r0, int r, int g, int b);
        //  void FillCir(int x0, int y0, int r, int color);

          SDL_Texture *CreateCircleTexture( double radius,
                                           int r,int g,int b);

          int getSCRW();
          int getSCRH();
          
          
          
          
  	private:
          SDL_Renderer *_ren;
          SDL_Window *_win;
          int SCRH;
          int SCRW;
          
  	};