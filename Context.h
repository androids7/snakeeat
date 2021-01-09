#pragma once
#include "GraphicsFrameWork.h"
//#include "Stage.h"
#include <SDL2/SDL.h>


#include "HashFuncEqualKey.h"
#include "HashMap.h"

class Context;
class Stage;

typedef  HashMap<string, Stage*, HashFunc, EqualKey> StageMap;
                
                



class Context {
	public:
          Context(SDL_Renderer *ren,SDL_Window *win);
                void addStage(char *stageName,Stage *stage);
                void removeStage(char *stageName);//移除并释放场景
                void setStage(char *stageName);//显示场景

                void loop();//
                
                
            //    Uint32 callback(Uint32 interval, void *param); //回调函数
              private:
                SDL_Renderer *_ren;
                SDL_Window *_win;
                
            
                
};



//#include "GraphicsFrameWork.h"
//#include "Context.h"

class Stage {

public:
  Stage(Context *ctx);
  virtual void logic();
  virtual void update(GraphicsFrameWork *g);
  
 private:
   Context *context;
 
   
   
};
  
 




