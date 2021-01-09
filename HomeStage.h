
#include <SDL2/SDL.h>
#include "GraphicsFrameWork.h"
#include "Context.h"
class HomeStage :Stage{
	
	public :
          HomeStage(Context *ctx) : Stage(ctx) {}
          
          void logic();
          void update(GraphicsFrameWork *g);

        private:
          float button_size=250;
          bool animate_flag = true;
          
          
};