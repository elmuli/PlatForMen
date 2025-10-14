#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>

struct Player {
  int PosX, PosY;
  SDL_Texture *playerTex;
  SDL_FRect playerRect;
  int hasJumped;
  int timeJumped;
  int jump;
  int isGrounded;
};

struct tileMap {
  int tilePxX, tilePxY;
  int tilesAcross, tilesDown;
  SDL_Texture *tileTexture;
  SDL_FRect tileRect;
  int tileType[252];
};

struct gameState {
  struct Player player;
  struct tileMap TileMap;
};

void LoadBitmapTexture(SDL_Texture **, SDL_Renderer *, char[]);

void SetPlayerRect(struct Player *, int, int);
void UpdatePlayerPos(struct Player *, int, int);
void RenderPlayer(struct gameState *, SDL_Renderer *);
void RotatePlayer(struct Player *, int);

void GetPlayerInput(SDL_Event *, struct gameState *, const bool *);
int CheckCollision(struct gameState *);

void CreateTileMap(struct gameState *, SDL_Renderer *);
void DrawTileMap(struct gameState *, SDL_Renderer *);

void CreateMap(SDL_Texture *, SDL_Renderer *);

void LoadMapTexture(SDL_Texture **,SDL_Renderer *);

void CleanUp(struct gameState *);
