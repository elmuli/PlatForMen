#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>

struct Player {
  int PosX, PosY;
  SDL_Texture *playerTex;
  SDL_FRect playerRect;
};

struct gameState {
  struct Player player;
  SDL_Texture *MapTexture;
  SDL_FRect MapRect;
};

void LoadPlayerTexture(struct Player *, SDL_Renderer *);
void SetPlayerRect(struct Player *, int, int);
void UpdatePlayerPos(struct Player *, int, int);
void RenderPlayer(struct gameState *, SDL_Renderer *);

void GetPlayerInput(SDL_Event *, struct gameState *, const bool *);

void LoadMapTexture(SDL_Texture *,SDL_Renderer *);

void CleanUp(struct gameState *);
