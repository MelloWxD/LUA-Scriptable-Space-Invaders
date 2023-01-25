/*
Space invaders game
Author:		Philip Alassad
Filename:	Game.h
Date:		14/10/2015
Last Updated:	__/__/____

Description: Header file for Game class
*/

#pragma once

//includes go here
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class Game
{
private:
	//members	
	ALLEGRO_FONT* m_game_over = NULL;//game over message
	ALLEGRO_FONT* m_lives = NULL;//lives display
	ALLEGRO_FONT* m_score = NULL;
	ALLEGRO_FONT* m_level = NULL;
	ALLEGRO_FONT* m_credits = NULL;

protected:
	//members
	ALLEGRO_DISPLAY* m_display = NULL;

public:
	//constructor
	Game();
	~Game();

	//methods
	ALLEGRO_FONT* game_over_message();//get method
	ALLEGRO_FONT* Lives_message();//get method
	ALLEGRO_FONT* Score_message();//get method
	ALLEGRO_FONT* Level_message();
	ALLEGRO_FONT* Credits();
};