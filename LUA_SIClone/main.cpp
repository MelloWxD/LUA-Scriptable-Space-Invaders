/*
Space invaders game
Author:		Philip Alassad
Filename:	main.cpp
Date:		14/10/2015
Last Updated:	25/10/2015

Description:main
*/

#include <ctime>
#include "Input.h"
#include "Player.h"
#include "Ufo.h"
#include "laser.h"
#include "Mothership.h"

using namespace std;

int randomNumber();//random number generator
int main()
{
	srand(time(NULL));//Sets the random seed for the whole game

	// DECLARE variables
	bool is_right = true;//move direction check

	int x, y;//used for ufo array coordinates
	int ufo_counter = 0;//how many ufos destroyed (this tells the game when to start a new level)
	int level_colour = 0;//for setting the background colour for each level and also defines the max number of levels
	int Level_number = 1;//used for displaying the level number
	int laser_generator;//chance of ufo firing
	int Mothership_chance;//chance of mothership appearing


	Game* Game_manager = new Game();
	Input* Input_manager = new Input();
	Ufo*** DynamicUfoArray = new Ufo**[5];
	Mothership* the_mothership = NULL;
	laser* laser_limit[10];
	laser* Ufo_lasers[10];

	Player* the_ship = new Player(500, 625, 3, "assets/player0.bmp");//create the player ship
	the_ship->addFrame("assets/player1.bmp");


	

	
	for (int i = 1; i <= 10; i++)//DISPLAY THE GAME START MESSAGE *maybe in a method or function?*
	{
		al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
		al_draw_textf(Game_manager->game_over_message(), al_map_rgb(255, 0, 0), 300, 300, 0, "GET READY");
		al_flip_display();
		al_rest(0.25);
		al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
		al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 0), 300, 300, 0, "GET READY");
		al_flip_display();
		al_rest(0.25);
	}
	for (int i = 5; i >= 0; i--)//DISPLAY THE GAME START MESSAGE *maybe in a method or function?*
	{
		al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
		al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 255, 0), 300, 300, 0, "START IN: %d", i);
		al_flip_display();
		al_rest(1.0);
	}
	
	while (the_ship->getLives() > 0)// keep going til the ship is dead
	{
		
			
			al_flush_event_queue(Input_manager->Get_event());//clears the queue of events

			for (y = 0; y < 5; y++)//spawn ufos
			{
				DynamicUfoArray[y] = new Ufo*[10];
			}
			for (y = 0; y < 5; y++)
			{
				for (x = 0; x < 10; x++)
				{
					DynamicUfoArray[y][x] = new Ufo((x * 85) + 85, (y * 50) + 70, "assets/Ufo1.bmp");
					DynamicUfoArray[y][x]->addFrame("assets/Ufo2.bmp");

				}
			}
			for (int i = 0; i < 10; i++)//set all lasers to null
			{
				laser_limit[i] = NULL;
			}
			for (int i = 0; i < 10; i++)
			{
				Ufo_lasers[i] = NULL;
			}
			if (Input_manager->key_is_pressed(KEY_D))//moves ship right
			{
				Input_manager->set_key_to_false(KEY_D);
			}
			if (Input_manager->key_is_pressed(KEY_A))//moves ship left
			{
				Input_manager->set_key_to_false(KEY_A);
			}

			while (the_ship->getLives() > 0)// keep going til the ship is dead
			{
				while (!Input_manager->key_is_pressed(KEY_ESCAPE)/*&& Input_manager->key_is_pressed(KEY_ENTER)*/)// loop until escape key is pressed
				{
					Input_manager->set_key_to_false(KEY_ENTER);

					Input_manager->update();
					if (Input_manager->key_is_pressed(KEY_D))//moves ship right
					{
						the_ship->right();
					}
					if (Input_manager->key_is_pressed(KEY_A))//moves ship left
					{
						the_ship->left();
					}
					if (Input_manager->key_is_pressed(KEY_SPACE))//fires
					{
						for (int i = 0; i < 10; i++)
						{
							if (laser_limit[i] == NULL)
							{
								laser_limit[i] = new laser(the_ship->getX() + 44, the_ship->getY(), "assets/PlayerLaser.bmp");
								break;
							}
						}
						Input_manager->set_key_to_false(KEY_SPACE);//stops the player from just keeping space pressed
					}

					for (y = 0; y < 5; y++)//this lot generates a random number to determine if each ufo shoots
					{
						for (x = 0; x < 10; x++)
						{
							if (DynamicUfoArray[y][x] != NULL)
							{
								laser_generator = randomNumber();
								if (laser_generator >= 41 - (ufo_counter / 3) && laser_generator <= 50 + (ufo_counter / 3))
								{
									for (int i = 0; i < 10; i++)
									{
										if (Ufo_lasers[i] == NULL)
										{
											Ufo_lasers[i] = new laser(DynamicUfoArray[y][x]->getX() + 35, DynamicUfoArray[y][x]->getY() + 53, "assets/PlayerLaser.bmp");
											break;
										}
									}
								}
							}
						}
					}

					// colour entire display with rgb colour
					al_clear_to_color(al_map_rgb(level_colour, level_colour*0.5, level_colour*0.25));

					if (the_mothership == NULL)//see if a mothership appears
					{
						Mothership_chance = randomNumber();
						if (Mothership_chance >= 250 && Mothership_chance <= 255)
						{
							the_mothership = new Mothership(0, 20, "assets/Mothership.bmp");
							the_mothership->addFrame("assets/Mothership.bmp");
						}
					}
					if (the_mothership != NULL)//draw and move the mothership
					{
						the_mothership->draw();
						the_mothership->right();
						if (the_mothership->getX() >= 1000)
						{
							delete the_mothership;
							the_mothership = nullptr;
							the_mothership = NULL;
						}
					}

					for (int i = 0; i < 10; i++)//delete the player lasers if they leave the screen
					{
						if (laser_limit[i] != NULL)
						{
							if (laser_limit[i]->getY() <= 0)
							{
								delete laser_limit[i];
								laser_limit[i] = nullptr;
								laser_limit[i] = NULL;
								break;
							}
						}
					}

					for (int i = 0; i < 10; i++)//delete the ufo lasers if they leave the screen
					{
						if (Ufo_lasers[i] != NULL)
						{
							if (Ufo_lasers[i]->getY() >= 700)
							{
								delete Ufo_lasers[i];
								Ufo_lasers[i] = nullptr;
								Ufo_lasers[i] = NULL;
								break;
							}
						}
					}

					for (int i = 0; i < 10; i++)//now to check for hits against ufos
					{
						if (laser_limit[i] != NULL)
						{
							for (y = 0; y < 5; y++)
							{
								for (x = 0; x < 10; x++)
								{
									if (DynamicUfoArray[y][x] != NULL)
									{
										if (laser_limit[i] != NULL)
										{
											if (laser_limit[i]->getX() >= DynamicUfoArray[y][x]->getX() && laser_limit[i]->getX() <= DynamicUfoArray[y][x]->getX() + 68)
											{
												if (laser_limit[i]->getY() >= DynamicUfoArray[y][x]->getY() && laser_limit[i]->getY() <= DynamicUfoArray[y][x]->getY() + 53)
												{
													if (laser_limit[i]->getX() + 4 >= DynamicUfoArray[y][x]->getX() && laser_limit[i]->getX() + 4 <= DynamicUfoArray[y][x]->getX() + 68)
													{
														ufo_counter++;
														delete DynamicUfoArray[y][x];
														DynamicUfoArray[y][x] = nullptr;
														the_ship->setScore(100);
														delete laser_limit[i];
														laser_limit[i] = nullptr;
														laser_limit[i] = NULL;
													}
												}
											}
											if (laser_limit[i] == NULL)break;
										}
										if (laser_limit[i] == NULL)break;
									}
								}
							}

							if (laser_limit[i] != NULL)//check to see if the mothership is hit 
							{
								if (the_mothership != NULL)
								{
									if (laser_limit[i]->getX() >= the_mothership->getX() && laser_limit[i]->getX() <= the_mothership->getX() + 103)
									{
										if (laser_limit[i]->getY() >= the_mothership->getY() && laser_limit[i]->getY() <= the_mothership->getY() + 42)
										{
											if (laser_limit[i]->getX() + 4 >= the_mothership->getX() && laser_limit[i]->getX() + 4 <= the_mothership->getX() + 103)
											{
												the_mothership->reduceLives();
												the_ship->setScore(20);
												if (the_mothership->getLives() <= 0)
												{
													the_ship->increaseLives();
													the_ship->setScore(300);
													delete the_mothership;
													the_mothership = nullptr;
													the_ship->setScore(100);
													delete laser_limit[i];
													laser_limit[i] = nullptr;
													laser_limit[i] = NULL;
												}
											}
										}
									}
								}
							}
							if (laser_limit[i] != NULL)//draw and move the player laser if no hit
							{
								laser_limit[i]->draw();
								laser_limit[i]->up();
							}
						}
					}

					for (int i = 0; i < 10; i++)//check for hit against player and delete the ufo lasers which hit
					{
						if (Ufo_lasers[i] != NULL)
						{
							if (Ufo_lasers[i]->getX() >= the_ship->getX() + 10 && Ufo_lasers[i]->getX() + 10 <= the_ship->getX() + 86)
							{
								if (Ufo_lasers[i]->getY() >= the_ship->getY() + 10 && Ufo_lasers[i]->getY() <= the_ship->getY() + 58)
								{
									if (Ufo_lasers[i]->getX() + 4 >= the_ship->getX() + 10 && Ufo_lasers[i]->getX() + 4 <= the_ship->getX() + 86)
									{
										the_ship->reduceLives();
										delete Ufo_lasers[i];
										Ufo_lasers[i] = nullptr;
										Ufo_lasers[i] = NULL;
									}
								}
							}

							if (Ufo_lasers[i] != NULL)//draw and move the ufo lasers if no hit
							{
								Ufo_lasers[i]->draw();
								Ufo_lasers[i]->down();
							}
						}
					}

					//draw all the ufos
					for (x = 0; x < 10; x++)
					{
						for (y = 0; y < 5; y++)
						{
							if (DynamicUfoArray[y][x] != NULL)
								DynamicUfoArray[y][x]->draw();
						}
					}

					for (x = 9; x >= 0; x--)//the bottom check
					{
						for (y = 0; y < 5; y++)
						{
							if (DynamicUfoArray[y][x] != NULL)
							{
								if (DynamicUfoArray[y][x]->Ufo::getY() >= 575)
								{
									the_ship->kill();//don't let the ufos get to the bottom !!!
									for (y = 0; y < 5; y++)
									{
										for (x = 0; x < 10; x++)
										{
											if (DynamicUfoArray[y][x] != NULL)
											{
												DynamicUfoArray[y][x]->Ufo::setX((x * 85) + 85);
												DynamicUfoArray[y][x]->Ufo::setY((y * 50) + 70);
											}
										}
									}
								}
							}
						}
					}

					for (x = 9; x >= 0; x--)//the edge check
					{
						for (y = 0; y < 5; y++)
						{
							if (DynamicUfoArray[y][x] != NULL)
							{
								if (DynamicUfoArray[y][x]->Ufo::getX() >= 910 || DynamicUfoArray[y][x]->Ufo::getX() <= -5)
								{
									for (int i = 0; i < 4; i++)
									{
										for (x = 9; x >= 0; x--)//move down
										{
											for (y = 0; y < 5; y++)
											{
												if (DynamicUfoArray[y][x] != NULL)
													DynamicUfoArray[y][x]->down();
											}
										}
									}
									if (is_right == true)//change direction
									{
										is_right = false;
									}
									else is_right = true;
								}
							}
						}
					}

					if (is_right)//move right
					{
						for (x = 0; x < 10; x++)
						{
							for (y = 0; y < 5; y++)
							{
								if (DynamicUfoArray[y][x] != NULL)
									DynamicUfoArray[y][x]->right(ufo_counter, Level_number);
							}
						}
					}
					else
						if (!is_right)//move left
						{
							for (x = 0; x < 10; x++)//the check
							{
								for (y = 0; y < 5; y++)
								{
									if (DynamicUfoArray[y][x] != NULL)
										DynamicUfoArray[y][x]->left(ufo_counter, Level_number);
								}
							}
						}

					for (x = 0; x < 10; x++)//draw the ufo's
					{
						for (y = 0; y < 5; y++)
						{
							if (DynamicUfoArray[y][x] != NULL)
								DynamicUfoArray[y][x]->draw();
						}
					}


					al_draw_textf(Game_manager->Lives_message(), al_map_rgb(100, 250, 50), 0, 0, 0, "lives: %d", the_ship->getLives());
					al_draw_textf(Game_manager->Score_message(), al_map_rgb(100, 250, 50), 200, 0, 0, "Score: %d", the_ship->getScore());
					al_draw_textf(Game_manager->Level_message(), al_map_rgb(100, 250, 50), 750, 0, 0, "level: %d", Level_number);
					al_draw_textf(Game_manager->Credits(), al_map_rgb(100, 250, 50), 0, 670, 0, "Game design and programming : Philip Alassad");
					al_draw_textf(Game_manager->Credits(), al_map_rgb(225, 100, 225), 600, 670, 0, "Assets and artwork : James Dorrington");


					the_ship->draw();//draw the ship
					al_flip_display(); // show what has just been drawn
					al_rest(0.01); // slow things down a bit
					if (the_ship->getLives() == 0)
					{
						for (int i = 10; i >= 0; i--)//DISPLAY THE GAME OVER MESSAGE *maybe in a method or function?*
						{
							al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
							al_draw_textf(Game_manager->game_over_message(), al_map_rgb(255, 0, 0), 300, 300, 0, "BLOWED UP");
							al_draw_textf(Game_manager->Lives_message(), al_map_rgb(255, 0, 0), 0, 400, 0, "ANOTHER GO? (press enter): %d", i);

							al_draw_textf(Game_manager->Lives_message(), al_map_rgb(255, 0, 0), 0, 0, 0, "lives: %d", the_ship->getLives());
							al_draw_textf(Game_manager->Score_message(), al_map_rgb(255, 0, 0), 200, 0, 0, "Score: %d", the_ship->getScore());
							al_draw_textf(Game_manager->Level_message(), al_map_rgb(255, 0, 0), 750, 0, 0, "level: %d", Level_number);
							al_flip_display();
							al_rest(0.25);

							



							al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
							al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 0), 300, 300, 0, "BLOWED UP");
							al_draw_textf(Game_manager->Lives_message(), al_map_rgb(0, 0, 0), 0, 0, 0, "lives: %d", the_ship->getLives());
							al_draw_textf(Game_manager->Score_message(), al_map_rgb(255, 0, 0), 200, 0, 0, "Score: %d", the_ship->getScore());
							al_draw_textf(Game_manager->Level_message(), al_map_rgb(0, 0, 0), 750, 0, 0, "level: %d", Level_number);
							al_draw_textf(Game_manager->Lives_message(), al_map_rgb(255, 0, 0), 0, 400, 0, "ANOTHER GO? (press enter): %d", i);

							al_flip_display();
							al_rest(0.25);
							Input_manager->update();
							if (Input_manager->key_is_pressed(KEY_ENTER))
							{
								
								for (y = 0; y < 5; y++)//spawn ufos
								{
									DynamicUfoArray[y] = new Ufo*[10];
								}
								for (y = 0; y < 5; y++)
								{
									for (x = 0; x < 10; x++)
									{
										DynamicUfoArray[y][x] = new Ufo((x * 85) + 85, (y * 50) + 70, "assets/Ufo1.bmp");

									}
								}
								the_ship->reset_score();
								ufo_counter = 0;//how many ufos destroyed (this tells the game when to start a new level)
								level_colour = 0;//for setting the background colour for each level and also defines the max number of levels
								Level_number = 1;
								the_ship->reset_lives();
								for (int i = 1; i <= 10; i++)//DISPLAY THE GAME START MESSAGE *maybe in a method or function?*
								{
									al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
									al_draw_textf(Game_manager->game_over_message(), al_map_rgb(255, 0, 0), 300, 300, 0, "GET READY");
									al_flip_display();
									al_rest(0.25);
									al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
									al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 0), 300, 300, 0, "GET READY");
									al_flip_display();
									al_rest(0.25);
								}
								for (int i = 5; i >= 0; i--)//DISPLAY THE GAME START MESSAGE *maybe in a method or function?*
								{
									al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
									al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 255, 0), 300, 300, 0, "START IN: %d", i);
									al_flip_display();
									al_rest(1.0);
								}
								for (int i = 0; i < 10; i++)//set all lasers to null
								{
									laser_limit[i] = NULL;
								}
								for (int i = 0; i < 10; i++)
								{
									Ufo_lasers[i] = NULL;
								}
								if (Input_manager->key_is_pressed(KEY_D))//moves ship right
								{
									Input_manager->set_key_to_false(KEY_D);
								}
								if (Input_manager->key_is_pressed(KEY_A))//moves ship left
								{
									Input_manager->set_key_to_false(KEY_A);
								}
								break;
							}

						}
						break;
					}
					if (ufo_counter == 50)
					{
						if (level_colour == 255)
						{
							for (int i = 1; i <= 10; i++)//DISPLAY THE GAME OVER MESSAGE *maybe in a method or function?*
							{
								al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
								al_draw_textf(Game_manager->game_over_message(), al_map_rgb(100, 250, 50), 300, 300, 0, "You Win");
								al_draw_textf(Game_manager->Lives_message(), al_map_rgb(100, 250, 50), 0, 0, 0, "lives: %d", the_ship->getLives());
								al_draw_textf(Game_manager->Score_message(), al_map_rgb(100, 250, 50), 200, 0, 0, "Score: %d", the_ship->getScore());
								al_flip_display();
								al_rest(0.25);
								al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
								al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 0), 300, 300, 0, "You Win");
								al_draw_textf(Game_manager->Lives_message(), al_map_rgb(100, 250, 50), 0, 0, 0, "lives: %d", the_ship->getLives());
								al_draw_textf(Game_manager->Score_message(), al_map_rgb(100, 250, 50), 200, 0, 0, "Score: %d", the_ship->getScore());
								al_flip_display();
								al_rest(0.25);
							}
						}

						if (level_colour != 255)
						{
							for (int i = 1; i <= 10; i++)//DISPLAY THE NEXT LEVEL MESSAGE *maybe in a method or function?*
							{
								al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
								al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 255), 300, 300, 0, "Next Level");
								al_draw_textf(Game_manager->Lives_message(), al_map_rgb(100, 250, 50), 0, 0, 0, "lives: %d", the_ship->getLives());
								al_draw_textf(Game_manager->Score_message(), al_map_rgb(100, 250, 50), 200, 0, 0, "Score: %d", the_ship->getScore());
								al_flip_display();
								al_rest(0.25);
								al_clear_to_color(al_map_rgb(125, 125, 125)); // colour entire display with rgb colour
								al_draw_textf(Game_manager->game_over_message(), al_map_rgb(0, 0, 0), 300, 300, 0, "Next Level");
								al_draw_textf(Game_manager->Lives_message(), al_map_rgb(100, 250, 50), 0, 0, 0, "lives: %d", the_ship->getLives());
								al_draw_textf(Game_manager->Score_message(), al_map_rgb(100, 250, 50), 200, 0, 0, "Score: %d", the_ship->getScore());
								al_flip_display();
								al_rest(0.25);
								al_flush_event_queue(Input_manager->Get_event());//clears the queue of events
							}

							for (int i = 0; i < 10; i++)//delete the lasers
							{
								if (laser_limit[i] != NULL)
								{
									delete Ufo_lasers[i];
									Ufo_lasers[i] = nullptr;
									Ufo_lasers[i] = NULL;
								}
							}
							level_colour = level_colour + 5;
							Level_number++;
							ufo_counter = 0;
							the_ship->setX(500);//sets the ships position back to the centre of the screen
							break;
						}
					}
				}
				if (!Input_manager->key_is_pressed(KEY_ENTER))
				break;
			}

			if (Input_manager->key_is_pressed(KEY_ESCAPE) || level_colour == 255 || the_ship->getLives() == 0)

				break;
		}
		

	///////////////////////////////////////////////

	//delete the ufo's (reverse order)
	for (y = 0; y< 5; y++)
	{
		for (x = 0; x < 10; x++)
		{
			delete DynamicUfoArray[y][x];
		}
	}
	for (y = 0; y < 5; y++)
	{
		delete DynamicUfoArray[y];
	}
	delete [] DynamicUfoArray;
	DynamicUfoArray = nullptr;
	//////////////////////////////////////////

	//delete the mothership
	if (the_mothership != NULL)
	{
		delete the_mothership;
		the_mothership = nullptr;
	}

	/////////////////////////////////////////

	for (int i = 0; i < 10; i++)//delete remaining lasers
	{
		delete laser_limit[i];
		laser_limit[i] = nullptr;
	}
	//////////////////////////////////////////
	
	delete the_ship;//delete the player ship
	the_ship = nullptr;


	return 0;
}

int randomNumber()//random number generator
{
	//Gives the remainder of a division of the random seed by the maximum range  
	//(this will always give an answer between 0 and Max-1)
	//Then adds one, to return a value in the range from 1 to Max (instead of 0 to Max-1)
	return (rand() % 18000)+1;	
}
