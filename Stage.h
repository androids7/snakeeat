//#pragma once


#ifndef STAGE_H
#define STAGE_H


#include "GraphicsFrameWork.h"
#include "Context.h"

public  class Stage {

public:
  Stage(Context *ctx);
  virtual void logic();
  virtual void update(GraphicsFrameWork *g);
  
 private:
   Context *context;
};
  
  #endif