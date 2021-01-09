//主页界面

#include "HomeStatge.h"

#include <vector>
#include <math.h>
using namespace std;
//std::vector<SDL_Point *> *heartdata;


HomeStatge::HomeStatge() {

//  heartdata = new SDL_Point[600];
  //heartdata = new std::vector<SDL_Point*>();
  
	}

void HomeStatge::logic() {
	//变小
	
	
	if(animate_flag==true){
          if (button_size > 195) {

            button_size -= 0.8 * pow(1.2,2) / 2;
            ;
            ;
          } else {
            animate_flag = false;
          }
        }
      if  (animate_flag==false){ 
      if(button_size <250) {

        button_size += 0.8 * pow(2, 2) / 2;
      } else {
        animate_flag = true;
      }
      }
        /*
	for (int i = 0; i < 600; i++) {
		
	//	if(i%5==0){

                  SDL_Point p = {i, getDeltaData( 500,  1000)};

                  heartdata[i] = p;
          //      }else{
             //     SDL_Point p = {0,250};

     //             heartdata[i] = p;
       //         }
                	
        //  heartdata->push_back(&p);
        }
        
        */
        
	}
void HomeStatge::update(GraphicsFrameWork *g) {

//  i++;
 // sprintf(str, "%d", i);
  
  
//  g->Clear();
g->Cls(0, 0, 0);
//g->Text(str, 250, 300, 200, 255, 255,        255);

g->Text("贪食蛇", 250, 300, 200, 255, 255, 255);
g->Text("Power By SDL2", 400,g->getSCRH()-200, 40, 255, 255,
        0);
 // g->DrawPoint(200, 200,  255, 0,0);
 
 
 /*
// 注：如果参数为const vector<int> 需要用const_iterator
	
	
	
	std::vector<SDL_Point*>::iterator it = heartdata->begin();
	// vector<int>::const_iterator iter=v.begin();
	for(; it != heartdata->end(); ++it)
	{
		g->DrawLines(*it, 1, 255, 0,   0);
 
	}
*/
/*
for (int i = 0; i < 600; i++) {

  g->DrawLines(heartdata, 600, 255, 0,
               0);
}
*/
g ->FillCir(g->getSCRW()/2,g->getSCRH()/1.5, button_size+8,255,255,255);

 
g->FillCir(g->getSCRW()/2, g->getSCRH()/1.5, button_size, 255, 0,0);
 
g->Text("开始游戏", g->getSCRW()/2.18-pow(button_size/20,2), g->getSCRH()/1.533-button_size/10, 56*button_size/150, 255, 255,
        255);
    
  g->Show();
	}