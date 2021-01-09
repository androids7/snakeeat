#include "Context.h"

char *currentRenderName;
GraphicsFrameWork *g;
StageMap *map;
   


Uint32 callback(Uint32 interval, void *param)//回调函数 
{







  
  
//exit(1);


	return interval;
}




Context::Context(SDL_Renderer *ren,SDL_Window *win)
//:_ren(ren), _win(win){
	{
		
  //
  
  _ren = ren;
  _win = win;
  g = new GraphicsFrameWork(ren,win);
  
  
  map = new StageMap(100);
  currentRenderName =(char*) malloc(256);
  
//  SDL_TimerID timer = SDL_AddTimer(10, callback, NULL);//创立定时器timer 

 	
  
  
  
	}

        void Context::loop() {
        	
        	if (strlen(currentRenderName)>0&&g!=nullptr){
    Stage *stage = map->find(currentRenderName);
/*
    g->Cls(255,0,0);
    g->Text(currentRenderName, 100, 200, 46, 255, 255,255);
    g->Show();
    
   */
     stage->logic();
    stage->update(g);
    
//exit(1);
                } else {
                }
        	
        	}

        void Context::addStage(char *stageName, Stage *stage) {
          map->insert(stageName, stage);
        }

void Context::removeStage(char *stageName) //移除并释放场景
{
  map->del(stageName);
	
	}
void Context::setStage(char *stageName) //显示场景
{
  strcpy(currentRenderName, stageName);
	
	}

