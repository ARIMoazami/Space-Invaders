
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

  sf::Sprite ship;

  sf::Texture ship_texture;
  sf::Texture alien_texture;
  sf::Texture laser_texture;

  bool visibility = true;

  float speed = 200.f;

  Vector2 direction = {0,0};

 private:
  sf::Sprite* sprite = nullptr;
};

#endif // SPACEINVADERS_GAMEOBJECT_H


