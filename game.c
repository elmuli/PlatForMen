#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int speed = 5;
int jumpSpeed = 3;
int jumplenght = 8;
int jump = 0;

void LoadBitmapTexture(SDL_Texture **texture, SDL_Renderer *renderer, char path[]) {
  SDL_Surface *Surface = SDL_LoadBMP(path);
  if (Surface == NULL) {
    printf("Could not load player bmp\n");
    return;
  }
  *texture = SDL_CreateTextureFromSurface(renderer, Surface);
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

  player->playerRect.x = player->PosX-(player->playerRect.w/2);
  player->playerRect.y = player->PosY-player->playerRect.h;
}

void RenderPlayer(struct gameState *GS, SDL_Renderer *renderer) {
  SDL_RenderTexture(renderer, GS->player.playerTex, NULL, &GS->player.playerRect);
}

void GetPlayerInput(SDL_Event *event, struct gameState *GS, const bool *keys) {

  
  SDL_PumpEvents();

  if (keys[SDL_SCANCODE_W]) {
    if (!GS->player.hasJumped){
      jump = 1;
    }  
  }
  if (keys[SDL_SCANCODE_S]) {
    //UpdatePlayerPos(&GS->player, 0, speed);
  }
  if (keys[SDL_SCANCODE_D]) {
    UpdatePlayerPos(&GS->player, speed, 0);
  }
  if (keys[SDL_SCANCODE_A]) {
    UpdatePlayerPos(&GS->player, -speed, 0);
  }

  if(jump){
    if(GS->player.timeJumped <= jumplenght){
      UpdatePlayerPos(&GS->player, 0, -jumpSpeed);
      GS->player.hasJumped = 1;
      GS->player.timeJumped ++;
    }
    else{
      GS->player.hasJumped = 0;
      GS->player.timeJumped = 0;
      jump = 0;
    }
  }
  
}

int CheckCollision(struct gameState *GS){
  for(int i=0; i<253;){
    if (GS->TileMap.tileType[i] == 1){
      float TileY = i/GS->TileMap.tilesAcross*(float)GS->TileMap.tilePxY;
      float TileX = i%GS->TileMap.tilesAcross*(float)GS->TileMap.tilePxX;

      if(TileY < GS->player.PosY && TileX < GS->player.PosX && TileY > GS->player.PosY+GS->TileMap.tilePxY && TileX > GS->player.PosX+GS->TileMap.tilePxY){
        printf("Collided\n");
        return 1;
      }
    }
    i++;
  }
  return 0;
}

void LoadMapTexture(SDL_Texture **texture, SDL_Renderer *renderer){ 
  SDL_Surface *Surface = SDL_LoadBMP("img/MapTile.bmp"); 
  if (!Surface) {
    printf("Could not load Map img: %s\n", SDL_GetError());
    return;
  }
  *texture = SDL_CreateTextureFromSurface(renderer, Surface);
  if(!*texture){
    printf("Did not create map texture: %s\n", SDL_GetError());
  }
  SDL_DestroySurface(Surface);
}

void CreateTileMap(struct gameState *GS, SDL_Renderer *renderer){
  
  GS->TileMap.tilePxX = 50;
  GS->TileMap.tilePxY = 50;

  GS->TileMap.tileRect.w = (float)GS->TileMap.tilePxX;
  GS->TileMap.tileRect.h = (float)GS->TileMap.tilePxY;

  GS->TileMap.tilesAcross = 18;
  GS->TileMap.tilesDown = 14;

  int grid[252] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  
  };

  memcpy(GS->TileMap.tileType, grid, sizeof(GS->TileMap.tileType));

}

void DrawTileMap(struct gameState *GS, SDL_Renderer *renderer){
  for (int i = 0; i <= 252;) {
    if (GS->TileMap.tileType[i] == 1){
      float TileY = i/GS->TileMap.tilesAcross*(float)GS->TileMap.tilePxY;
      float TileX = i%GS->TileMap.tilesAcross*(float)GS->TileMap.tilePxX;

      GS->TileMap.tileRect.x = TileX;
      GS->TileMap.tileRect.y = TileY;

      if(!GS->TileMap.tileTexture){
        printf("TileTexture is NULL\n");
        break;
      }

      if(!SDL_RenderTexture(renderer, GS->TileMap.tileTexture, NULL, &GS->TileMap.tileRect)){
        printf("%s\n", SDL_GetError());
        break;
      }
    }
    i++;
  }
}

void CleanUp(struct gameState *GS){
  SDL_DestroyTexture(GS->player.playerTex);
  SDL_DestroyTexture(GS->TileMap.tileTexture);
}
