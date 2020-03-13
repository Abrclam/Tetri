#include<iostream>
using namespace std;
#include<allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <vector>
#include "line.h"
#include "piece.h"
#include"square.h"
#include"Lblock.h"
#include"squig.h"
#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>

//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 500;
const int SCREEN_H = 800;

bool cullGrid();

int grid[10][16] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};

//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main()
{
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	srand(time(NULL));
	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_FONT* font = al_load_font("sponge.ttf", 40, 0);
	al_start_timer(timer);
	int ticker = 0;
	int movetimer = 0;
	//position of player
	double xPos = 400;
	double yPos = 700;

	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	bool ActivePiece = false;
	int pieceChoice = 0;

	vector<piece*>pieces;
	vector<piece*>::iterator iter;
	//tell event queue what to look for
	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));




	while (!doexit)//game loop!
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP]) {
				yPos -= 4.0;
			}

			if (key[KEY_DOWN]) {
				yPos += 4.0;
			}

			if (key[KEY_LEFT]) {
				xPos -= 4.0;
			}

			if (key[KEY_RIGHT]) {
				xPos += 4.0;
			}

			redraw = true;
		}

		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)

			al_draw_circle(xPos, yPos, 50, al_map_rgb(50, 120, 10), 10); //draw the player

			al_flip_display(); //flip everything from memory to gamescreen
		}//end render


	}//end game loop

	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

