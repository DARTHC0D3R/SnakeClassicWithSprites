#include "SnakeRenderer.h"


SDL_Rect *head_right;
SDL_Rect *head_up;
SDL_Rect *head_left;
SDL_Rect *head_down;
SDL_Rect *tail_right;
SDL_Rect *tail_up;
SDL_Rect *tail_left;
SDL_Rect *tail_down;
SDL_Rect *body_horizontal;
SDL_Rect *body_vertical;
SDL_Rect *body_turn_top_left;
SDL_Rect  *body_turn_right_down;
SDL_Rect *body_turn_top_right;
SDL_Rect  *body_turn_left_down;
SDL_Rect *body_turn_right_up;
SDL_Rect  *body_turn_down_left;
SDL_Rect *body_turn_down_right;
SDL_Rect  *body_turn_left_up;
SDL_Rect *apple;

int get_length(RenderingTexture *head){
	int counter=1;
	RenderingTexture *temp=head;
	while(temp!=NULL){
		counter++;
		temp=temp->next;
	}
	return counter*10;
}
int check_snake_collision(RenderingTexture *head){
	RenderingTexture *temp=head->next->next;
	while(temp!=NULL){
		if(check_collision(temp->x,temp->y,head->x,head->y)==1){
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}
void increase_length(RenderingTexture **head, SDL_Texture *target, SDL_Texture *snake_head_and_tail) {
	RenderingTexture *next;
	*head = insert_new_texture(*head, (*head)->x + (*head)->x_incr, (*head)->y + (*head)->y_incr, (*head)->clipped_texture, snake_head_and_tail, (*head)->x_incr, (*head)->y_incr, (*head)->direction);
	next=(*head)->next;
	next->target_texture = target;
	switch (next->direction) {
	case SDLK_DOWN:
	case SDLK_UP:
		next->clipped_texture = body_vertical;
		break;
	case SDLK_RIGHT:
	case SDLK_LEFT:
		next->clipped_texture = body_horizontal;
	}
}
void generate_food(SDL_Renderer *renderer, SDL_Texture *apple_texture, SDL_Rect *food) {
	if (food->x == -1) {
		food->x = 64 * (rand() % 20);
		food->y = 64 * (rand() % 12);
	}
	SDL_RenderCopy(renderer, apple_texture, apple, food);
}
int check_collision(int x,int y,int x1,int y1) {
	if (x < x1 + 64 && x + 64 > x1 && y < y1 + 64 && 64 + y > y1) {
		return 1;
	}
	return 0;
}
void snake_init() {
	srand(time(NULL));
	head_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	head_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	tail_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_horizontal = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_vertical = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_top_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_right_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_top_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_left_down = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_right_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_down_left = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_down_right = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	body_turn_left_up = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	apple = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	*head_right = (SDL_Rect) {64, 0, 64, 64};
	*head_up = (SDL_Rect) {0, 0, 64, 64};
	*head_left = (SDL_Rect)  {0, 64, 64, 64};
	*head_down = (SDL_Rect) {64, 64, 64, 64};
	*tail_right = (SDL_Rect) {64, 128, 64, 64};
	*tail_up = (SDL_Rect) {0, 128, 64, 64};
	*tail_left = (SDL_Rect)  {0, 192, 64, 64};
	*tail_down = (SDL_Rect) {64, 192, 64, 64};
	*body_horizontal = (SDL_Rect) {0, 0, 64, 64};
	*body_vertical = (SDL_Rect) {64, 0, 64, 64};
	*body_turn_top_left = (SDL_Rect)  {0, 64, 64, 64};
	*body_turn_top_right = (SDL_Rect) {64, 64, 64, 64};
	*body_turn_right_up = (SDL_Rect) {0, 134, 64, 64};
	*body_turn_down_right = (SDL_Rect) {64, 134, 64, 64};
	*apple = (SDL_Rect) {0, 0, 64, 64};

	body_turn_right_down = body_turn_top_left;
	body_turn_left_down = body_turn_top_right;
	body_turn_down_left =  body_turn_right_up;
	body_turn_left_up = body_turn_down_right;


}

RenderingTexture *insert_new_texture(RenderingTexture *head, int x, int y, SDL_Rect  *clipped_texture, SDL_Texture *target_texture, int x_incr, int y_incr, SDL_Keycode direction) {
	RenderingTexture *n = (RenderingTexture*)malloc(sizeof(RenderingTexture));
	if (n == NULL) {
		printf("ERROR IN ALLOCATION");
		return NULL;
	}
	n->clipped_texture = clipped_texture;
	n->x = x;
	n->y = y;
	n->target_texture = target_texture;
	n->next = NULL;
	n->prev = NULL;
	n->x_incr = x_incr;
	n->y_incr = y_incr;
	n->direction = direction;
	if (head == NULL) {
		return n;
	}
	n->next = head;
	head->prev = n;
	return n;
}
void change_direction(RenderingTexture *head, int x_incr, int y_incr, SDL_Rect *clipped_texture, SDL_Keycode direction) {
	head->x_incr = x_incr;
	head->y_incr = y_incr;
	head->clipped_texture = clipped_texture;
	head->direction = direction;
}
void update_texture(RenderingTexture *last) {
	RenderingTexture *temp = last->prev;
	if (last->prev->x_incr == 0 && last->prev->y_incr == 0) {
		switch (last->prev->direction) {
		case SDLK_DOWN:
			last->clipped_texture = tail_down;
			last->x_incr = 0;
			last->y_incr = 64;
			last->direction = SDLK_DOWN;
			last->x = last->prev->x;
			last->y = last->prev->y;
			break;
		case SDLK_RIGHT:
			last->clipped_texture = tail_right;
			last->x_incr = 64;
			last->y_incr = 0;
			last->direction = SDLK_RIGHT;
			last->x = last->prev->x;
			last->y = last->prev->y;
			break;
		case SDLK_UP:
			last->clipped_texture = tail_up;
			last->x_incr = 0;
			last->y_incr = -64;
			last->direction = SDLK_UP;
			last->x = last->prev->x;
			last->y = last->prev->y;
			break;
		case SDLK_LEFT:
			last->clipped_texture = tail_left;
			last->x_incr = -64;
			last->y_incr = 0;
			last->direction = SDLK_LEFT;
			last->x = last->prev->x;
			last->y = last->prev->y;
			break;
		}
	} else {
		last->x += last->x_incr;
		last->y += last->y_incr;
		if (last->x > 1216) {
			last->x = 0;
		}
		else if (last->x < 0) {
			last->x = 1216;
		}
		if (last->y > 704) {
			last->y = 0;
		}
		else if (last->y < 0) {
			last->y = 704;
		}
	}
	while (temp->prev->prev != NULL) {

		temp->clipped_texture = temp->prev->clipped_texture;
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->x_incr = 0;
		temp->y_incr = 0;
		temp->direction = temp->prev->direction;
		temp = temp->prev;
	}
	if (temp->direction != temp->prev->direction) {
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->x_incr = 0;
		temp->y_incr = 0;
		switch (temp->prev->direction) {
		case SDLK_LEFT:
			switch (temp->direction) {
			case SDLK_UP:
				temp->clipped_texture = body_turn_top_left;
				break;
			case SDLK_DOWN:
				temp->clipped_texture = body_turn_down_left;
				break;
			}
			break;
		case SDLK_RIGHT:
			switch (temp->direction) {
			case SDLK_UP:
				temp->clipped_texture = body_turn_top_right;
				break;
			case SDLK_DOWN:
				temp->clipped_texture = body_turn_down_right;
			}
			break;
		case SDLK_UP:
			switch (temp->direction) {
			case SDLK_LEFT:
				temp->clipped_texture = body_turn_left_up;
				break;
			case SDLK_RIGHT:
				temp->clipped_texture =  body_turn_right_up;
			}
			break;
		case SDLK_DOWN:
			switch (temp->direction) {
			case SDLK_LEFT:
				temp->clipped_texture = body_turn_left_down;
				break;
			case SDLK_RIGHT:
				temp->clipped_texture = body_turn_right_down;
			}
			break;
		}
		temp->direction = temp->prev->direction;
	} else {
		temp->x_incr = temp->prev->x_incr;
		temp->y_incr = temp->prev->y_incr;
		temp->x = temp->prev->x;
		temp->y = temp->prev->y;
		temp->direction = temp->prev->direction;
		switch (temp->prev->direction) {
		case SDLK_LEFT:
		case SDLK_RIGHT:
			temp->clipped_texture = body_horizontal;
			break;
		case SDLK_UP:
		case SDLK_DOWN:
			temp->clipped_texture = body_vertical;
			break;
		}
	}



	temp = temp->prev;
	temp->x += temp->x_incr;
	temp->y += temp->y_incr;
	if (temp->x > 1216) {
		temp->x = 0;
	}
	else if (temp->x < 0) {
		temp->x = 1216;
	}
	if (temp->y > 704) {
		temp->y = 0;
	}
	else if (temp->y < 0) {
		temp->y = 704;
	}
}

void render_snake(SDL_Renderer *renderer, RenderingTexture *head) {
	RenderingTexture *temp = head;
	SDL_Rect viewing_window;
	viewing_window.w = 64;
	viewing_window.h = 64;
	while (temp != NULL) {
		viewing_window.x = temp->x;
		viewing_window.y = temp->y;
		SDL_RenderCopy(renderer, temp->target_texture, temp->clipped_texture, &viewing_window);
		temp = temp->next;
	}
}