#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Pong raylib");

  Rectangle player = {50, screenHeight / 2 - 40, 20, 80};

  Rectangle bot = {screenWidth - 70, screenHeight / 2 - 40, 20, 80};

  Vector2 ballPosition = {screenWidth / 2, screenHeight / 2};
  Vector2 ballSpeed = {4.0f, 4.0f};
  float ballRadius = 10;

  int playerScore = 0;
  int botScore = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_W))
      player.y -= 5.0f;
    if (IsKeyDown(KEY_S))
      player.y += 5.0f;

    if (player.y < 0)
      player.y = 0;
    if (player.y + player.height > screenHeight)
      player.y = screenHeight - player.height;

    if (ballPosition.y < bot.y + bot.height / 2)
      bot.y -= 4.0f;
    if (ballPosition.y > bot.y + bot.height / 2)
      bot.y += 4.0f;

    if (bot.y < 0)
      bot.y = 0;
    if (bot.y + bot.height > screenHeight)
      bot.y = screenHeight - bot.height;

    ballPosition.x += ballSpeed.x;
    ballPosition.y += ballSpeed.y;

    if (ballPosition.y - ballRadius <= 0 ||
        ballPosition.y + ballRadius >= screenHeight)
      ballSpeed.y *= -1;

    if (CheckCollisionCircleRec(ballPosition, ballRadius, player) ||
        CheckCollisionCircleRec(ballPosition, ballRadius, bot)) {
      ballSpeed.x *= -1;
      ballSpeed.x *= 1.05f;
      ballSpeed.y *= 1.05f;
    }

    if (ballPosition.x - ballRadius < 0) {
      botScore++;
      ballPosition = {screenWidth / 2, screenHeight / 2};
      ballSpeed = {4.0f, 4.0f};
    }

    if (ballPosition.x + ballRadius > screenWidth) {
      playerScore++;
      ballPosition = {screenWidth / 2, screenHeight / 2};
      ballSpeed = {-4.0f, 4.0f};
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText("PONG raylib", screenWidth / 2 - 100, 10, 20, LIGHTGRAY);

    DrawText(TextFormat("Jogador: %i", playerScore), 10, 40, 20, WHITE);
    DrawText(TextFormat("Bot: %i", botScore), screenWidth - 150, 40, 20, WHITE);

    DrawRectangleRec(player, WHITE);
    DrawRectangleRec(bot, WHITE);
    DrawCircleV(ballPosition, ballRadius, RED);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
