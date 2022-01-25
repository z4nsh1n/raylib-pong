#include <raylib.h>
#include "pong.h"

static const int screenWidth = 800;
static const int screenHeight = 600;

typedef struct Paddle {
  Color color;
  Rectangle rect;
  int speed;
} Paddle;

typedef struct Ball {
  Rectangle rect;
  Color color;
  Vector2 speed;
} Ball;

typedef struct Game {
  Paddle leftPaddle;
  Paddle rightPaddle;
  Ball ball;
  int left_score;
  int right_score;
} Game;

void drawPaddle(Paddle paddle){
  DrawRectangleRec(paddle.rect, paddle.color);
}

void drawBall(Ball ball) {
  DrawRectangleRec(ball.rect, ball.color);
}

void initBall(Ball *ball){
  ball->rect.width = BALL_SIZE;
  ball->rect.height = BALL_SIZE;
  ball->rect.x = (SCREEN_WIDTH - BALL_SIZE)/2;
  ball->rect.y = (SCREEN_HEIGHT - BALL_SIZE)/2;
  ball->color = BLACK;
  ball->speed.x = -5;
  ball->speed.y = 0;
}
void initGame(Game *game) {
  game->leftPaddle.rect.width = PADDLE_WIDTH;
  game->leftPaddle.rect.height = PADDLE_HEIGHT;

  game->leftPaddle.rect.x = PADDLE_POS_X;
  game->leftPaddle.rect.y = PADDLE_POS_Y;
  game->leftPaddle.speed = 5;

  game->leftPaddle.color = RED;

  game->rightPaddle.rect.width = PADDLE_WIDTH;
  game->rightPaddle.rect.height = PADDLE_HEIGHT;
  game->rightPaddle.rect.x = SCREEN_WIDTH - PADDLE_POS_X - PADDLE_WIDTH;
  game->rightPaddle.rect.y = PADDLE_POS_Y;
  game->rightPaddle.speed = 5;

  game->rightPaddle.color = BLUE;

  game->left_score = 0;
  game->right_score = 0;

  initBall(&(game->ball));


}

void updateGame(Game *game) {

  Paddle *leftPaddle = &game->leftPaddle;
  Paddle *rightPaddle = &game->rightPaddle;
  //check for left paddle keys
  if (IsKeyDown(KEY_W)) {
    leftPaddle->rect.y -= leftPaddle->speed;
  } else if (IsKeyDown(KEY_S)) {
    leftPaddle->rect.y += leftPaddle->speed;
  }
  //Check for right paddle keys 
  if (IsKeyDown(KEY_UP)) {
    rightPaddle->rect.y -= rightPaddle->speed;
  } else if (IsKeyDown(KEY_DOWN)) {
    rightPaddle->rect.y += rightPaddle->speed;
  }

  //Check border collisions
  if (
      game->ball.rect.y <= (0 + BALL_SIZE)||
      game->ball.rect.y >= (SCREEN_HEIGHT - BALL_SIZE) ) {

      game->ball.speed.y *= -1;
  }
  //Check paddle collisions
  if (
      CheckCollisionRecs(game->leftPaddle.rect, game->ball.rect) ||
      CheckCollisionRecs(game->rightPaddle.rect, game->ball.rect)) {
    game->ball.speed.x *= -1.2;
    game->ball.speed.y += GetRandomValue(-3, 3);
  }

  //check paddle positions
  if (game->leftPaddle.rect.y <= 0) game->leftPaddle.rect.y = 0;
  if (game->rightPaddle.rect.y <= 0) game->rightPaddle.rect.y = 0;
  if (game->leftPaddle.rect.y >= SCREEN_HEIGHT - PADDLE_HEIGHT) game->leftPaddle.rect.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
  if (game->rightPaddle.rect.y >= SCREEN_HEIGHT - PADDLE_HEIGHT) game->rightPaddle.rect.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    
  //check score
  if (game->ball.rect.x < PADDLE_POS_X) {
    initBall(&game->ball);
    game->right_score += 1;
  } else if (game->ball.rect.x > (SCREEN_WIDTH - PADDLE_POS_X)) {
    initBall(&game->ball);
    game->left_score += 1;
  }
  drawPaddle(*leftPaddle);
  drawPaddle(*rightPaddle);
  
  DrawText(
      TextFormat("%d | %d", game->left_score, game->right_score)
      , (SCREEN_WIDTH-100)/2, 20+10, 50, BLACK);

  game->ball.rect.x += game->ball.speed.x;
  game->ball.rect.y += game->ball.speed.y;

  drawBall(game->ball);
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
