#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H

#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <time.h>

extern  SDL_Rect *head_right;
extern  SDL_Rect *head_up;
extern  SDL_Rect *head_left;
extern  SDL_Rect *head_down;
extern  SDL_Rect *tail_right;
extern  SDL_Rect *tail_up;
extern  SDL_Rect *tail_left;
extern  SDL_Rect *tail_down;
extern  SDL_Rect *body_horizontal;
extern  SDL_Rect *body_vertical;
extern  SDL_Rect *body_turn_top_left;
extern  SDL_Rect  *body_turn_right_down;
extern  SDL_Rect *body_turn_top_right;
extern  SDL_Rect  *body_turn_left_down;
extern  SDL_Rect *body_turn_right_up;
extern  SDL_Rect  *body_turn_down_left;
extern  SDL_Rect *body_turn_down_right;
extern  SDL_Rect  *body_turn_left_up;
extern  SDL_Rect *apple;
extern SDL_Texture *snake_head_and_tail;
extern SDL_Texture *snake_body;
extern SDL_Texture *apple_texture;
extern SDL_Texture *background;

typedef struct renderingTex {
	SDL_Rect  *clipped_texture;
	SDL_Texture *target_texture;
	int x;
	int y;
	struct renderingTex *next;
	struct renderingTex *prev;
	int x_incr;
	int y_incr;
	SDL_Keycode direction;
} RenderingTexture;

void snake_init();
int get_length(RenderingTexture *head);
int check_snake_collision(RenderingTexture *head);
int check_collision(int x,int y,int x1,int y1);
void increase_length(RenderingTexture **head,SDL_Texture *target,SDL_Texture *snake_head_and_tail);
void generate_food(SDL_Renderer *renderer,SDL_Texture *apple_texture,SDL_Rect *food);
void change_direction(RenderingTexture *head,int x_incr,int y_incr,SDL_Rect *clipped_texture,SDL_Keycode direction);

void update_texture(RenderingTexture *last);

RenderingTexture *insert_new_texture(RenderingTexture *head, int x, int y, SDL_Rect  *clipped_texture, SDL_Texture *target_texture, int x_incr, int y_incr,SDL_Keycode direction);

void render_snake(SDL_Renderer *renderer, RenderingTexture *head);

#endif // SNAKE_RENDERER_H
