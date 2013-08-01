#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "RosalilaGraphics/RosalilaGraphics.h"

typedef struct Sprite
{
	SDL_Texture* texture;
	Uint16 w;
	Uint16 h;
} Sprite;

/* Adapted from SDL's testspriteminimal.c */
Sprite LoadSprite(const char* file, SDL_Renderer* renderer, RosalilaGraphics* graphics)
{
	Sprite result;
	result.texture = NULL;
	result.w = 0;
	result.h = 0;
	
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
	SDL_Surface* temp2 = IMG_Load("image.png");
    if (temp == NULL)
	{
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

	result.texture = graphics->getTexture("image3.png")->sdl_texture;

    return result;
}

void draw(SDL_Window* window, SDL_Renderer* renderer, const Sprite sprite)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, sprite.w, sprite.h};
	/* Blit the sprite onto the screen */
	SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);
}

int main(int argc, char *argv[])
{
	RosalilaGraphics* graphics = new RosalilaGraphics();
    SDL_Window *window = graphics->window;
    SDL_Renderer *renderer = graphics->renderer;

	Image*image=graphics->getTexture("image.png");

	Sprite sprite = LoadSprite("image2.bmp", renderer,graphics);
    if(sprite.texture == NULL)
        exit(2);

    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    while(!done)
	{
        /* Check for events */
        while(SDL_PollEvent(&event))
		{
            if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
			{
                done = 1;
            }
        }
		
		
		/* Draw a gray background */
//		SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
//		SDL_RenderClear(renderer);
		
		//draw(window, renderer, sprite);
		graphics->draw2DImage	(
             image,
             image->getWidth(),image->getHeight(),
             0,0,
             1,
             0,
             false,
             1,
             1,
             Color(1,1,1,1),
             false);
	graphics->updateScreen();
		/* Update the screen! */
//		SDL_RenderPresent(renderer);
		
//		SDL_Delay(10);
    }

    exit(0);
}
