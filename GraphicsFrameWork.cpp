#include "GraphicsFrameWork.h"

using namespace std;

GraphicsFrameWork::GraphicsFrameWork(SDL_Renderer *ren,SDL_Window *win) {
  _ren = ren;
  _win = win;
	
	
SDL_GetWindowSize(_win, &SCRW, &SCRH);

	
	
	
	}
void GraphicsFrameWork::Text(char *t,int x,int y,int size,int r,int g,int b)
{
	int f_w,f_h;
        SDL_Color color{(Uint8)r, (Uint8)g, (Uint8)b, 0};
        SDL_Rect fontRect;

        TTF_Font *l_font = TTF_OpenFont("./assets/font.ttf", size);
        SDL_Surface *s_font = TTF_RenderUTF8_Blended(l_font, t, color);
        SDL_Texture *t_font = SDL_CreateTextureFromSurface(_ren, s_font);
        SDL_QueryTexture(t_font, NULL, NULL, &f_w, &f_h);
        fontRect.x = x;
        fontRect.y = y;
        fontRect.w = f_w;
        fontRect.h = f_h;
        SDL_RenderCopy(_ren, t_font, NULL, &fontRect);
        SDL_FreeSurface(s_font);
        SDL_DestroyTexture(t_font);
        TTF_CloseFont(l_font);
        
}




void   GraphicsFrameWork::gr_point(int x, int y, int color) {

            //	Uint8 alpha = (color & 0xff000000) >> 24;
            Uint8 r = (color & 0x00ff0000) >> 16;
            Uint8 g = (color & 0x0000ff00) >> 8;
            Uint8 b = (color & 0x000000ff);
            DrawPoint(x, y, r, g, b);
          }

/*
void GraphicsFrameWork::FillCir(int x0, int y0, int r, int color) {

	for (int i = r; i > 0; i--) {
		DrawCir(x0, y0, i, color);
	}
}
*/

//圆的半径不同，绘制时间也不同！精确度自动计算。
void GraphicsFrameWork::FillCir
(int x,int y,int r0, int r,int g,int b)
{
	int k=0,xx,yy,n=6*(r0+1)/4;

        SDL_SetRenderDrawColor(_ren, r,g, b, 255);
        while (k <= n) {
          xx = ((n * n - k * k) * r0) / (n * n + k * k) + x;
          yy = 2 * n * k * r0 / (n * n + k * k) + y;

          SDL_RenderDrawLine(_ren,xx, yy, xx, 2 * y - yy);
          SDL_RenderDrawLine(_ren,2 * x - xx, yy, 2 * x - xx, 2 * y - yy);
          // mrc_refreshScreen(xx,2*y-yy,1,2*(yy-y));
          // mrc_refreshScreen(2*x-xx,2*y-yy,1,2*(yy-y));
          k += 1;
        }
        
        
        
}

void GraphicsFrameWork::DrawLines(SDL_Point *point,int count, int r, int g, int b) {

  SDL_SetRenderDrawColor(_ren, (Uint8)r, (Uint8)g,
                         (Uint8)b, 255);
  SDL_RenderDrawLines(_ren, point,
                      count);
	}


void DrawCircle(SDL_Renderer *ren,int radius){
    using std::cout;
    using std::clock;
    using std::endl;
    int st=clock(),tx=0,ty=radius,d=3-(radius<<1),x=radius,y=radius;
	while(tx<ty){
		for (int i=x-ty;i<=x+ty;++i){
			SDL_RenderDrawPoint(ren,i,y-tx);
			if (tx)
				SDL_RenderDrawPoint(ren,i,y+tx);
		}
		if (d<0)
			d+=(tx<<2)+6;
		else{
			for (int i=x-tx;i<=x+tx;++i){
                SDL_RenderDrawPoint(ren,i,y-ty);
				SDL_RenderDrawPoint(ren,i,y+ty);
			}
			d+=((tx - ty)<<2)+10,ty--;
		}
		tx++;
	}
	if (tx==ty)
		for (int i=x-ty;i<=x+ty;++i){
                SDL_RenderDrawPoint(ren,i,y-tx);
				SDL_RenderDrawPoint(ren,i,y+tx);
		}
    int en=clock();
    cout<<"Drawing Circle(radius "<<radius<<" pixels),costs:"<<en-st<<"ms"<<endl;
}



SDL_Texture * GraphicsFrameWork::CreateCircleTexture(double radius,int r,int g,int b){

  SDL_Color color = {(Uint8)r,(Uint8) g, (Uint8)b, 255};
	
    SDL_Texture *tex=SDL_CreateTexture(_ren,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,(int)(2*radius),(int)(2*radius));
    SDL_SetTextureBlendMode(tex,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(_ren,100,200,100,70);
    SDL_SetRenderTarget(_ren,tex);
    SDL_RenderClear(_ren);
    SDL_SetRenderDrawColor(_ren,color.r,color.g,color.b,255);
    DrawCircle(_ren,radius);
    SDL_SetRenderTarget(_ren,NULL);
    return tex;
}




void GraphicsFrameWork::DrawCir(int x0, int y0, int r, int color)
{
	//使用正负法画圆
	int x, y, f;//(x,y)为当前坐标 f为误差值

	x = x0;
	y = y0 + r;
	f = 0;

	while (y >= y0) {//从圆周的右上部分开始
		gr_point(x, y, color);//对称地画出四个象限内的坐标点
		gr_point(2 * x0 - x, y, color);
		gr_point(x, 2 * y0 - y, color);
		gr_point(2 * x0 - x, 2 * y0 - y, color);

		if (f > 0) {
			f = f - 2 * (y - y0) + 1;
			y--;//向圆内走
                } else {
                  f = f + 2 * (x - x0) + 1;
                  x++; //向圆外走
                }
        }

        if (y == y0)
          gr_point(x, y, color);
}

void GraphicsFrameWork::DrawPoint(int x,int y,int r, int g,
                                  int b) {
  
  
  SDL_SetRenderDrawColor(_ren,r,g,b, 255);
   SDL_RenderDrawPoint(_ren, x, y);


  
                                  	}
void GraphicsFrameWork::Cls(int r ,int g,int b){



  SDL_Rect rect = {0, 0, SCRW, SCRH};
  SDL_SetRenderDrawColor(_ren, r, g,
                         b, 255);
  SDL_RenderFillRect(_ren, &rect);
}

int GraphicsFrameWork::getSCRW() { return SCRW; }
int GraphicsFrameWork::getSCRH() {  return SCRH; }





void GraphicsFrameWork::Clear( void )
{
	SDL_RenderClear(_ren);
}

void GraphicsFrameWork::Show(void) { SDL_RenderPresent(_ren); }