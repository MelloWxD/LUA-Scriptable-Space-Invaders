/*
Space invaders game
Author:		Philip Alassad
Filename:	Game.cpp
Date:		14/10/2015
Last Updated:	__/__/____

Description: Source file for Game class
*/

#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "Input.h"



//Constructor
Game::Game()
{
	if (!al_init())
	{
		cout << "Allegro initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return;
	}

	// tell allegro program needs keyboard input
	if (!al_install_keyboard())
	{
		cout << "Keyboard initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		return;
	}

	m_display = al_create_display(1000, 700); // create a display window of size 1000 by 700

	if (!m_display)
	{
		cout << "Display initialisation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_display(m_display);
		return;
	}

	al_set_window_position(m_display, 250, 20); // position display window on screen


	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();  // initialize the True Type Font addon

	m_game_over = al_load_ttf_font("assets/DejaVuSans.ttf", 70, 0);
	if (!m_game_over)
	{
		cout << "Game over message creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(m_game_over);
		return;
	}

	m_lives = al_load_ttf_font("assets/DejaVuSans.ttf", 20, 0);
	if (!m_lives)
	{
		cout << "Lives display creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(m_lives);
		return;
	}

	m_score = al_load_ttf_font("assets/DejaVuSans.ttf", 20, 0);
	if (!m_score)
	{
		cout << "Score display creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(m_score);
		return;
	}

	m_level = al_load_ttf_font("assets/DejaVuSans.ttf", 20, 0);
	if (!m_level)
	{
		cout << "Score display creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(m_level);
		return;
	}

	m_credits = al_load_ttf_font("assets/DejaVuSans.ttf", 20, 0);
	if (!m_credits)
	{
		cout << "Credits display creation failed" << endl;
		cout << "Press any key to exit" << endl;
		_getch();
		al_destroy_font(m_credits);
		return;
	}

	al_init_image_addon(); // initialise allegro image loading 
	Input* Input_manager = new Input();

	// register  display with the event queue, so display change events can be processed
	al_register_event_source(Input_manager->Get_event(), al_get_display_event_source(m_display));
}

Game::~Game()
{
	al_destroy_font(m_game_over);
	al_destroy_font(m_lives);
	al_destroy_font(m_score);
	al_destroy_font(m_level);
	al_destroy_display(m_display);
	al_destroy_font(m_credits);
}

//Methods
ALLEGRO_FONT* Game::game_over_message()
{
	return m_game_over;
}

ALLEGRO_FONT* Game::Lives_message()
{
	return m_lives;
}

ALLEGRO_FONT* Game::Score_message()
{
	return m_score;
}

ALLEGRO_FONT* Game::Level_message()
{
	return m_level;
}

ALLEGRO_FONT* Game::Credits()
{
	return m_credits;
}

