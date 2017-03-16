#include "SnakeRenderer.h"
#include <stdio.h>

void clear_background(SDL_Renderer *renderer, SDL_Texture *background) {
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

int main(int argc, char **argv) {
	int condition = 1;
	SDL_Window *window = NULL;
	SDL_Event event;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *snake_head_and_tail;
	SDL_Texture *snake_body;
	SDL_Texture *apple_texture;
	SDL_Texture *background;
	RenderingTexture *head = NULL, *last;
	SDL_Keycode lastKey = SDLK_DOWN;
	SDL_Rect food = { -1, -1, 64, 64};
	snake_init();

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	if ( IMG_Init(IMG_INIT_PNG) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	if (SDL_CreateWindowAndRenderer(1280, 768, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	if 	((snake_head_and_tail = IMG_LoadTexture(renderer, "images/head.png")) == NULL || (snake_body = IMG_LoadTexture(renderer, "images/body.png")) == NULL || (apple_texture = IMG_LoadTexture(renderer, "images/apple.png")) == NULL || (background = IMG_LoadTexture(renderer, "images/Background.png")) == NULL) {
		printf("Error:%s\n", IMG_GetError() );
		return -1;
	}


	head = insert_new_texture(head, 200, 136, tail_down, snake_head_and_tail, 0, 64, SDLK_DOWN);
	last = head;
	if (head == NULL) {
		condition = 0;
	}
	head = insert_new_texture(head, 200, 200, body_vertical, snake_body, 0, 64, SDLK_DOWN);
	head = insert_new_texture(head, 200, 264, head_down, snake_head_and_tail, 0, 64, SDLK_DOWN);
	while (condition) {
		if (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					condition = 0;
					break;
				case SDLK_LEFT:
					if (lastKey == SDLK_RIGHT || lastKey == SDLK_LEFT) {
						break;
					}
					change_direction(head, -64, 0, head_left, SDLK_LEFT);

					break;
				case SDLK_RIGHT:
					if (lastKey == SDLK_LEFT || lastKey == SDLK_RIGHT) {
						break;
					}
					change_direction(head, 64, 0, head_right, SDLK_RIGHT);
					break;
				case SDLK_UP:
					if (lastKey == SDLK_DOWN || lastKey == SDLK_UP) {
						break;
					}
					change_direction(head, 0, -64, head_up, SDLK_UP);
					break;
				case SDLK_DOWN:
					if (lastKey == SDLK_UP || lastKey == SDLK_DOWN ) {
						break;
					}
					change_direction(head, 0, 64, head_down, SDLK_DOWN);
					break;
				}
				lastKey = event.key.keysym.sym;
			}
		}
		clear_background(renderer, background);
		generate_food(renderer, apple_texture, &food);
		update_texture(last);
		render_snake(renderer, head);
		SDL_RenderPresent(renderer);
		if(check_snake_collision(head)==1){
			break;
		}
		if (check_collision(head->x,head->y,food.x,food.y) == 1) {
			increase_length(&head, snake_body, snake_head_and_tail);
			food.x=-1;
		}
		SDL_Delay(100);
	}
	printf("SCORE=%d\n",get_length(head) );
	SDL_DestroyTexture( snake_head_and_tail );
	SDL_DestroyTexture( snake_body );
	SDL_DestroyTexture(apple_texture);
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	IMG_Quit();
	SDL_Quit();
}