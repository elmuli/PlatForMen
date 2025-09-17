#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void LoadPlayerTexture(struct Player *player, SDL_Renderer *renderer) {
  SDL_Surface *Surface = SDL_LoadBMP("img/playerBMP.bmp");
  if (Surface == NULL) {
    printf("Could not load player bmp\n");
    return;
  }
  player->playerTex = SDL_CreateTextureFromSurface(renderer, Surface);
  SDL_DestroySurface(Surface);
}

void SetPlayerRect(struct Player *player, int w, int h) {
  player->playerRect.x = (float)player->PosX;
  player->playerRect.y = (float)player->PosY;

  player->playerRect.w = (float)w;
  player->playerRect.h = (float)h;
}

void UpdatePlayerPos(struct Player *player, int x, int y) {
  player->PosX += x;
  player->PosY += y;

  player->playerRect.x = player->PosX;
  player->playerRect.y = player->PosY;
}

void RenderPlayer(struct gameState *GS, SDL_Renderer *renderer) {
  SDL_RenderTexture(renderer, GS->player.playerTex, NULL, &GS->player.playerRect);
}

void GetPlayerInput(SDL_Event *event, struct gameState *GS, const bool *keys) {

  int speed = 5;

  SDL_PumpEvents();

  if (keys[SDL_SCANCODE_W]) {
    UpdatePlayerPos(&GS->player, 0, -speed);
  }
  if (keys[SDL_SCANCODE_S]) {
    UpdatePlayerPos(&GS->player, 0, speed);
  }
  if (keys[SDL_SCANCODE_D]) {
    UpdatePlayerPos(&GS->player, speed, 0);
  }
  if (keys[SDL_SCANCODE_A]) {
    UpdatePlayerPos(&GS->player, -speed, 0);
  }
}

void LoadMapTexture(SDL_Texture *texture, SDL_Renderer *renderer){
  SDL_Surface *Surface = IMG_Load("img/Map.png");
  if (Surface == NULL) {
    printf("Could not load Map img\n");
    return;
  }
  texture = SDL_CreateTextureFromSurface(renderer, Surface);
  SDL_DestroySurface(Surface);
}

void CleanUp(struct gameState *GS){
  SDL_DestroyTexture(GS->player.playerTex);
  SDL_DestroyTexture(GS->MapTexture);
}
