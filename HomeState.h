
#include <SDL2/SDL.h>
#include "GraphicsFrameWork.h"
class HomeState {
	
	public :
          HomeState();
          void logic();
          void update(GraphicsFrameWork *g);

        private:
          float button_size=250;
          bool animate_flag = true;
          
          
};