//
//  PlayState.h
//  Tetris
//
//  Created by Fielding Johnston on 3/25/13.
//  Copyright (c) 2013 Fielding Johnston. All rights reserved.
//

#ifndef __Tetris__PlayState__
#define __Tetris__PlayState__

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

#include "GameEngine.h"
#include "GameState.h"
#include "AssetCache.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Constants.h"
#include "Board.h"
#include "Bag.h"
#include "Timer.h"
#include "Block.h"
#include "Tetrimino.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

class PlayState : public GameState
{
public:
  
  PlayState( GameEngine* game );
  ~PlayState();

  void Pause();
  void Resume();
  
  void HandleEvents(GameEngine* game);
  void Update(GameEngine* game);
  void Draw(GameEngine* game);

private:
  // Objects/Object Pointers
  Board* myBoard;
  
  Bag* bag;
  
  Tetrimino* aTetrimino;
  Tetrimino* nTetrimino;
  Tetrimino* hTetrimino;
  Tetrimino* bTetrimino;
  Tetrimino* gTetrimino;
  
  std::deque<int> queue; // used as Tetrimino queue
  
  Timer playTimer;

  SDL_Event event;
  // Uint8 *keystates = SDL_GetKeyState ( NULL ); // haven't decided if I'm going to use this yet
  
  // Surfaces
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
  SDL_Surface *ghostBlock = NULL;
  
  // Message Surfaces
  
  // default font, font fg color and font bg color
  TTF_Font *font = NULL;
  SDL_Color fontFgColor = { 255, 255, 255 };
  SDL_Color fontBgColor = { 13, 13, 13 };
  
  // Enum
  
  enum GameState { Menu, Playing, GameOver, Paused };
  char *gameStateNames[4] = { "Menu", "Playing", "GameOver", "Paused" };
  enum type_t { active, fixed, next, held, ghost };
  enum direction_t { left, right, down };

  // Variables
  bool holdUsed = false;
  bool forceLock = false;   // flag used to make hardDrops force a lock instantly, instead of waiting for lock time
  bool locking = false;
  
  int frame = 0;
  int startTime, endTime, lockStartTime = 0;
  int forceTime = 1000;           // 1sec force time starting out ( might need to adjust this in the future )
  int lockDelay = 300;  // need to figure out appropriate lockDelay for this
  
  int prevLinesCleared = 0;
  int linesCleared = 0;
  int linesAwarded = 0;
  
  int score = 0;
  
  int level = 1;
  int goal = 5;   // number of lines needed to advance a level ( a function of the level we are currently on )
  
  // variables for DAS implementationj
  int delayDown, delayLeft, delayRight = -1;
  long dasLastTime;

  
  // Functions
  
  // Functions: Rendering
  void displayGoal( GameEngine* game, int gl );
  void displayLevel( GameEngine* game, int lvl );
  void displayScore( GameEngine* game, int scr );
  void displayText(GameEngine* game, string text, Sint16 x, Sint16 y, Uint8 fgR, Uint8 fgG, Uint8 fgB, Uint8 bgR, Uint8 bgG, Uint8 bgB);
  void displayTimer(GameEngine* game, int time, int x, int y);
  void drawActiveTetrimino(GameEngine* game);
  void drawBlock(GameEngine* game, Block block, int type, int xOffset = 0, int yOffset = 0 );
  void drawBoard(GameEngine* game);
  void drawGhostTetrimino(GameEngine* game);
  void drawHeldTetrimino(GameEngine* game);
  void drawInterface(GameEngine* game);
  void drawNextContainer(GameEngine* game);
  void drawNextTetrimino(GameEngine* game, int whichTetrimino);
  void drawTetriminoQueue(GameEngine* game);
  bool loadAssets( GameEngine* game );
  
  // Functions: Input
  void interfaceInput(GameEngine* game);
  void movementInput();
  
  // Functions: Logic
  void addLineScore();
  int checkLines();
  bool checkLevelUp();
  void deleteLine( int y );
  void dropLines( int y );
  void fillQueue();
  int getLinesAwarded();
  void holdTetrimino();
  bool isGameOver();
  bool lineIsFull( int y );
  void nextTetrimino();
  void storeTetrimino();
  void reset();
  
};

#endif /* defined(__Tetris__PlayState__) */
