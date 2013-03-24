//
//  Game.h
//  Tetris
//
//  Created by Fielding Johnston on 3/18/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__Game__
#define __Tetris__Game__

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Constants.h"
#include "Board.h"
#include "Timer.h"
#include "Block.h"
#include "Tetrimino.h"
#include "Bag.h"


using namespace std;



// Tetris Board Attributes

class Game
{

public:
  // Constructor/Destructor
  Game();
  ~Game();
  
  // public functions
  int start();

private:
  Board *myBoard;
  Tetrimino *aTetrimino; //activeTetrimino
  Tetrimino *nTetrimino; //nextTetrimino
  Tetrimino *hTetrimino; //heldTetrimino
  Tetrimino *bTetrimino; //bufferTetrimino for exhanges
  
  Timer globalTimer;
  Timer playTimer;
  Timer fps;
  Timer update;
  
  Bag* bag;
  
  std::deque<int> queue;

  enum GameState { Menu, Playing, GameOver, Paused };
  char *gameStateNames[4] = { "Menu", "Playing", "GameOver", "Paused" };
  enum type_t { active, fixed, next, held };

  int gameState;
  int previousGameState;
  bool quit;
  bool holdUsed;
  

  void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL );
  void clean_up();
  void drawBlock( Block block, int type, int xOffset = 0, int yOffset = 0 );
  void drawBoard();
  void drawNextContainer();
  void drawHeldContainer();
  void drawActiveTetrimino();
  void drawNextTetrimino(int whichTetrimino);
  void drawTetriminoQueue();
  void drawHeldTetrimino();
  bool init();
  void interfaceInput();
  bool load_files();
  void movementInput();
  void storeTetrimino();
  bool isGameOver();
  int checkLines();
  bool lineIsFull( int y );
  void deleteLine( int y );
  void dropLines( int y );
  void displayText(string text, Sint16 x, Sint16 y, Uint8 fgR, Uint8 fgG, Uint8 fgB, Uint8 bgR, Uint8 bgG, Uint8 bgB);
  void displayTimer(int time, int x, int y);
  bool updateScreen();
  void drawInterface();
  void holdTetrimino();
  void nextTetrimino();
  void fillQueue();
  void startCountdown();
  
  
  SDL_Surface *load_image( string filename );
  
  // Surfaces
  SDL_Surface *screen = NULL;
  SDL_Surface *background = NULL;
  SDL_Surface *boardSurface = NULL;
  SDL_Surface *boardTile = NULL;
  SDL_Surface *boardOutline = NULL;
  
  // Surfaces for block images
  SDL_Surface *cyanBlock = NULL;
  SDL_Surface *blueBlock = NULL;
  SDL_Surface *orangeBlock = NULL;
  SDL_Surface *yellowBlock = NULL;
  SDL_Surface *greenBlock = NULL;
  SDL_Surface *purpleBlock = NULL;
  SDL_Surface *redBlock = NULL;
  
  // Message Surfaces
  SDL_Surface *startStop = NULL;
  SDL_Surface *pauseMessage = NULL;
  SDL_Surface *mainMessage = NULL;
  SDL_Surface* interfaceMessageGameOver;
  SDL_Surface* interfaceMessagePaused;
  
  SDL_Surface* interfaceMenu;
  
  // Event Structure
  SDL_Event event;
  
  // default font, font fg color and font bg color
  TTF_Font *font = NULL;
  SDL_Color fontFgColor = { 0, 0, 0 };
  SDL_Color fontBgColor = { 255, 255, 255 };
  
};


#endif /* defined(__Tetris__Game__) */
