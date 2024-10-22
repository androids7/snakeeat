#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
SDL_Texture *t_snakeBody = NULL;
SDL_Texture *t_blackbord = NULL;
SDL_Texture * t_block = NULL;
SDL_Texture * t_food = NULL;
SDL_Texture * t_snakeUp = NULL;
SDL_Texture * t_snakeDown = NULL;
SDL_Texture * t_snakeLeft = NULL;
SDL_Texture * t_snakeRight = NULL;
SDL_Texture * t_begin = NULL;

enum direct {Up,Down,Left,Right};//枚举方向
const int MAX_LENGTH = 40;//蛇最大长度
const int RECT_SIZE = 50;//小原件的大小

struct Snake//蛇结构体
{
	int x;//每部分的横坐标
	int y;//每部分的纵坐标
	direct dir;//蛇头方向
	bool flag;//蛇的生死
	int length;//蛇的长度
}snake[MAX_LENGTH];

Snake food;//通过蛇结构体创建食物变量，因为蛇的结构体中包含食物结构体的所有成员，所以可以这样简化

void Init( void );//初始化
void Quit( void );//退出
void Clear( void );//清除屏幕
void Show( void );//显示绘图
void DrawBackGround( void ){SDL_RenderCopy(render,t_blackbord,NULL,NULL);}
void DrawWall( void );//画墙
void DrawSnake( void );//画蛇
void Move( void );//蛇的移动
void Speed(int speed){SDL_Delay(300-speed*40);}//蛇的爬行速度
void DrawFood( void );//画出食物
void Contral( void );//控制蛇头
void Eat( void );//吃食物
void Die( void );//蛇死掉
void GameOver( void );//游戏结束界面
void Score( int );//显示分数
void Text(char* ,int , int , int ,int,int,int );//显示文字
void Begin( void );//游戏开始界面

int main(int argc,char* argv[])
{
	Init();
	Begin();
	while (snake[0].flag == true )
	{
		Clear();
		Contral();
		DrawBackGround();
		DrawWall();
		DrawFood();
		Move();
		Eat();
		Die();
		DrawSnake();
		Score(snake[0].length);
		Show();
		Speed(snake[0].length/2);//蛇每增加4的时候速度增大一次，达到最大长度40时速度达到最大
	}
	GameOver();
	atexit(Quit);
	return 0;
}

void Init( void )
{
	//图形的初始化
	window = SDL_CreateWindow("Snake",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,600,480,SDL_WINDOW_RESIZABLE);
	render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
	TTF_Init();
	
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	t_snakeBody = IMG_LoadTexture(render,"./assets/body.png");
	t_blackbord = IMG_LoadTexture(render,"./assets/blackbord.png");
	t_block = IMG_LoadTexture(render,"./assets/block.jpg");
	t_food = IMG_LoadTexture(render,"./assets/food.png");
	t_snakeUp = IMG_LoadTexture(render,"./assets/head_up.png");
	t_snakeDown = IMG_LoadTexture(render,"./assets/head_down.png");
	t_snakeLeft = IMG_LoadTexture(render,"./assets/head_left.png");
	t_snakeRight = IMG_LoadTexture(render,"./assets/head_right.png");
	t_begin = IMG_LoadTexture(render,"./assets/begin.png");
	
	//蛇的初始化
	snake[0].length = 2;
	snake[0].x = 150;
	snake[0].y = 150;
	snake[1].x = 150-RECT_SIZE;
	snake[1].y = 150;
	snake[0].dir = Right;
	snake[0].flag = true;
	
	//食物的初始化
	food.flag = false;
	srand(time(NULL));
}

void Quit( void )
{
	SDL_DestroyTexture(t_snakeBody);
	SDL_DestroyTexture(t_blackbord);
	SDL_DestroyTexture(t_block);
	SDL_DestroyTexture(t_food);
	SDL_DestroyTexture(t_begin);
	
	SDL_DestroyTexture(t_snakeUp);
	SDL_DestroyTexture(t_snakeDown);
	SDL_DestroyTexture(t_snakeLeft);
	SDL_DestroyTexture(t_snakeRight);
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Clear( void )
{
	SDL_RenderClear(render);
}

void Show( void )
{
	SDL_RenderPresent(render);
}

void DrawWall( void )
{
	int w,h;
	SDL_Rect wallRect;
	wallRect.y = 0;
	wallRect.x = 0;
	wallRect.w = RECT_SIZE;
	wallRect.h = RECT_SIZE;
	SDL_GetWindowSize(window,&w,&h);
	
	for (int i = 0;i<w;i+=RECT_SIZE)
	{
		wallRect.x = i;
		wallRect.y = 0;
		
		SDL_RenderCopy(render,t_block,NULL,&wallRect);
		wallRect.y = h - RECT_SIZE;
		SDL_RenderCopy(render,t_block,NULL,&wallRect);
	}
	
	for (int i = 0; i<h;i+=RECT_SIZE)
	{
		wallRect.y = i;
		wallRect.x = 0;
		
		SDL_RenderCopy(render,t_block,NULL,&wallRect);
		wallRect.x = w - RECT_SIZE;
		
		SDL_RenderCopy(render,t_block,NULL,&wallRect);
	}
}

void DrawSnake( void )
{
	SDL_Rect snakeRect;
	snakeRect.w = RECT_SIZE;
	snakeRect.h = RECT_SIZE;
	
	//画蛇头
	snakeRect.x = snake[0].x;
	snakeRect.y = snake[0].y;
	switch (snake[0].dir)
	{
		case Up:
		SDL_RenderCopy(render,t_snakeUp,NULL,&snakeRect);
		break;
		case Down:
		SDL_RenderCopy(render,t_snakeDown,NULL,&snakeRect);
		break;
		case Left:
		SDL_RenderCopy(render,t_snakeLeft,NULL,&snakeRect);
		break;
		case Right:
		SDL_RenderCopy(render,t_snakeRight,NULL,&snakeRect);
		break;
	}
	//画蛇的身子
	for (int i = 1;i<snake[0].length;i++)
	{
		snakeRect.x = snake[i].x;
		snakeRect.y = snake[i].y;
		SDL_RenderCopy(render,t_snakeBody,NULL,&snakeRect);
	}
}

void Move( void )
{
	for (int i = snake[0].length-1; i>0; i--)
	{
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}
	
	switch (snake[0].dir)
	{
		case Up:
		snake[0].y-=RECT_SIZE;
		break;
		case Down:
		snake[0].y+=RECT_SIZE;
		break;
		case Left:
		snake[0].x-=RECT_SIZE;
		break;
		case Right:
		snake[0].x+=RECT_SIZE;
		break;
	}
}

void DrawFood( void )
{
	int w,h;
	bool flag = true;
	SDL_Rect foodRect;
	foodRect.w = RECT_SIZE;
	foodRect.h = RECT_SIZE;
	SDL_GetWindowSize(window,&w,&h);
	if (food.flag == false )
	{
		food.x = (rand()%(w/RECT_SIZE-2)+1)*RECT_SIZE;
		food.y = (rand()%(h/RECT_SIZE-2)+1)*RECT_SIZE;
		
		for (int i = 0; i <snake[0].length ; i ++ )
		{
			if (food.x == snake[0].x && food.y == snake[0].y)
			{
				flag = false;
			}
		}
		
		if (flag == true )
		{
			food.flag = true;
		}
	}
	
		foodRect.x = food.x;
		foodRect.y = food.y;
		
		SDL_RenderCopy(render,t_food,NULL,&foodRect);
}

void Contral( void )
{
	SDL_Event event;
	double move_x,move_y;
	while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_FINGERMOTION)
				// 当事件为触屏
			{
				move_x = event.tfinger.dx;
				move_y = event.tfinger.dy;
				if (fabs(move_x) - fabs(move_y) >=0.005)
				{
					if (move_x > 0 && snake[0].dir != Left && snake[0].dir != Right)
						snake[0].dir = Right;
					else if (move_x < 0 && snake[0].dir != Right && snake[0].dir != Left)
						snake[0].dir = Left;
				}
				else if (fabs(move_y) - fabs(move_x) > 0.005)
				{
					if (move_y > 0 && snake[0].dir != Up && snake[0].dir != Down)
						snake[0].dir = Down;
					else if (move_y < 0 && snake[0].dir != Down && snake[0].dir != Up)
						snake[0].dir = Up;
				}
			}
			
			else if (event.type == SDL_KEYDOWN )
			//当事件为键盘
			{
				switch (event.key.keysym.sym) 
				{
					case SDLK_UP:
					snake[0].dir = Up;
					break;
					case SDLK_DOWN:
					snake[0].dir = Down;
					break;
					case SDLK_LEFT:
					snake[0].dir = Left;
					break;
					case SDLK_RIGHT:
					snake[0].dir = Right;
					break;
				}
			}
		}
}

void Eat( void )
{
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		food.flag = false;
		snake[0].length ++;
		
		//这两行是BUG修复，修复每次吃到食物后在屏幕左上角出现一节蛇的BUG
		snake[snake[0].length-1].x = snake[snake[0].length-2].x;
		snake[snake[0].length-1].y = snake[snake[0].length-2].y;
	}
}

void Die( void )
{
	int w,h;
	SDL_GetWindowSize(window,&w,&h);
	for (int i = 1 ; i < snake[0].length ; i ++ )
	{
		if (snake[i].x == snake[0].x && snake[i].y ==snake[0].y)
		{
			snake[0].flag = false;
		}
	}
	
	if (snake[0].x < RECT_SIZE || snake[0].x > w - RECT_SIZE*2 || snake[0].y < RECT_SIZE || snake[0].y > h - RECT_SIZE*2)
	{
		snake[0].flag = false;
	}
}

void GameOver( void )
{
	Clear();
	Text("游戏结束",300,600,60,rand()%255,rand()%255,rand()%255);
	Show();
	SDL_Delay(2000);
}

void Score( int score )
{
	int f_w,f_h;
	char s_score[9];
	SDL_Color color{255,255,0,0};
	SDL_Rect fontRect;
	
	sprintf(s_score,"身长:%d",score);
	TTF_Font *l_font = TTF_OpenFont("./assets/font.ttf",30);
	SDL_Surface *s_font = TTF_RenderUTF8_Blended(l_font,s_score,color);
	SDL_Texture *t_font = SDL_CreateTextureFromSurface(render,s_font);
	SDL_QueryTexture(t_font,NULL,NULL,&f_w,&f_h);
	fontRect.x = 30;
	fontRect.y = 30;
	fontRect.w = f_w;
	fontRect.h = f_h;
	SDL_RenderCopy(render,t_font,NULL,&fontRect);
}

void Text(char *t,int x,int y,int size,int r,int g,int b)
{
	int f_w,f_h;
	SDL_Color color{r,g,b,0};
	SDL_Rect fontRect;
	
	TTF_Font *l_font = TTF_OpenFont("./assets/font.ttf",size);
	SDL_Surface *s_font = TTF_RenderUTF8_Blended(l_font,t,color);
	SDL_Texture *t_font = SDL_CreateTextureFromSurface(render,s_font);
	SDL_QueryTexture(t_font,NULL,NULL,&f_w,&f_h);
	fontRect.x = x;
	fontRect.y = y;
	fontRect.w = f_w;
	fontRect.h = f_h;
	SDL_RenderCopy(render,t_font,NULL,&fontRect);
}

void Begin( void )
{
	Clear();
	for (int i =0;i<10;i++)
	{
	SDL_RenderCopy(render,t_begin,NULL,NULL);
	
	Text("androids7",430,600,90,rand()%255,rand()%255,rand()%255);

	Text("贪吃蛇测试",430,400,90,rand()%255,rand()%255,rand()%255);
	
		Text("power by SDL2",300,1000,90,rand()%255,rand()%255,rand()%255);


	
	
	Show();
	SDL_Delay(200);
	}
}