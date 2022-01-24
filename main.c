#include <raylib.h>
#include "pong.h"

static const int screenWidth = 800;
static const int screenHeight = 600;

typedef struct Paddle {
  Vector2 pos;
  Color color;
  Vector2 size;
  int speed;
} Paddle;

typedef struct Ball {
  Vector2 pos;
  Vector2 size;
  Color color;
} Ball;

typedef struct Game {
  Paddle leftPaddle;
  Paddle rightPaddle;
  Ball ball;
} Game;

void drawPaddle(Paddle paddle){
  DrawRectangleV(paddle.pos , paddle.size, paddle.color);
}

void initGame(Game *game) {
  game->leftPaddle.size.x = PADDLE_WIDTH;
  game->leftPaddle.size.y = PADDLE_HEIGHT;

  game->leftPaddle.pos.x = PADDLE_POS_X;
  game->leftPaddle.pos.y = PADDLE_POS_Y;
  game->leftPaddle.speed = 5;

  game->leftPaddle.color = RED;

  game->rightPaddle.size.x = PADDLE_WIDTH;
  game->rightPaddle.size.y = PADDLE_HEIGHT;
  game->rightPaddle.pos.x = SCREEN_WIDTH - PADDLE_POS_X - PADDLE_WIDTH;
  game->rightPaddle.pos.y = PADDLE_POS_Y;
  game->rightPaddle.speed = 5;

  game->rightPaddle.color = BLUE;

}

void updateGame(Game *game) {
  Paddle *leftPaddle = &game->leftPaddle;
  Paddle *rightPaddle = &game->rightPaddle;
  drawPaddle(*leftPaddle);
  drawPaddle(*rightPaddle);

  //check for left paddle keys
  if (IsKeyDown(KEY_W)) {
    leftPaddle->pos.y -= leftPaddle->speed;
  } else if (IsKeyDown(KEY_S)) {
    leftPaddle->pos.y += leftPaddle->speed;
  }
  //Check for right paddle keys 
  if (IsKeyDown(KEY_UP)) {
    rightPaddle->pos.y -= rightPaddle->speed;
  } else if (IsKeyDown(KEY_DOWN)) {
    rightPaddle->pos.y += rightPaddle->speed;
  }
}

int main (int argc, char *argv[])
{
  InitWindow(screenWidth , screenHeight , "Pong");
  Game game;
  initGame(&game);

  SetTargetFPS(30);
  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    updateGame(&game);
    EndDrawing();
  }
  
  return 0;
}
