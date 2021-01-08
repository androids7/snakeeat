//主页界面

#include "HomeState.h"

int i = 0;
char *str;
HomeState::HomeState() {

  str = (char *)malloc(256);
	
	
	}




void HomeState::logic() {
	//变小
	
	
	if(animate_flag==true){
          if (button_size > 180) {

            button_size -= 2;
            ;
          } else {
            animate_flag = false;
          }
        }
      if  (animate_flag==false){ 
      if(button_size <250) {

          button_size+=2;
      } else {
        animate_flag = true;
      }
      }
        
	
	}
void HomeState::update(GraphicsFrameWork *g) {

//  i++;
 // sprintf(str, "%d", i);
  
  
//  g->Clear();
g->Cls(0, 0, 0);
//g->Text(str, 250, 300, 200, 255, 255,        255);

g->Text("贪食蛇", 250, 300, 200, 255, 255, 255);
g->Text("Power By SDL2", 400,g->getSCRH()-200, 40, 255, 255,
        0);
 // g->DrawPoint(200, 200,  255, 0,0);
g->FillCir(g->getSCRW()/2, g->getSCRH()/1.5, button_size, 255, 0,0);
//    g->DrawCir(g->getSCRW()/2,g->getSCRH()/1.5, button_size,0x00ff0000);

g->Text("开始游戏", g->getSCRW()/3, g->getSCRH()/1.548, 56*300/button_size, 255, 255,
        255);
    
  g->Show();
	}