
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void lasers(float dt);

 private:

  //main menu text
  sf::Text play_text;
  sf::Text quit_text;
  sf::Text instr_text;

  //win and lose menu text
  sf::Text lose_text;
  sf::Text win_text;
  sf::Text main_menu_text;

  //in game menu text
  sf::Text score_text;

  //game ver text
  sf::Text normal_text;
  sf::Text gravity_text;
  sf::Text quadratic_text;
  sf::Text sine_text;

  sf::Font font;

  sf::RenderWindow& window;

  bool in_menu = true;
  bool in_win = false;
  bool in_lose = false;
  bool in_game_opt = false;
  bool opt_change = true;

  float speed = 80.f;
  float y_move = 0.f;

  int curve_type = 0;
  int selected = 0;
  int score = 0;
  int alien_num = sizeof(alien_ship)/4;
  int shot_num = 3;

  GameObject* ship;
  GameObject* alien_ship[10][4];
  GameObject* laser[4];

};

#endif // SPACEINVADERS_GAME_H
