#include <iostream>
#include <armadillo>
#include <SDL2/SDL.h>

using namespace std;
using namespace arma;



class Array
{
public:
  int x, y;
  int dx, dy;
  int xMove = 5;
  int yMove = 5;
  const int n = 80;
  const int w = 640;
  const int h = 640;
  enum direction {STOP=0, LEFT, RIGHT, UP, DOWN};
  direction dir;
  mat m;
  SDL_Rect col;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

  Array()
  {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Test", 0, 0, w, h, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    dir = STOP;
    m = zeros<mat>(n, n);
    dx = w / n;
    dy = h / n;
  }

  ~Array()
  {
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void setup()
  {
    m(0,0) = 1;
    drawArray();
  }

  int getX()
  {
    return xMove;
  }

  int logic()
  {
    if(xMove < 1 or xMove > n-2 or yMove < 1 or yMove > n-2)
      {
	return 1;
      }
    else
      {
	m(xMove, yMove) = 0;
	switch(dir)
	  {
	  case UP:
	    yMove--;
	    break;
	  case DOWN:
	    yMove++;
	    break;
	  case LEFT:
	    xMove--;
	    break;
	  case RIGHT:
	    xMove++;
	    break;
	  }
	m(xMove, yMove) = 1;
	return 0;
      }
  }


  int game()
  {
    while(SDL_PollEvent(&event))
      {
	switch(event.type)
	  {
	  case SDL_KEYDOWN:
	    switch(event.key.keysym.sym)
	      {
	      case SDLK_DOWN:
		dir = DOWN;
		return 0;
		break;
	      case SDLK_UP:
		dir = UP;
		return 0;
		break;
	      case SDLK_LEFT:
		dir = LEFT;
		return 0;
		break;
	      case SDLK_RIGHT:
		dir = RIGHT;
		return 0;
		break;
	      }
	  case SDL_QUIT:
	    return 1;
	    break;
	  }
      }
  }
  
  void drawArray()
  /**
     Draw each != 0 element of an array with red.
   */
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    for(int i = 0; i < n; i++)
      {
	for(int j = 0; j < n; j++)
	  {
	    x = i*dx;
	    y = j*dy;
	    if(m(i,j) != 0)
	      {
		col.x = x;
		col.y = y;
		col.w = dx;
		col.h = dy;
		SDL_SetRenderDrawColor(
				       renderer, 255, 0, 0,
				       SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &col);
	      }
	  }
      }
    SDL_RenderPresent(renderer);
  }
  
}; // End of class definition



// ----- MAIN -----
int main()
{
  Array a;
  // a.setup();

  SDL_Event event;
  int gameOver = 0;

  while(gameOver == 0)
    {
      gameOver = a.game();
      gameOver = a.logic();
      a.drawArray();
      SDL_Delay(50);
    }

  SDL_Delay(100);
  cout << "Game over" << endl;
  return 0;
}

