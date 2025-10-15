#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int widht = 900;
int hight = 700;
int isUp = 0;

struct gameState GS;

int main(int argc, char *argv[]){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  SDL_Window *window = SDL_CreateWindow("Platformer", widht, hight, 0);
  SDL_SetWindowResizable(window, true);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  SDL_Event windowEvent;

  const bool *keys = SDL_GetKeyboardState(NULL);

  printf("-Initialized SDL-\n");

  LoadBitmapTexture(&GS.player.playerTex, renderer, "img/playerBMP.bmp");

  printf("-Player loaded-\n");

  CreateTileMap(&GS, renderer);
  LoadMapTexture(&GS.TileMap.tileTexture, renderer);

  printf("-Map loaded-\n");

  GS.player.PosX = 50;
  GS.player.PosY = 100;

  SetPlayerRect(&GS.player, 60, 60);

  bool GameIsRunning = true;
  GS.player.hasJumped = 0;
  GS.player.timeJumped = 0;
  GS.player.jump = 0;
  GS.player.isGrounded = 0;

  while (GameIsRunning) {
    if (SDL_PollEvent(&windowEvent)) {
      if (SDL_EVENT_QUIT == windowEvent.type) {
        break;
      }
    }

    GetPlayerInput(&windowEvent, &GS, keys);
    
    if(CheckCollision(&GS)){
      GS.player.hasJumped = 0;
      GS.player.timeJumped = 0;
      GS.player.isGrounded = 1;
    }else if (!CheckCollision(&GS) && !GS.player.jump){
      UpdatePlayerPos(&GS.player, 0, 5);
    }

    if(GS.player.PosY > 600 && GS.TileMap.tileOffsetY > -100){
      GS.TileMap.tileOffsetY -= GS.player.PosY-600;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    DrawTileMap(&GS, renderer);
    RenderPlayer(&GS, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugTextFormat(renderer, 10, 10, "Jump: %i", GS.player.jump);
    SDL_RenderDebugTextFormat(renderer, 10, 25, "isGrounded: %i", GS.player.isGrounded);
    SDL_RenderDebugTextFormat(renderer, 10, 40, "time jumped: %i", GS.player.timeJumped);
    SDL_RenderDebugTextFormat(renderer, 10, 55, "tileoffset Y: %i", GS.TileMap.tileOffsetY);

    SDL_Delay(16);

    SDL_RenderPresent(renderer);
  }

  CleanUp(&GS);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
