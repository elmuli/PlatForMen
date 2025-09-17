#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int widht = 900;
int hight = 700;

struct gameState GS;

int main(int argc, char *argv[]){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  SDL_Window *window = SDL_CreateWindow("Platformer", widht, hight, 0);
  SDL_SetWindowResizable(window, true);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  SDL_Event windowEvent;

  const bool *keys = SDL_GetKeyboardState(NULL);

  printf("-Initialized SDL-\n");

  LoadPlayerTexture(&GS.player, renderer);

  printf("-Player loaded-\n");

  LoadMapTexture(GS.MapTexture, renderer);

  printf("-Map loaded-\n");

  GS.player.PosX = 50;
  GS.player.PosY = 800;

  SetPlayerRect(&GS.player, 60, 50);
  UpdatePlayerPos(&GS.player, 0, 0);

  bool GameIsRunning = true;

  while (GameIsRunning) {
    if (SDL_PollEvent(&windowEvent)) {
      if (SDL_EVENT_QUIT == windowEvent.type) {
        break;
      }
    }

    GetPlayerInput(&windowEvent, &GS, keys);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    RenderPlayer(&GS, renderer);

    SDL_Delay(16);

    SDL_RenderPresent(renderer);
  }

  CleanUp(&GS);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
