
#include "Game.h"
#include <cmath>
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

  font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");

  //play text
  play_text.setString("> ENTER SPACE INVADERS");
  play_text.setFont(font);
  play_text.setCharacterSize(50);
  play_text.setFillColor(sf::Color(255,255,255));
  play_text.setPosition(250,100);

  //quit text
  quit_text.setString("QUIT GAME");
  quit_text.setFont(font);
  quit_text.setCharacterSize(50);
  quit_text.setFillColor(sf::Color(255,255,255));
  quit_text.setPosition(350,200);

  //score text
  score_text.setString("score: " + std::to_string(score));
  score_text.setFont(font);
  score_text.setCharacterSize(20);
  score_text.setFillColor(sf::Color(51,255,255));
  score_text.setPosition(970,690);

  //ship gameobject creation
  ship = new GameObject();
  ship->initialiseSprite(ship->ship_texture,"Data/Images/SpaceShooterRedux/PNG/playerShip1_blue.png");
  ship->getSprite()->setPosition(450,600);

  //win menu message
  win_text.setString("YOU WIN!");
  win_text.setFont(font);
  win_text.setCharacterSize(50);
  win_text.setFillColor(sf::Color(255,255,255));
  win_text.setPosition(
    window.getSize().x/2.1 - win_text.getGlobalBounds().width/2,
    window.getSize().y/2 - win_text.getGlobalBounds().height/2);

  //lose menu message
  lose_text.setString("YOU LOSE!");
  lose_text.setFont(font);
  lose_text.setCharacterSize(50);
  lose_text.setFillColor(sf::Color(255,255,255));
  lose_text.setPosition(
    window.getSize().x/2.1 - win_text.getGlobalBounds().width/2,
    window.getSize().y/2 - win_text.getGlobalBounds().height/2);

  //return to menu text
  main_menu_text.setString("*TAB* KEY TO RETURN TO MENU");
  main_menu_text.setFont(font);
  main_menu_text.setCharacterSize(40);
  main_menu_text.setFillColor(sf::Color(255,255,255));
  main_menu_text.setPosition(
    window.getSize().x/2.1 - main_menu_text.getGlobalBounds().width/2,
    window.getSize().y/7 - main_menu_text.getGlobalBounds().height/2);


  //normal game text
  normal_text.setString("NORMAL GAME");
  normal_text.setFont(font);
  normal_text.setCharacterSize(50);
  normal_text.setFillColor(sf::Color(255,255,255));
  normal_text.setPosition(350,100);

  //gravity game text
  gravity_text.setString("GRAVITY GAME");
  gravity_text.setFont(font);
  gravity_text.setCharacterSize(50);
  gravity_text.setFillColor(sf::Color(255,255,255));
  gravity_text.setPosition(350,150);

  //quadratic game text
  quadratic_text.setString("QUADRATIC GAME");
  quadratic_text.setFont(font);
  quadratic_text.setCharacterSize(50);
  quadratic_text.setFillColor(sf::Color(255,255,255));
  quadratic_text.setPosition(350,200);

  //sine game text
  sine_text.setString("SINE GAME");
  sine_text.setFont(font);
  sine_text.setCharacterSize(50);
  sine_text.setFillColor(sf::Color(255,255,255));
  sine_text.setPosition(350,250);

  //instruction text
  instr_text.setString("USE W AND S TO NAVIGATE MENU\nUSE ENTER TO CHOOSE SELECTED OPTION");
  instr_text.setFont(font);
  instr_text.setCharacterSize(25);
  instr_text.setFillColor(sf::Color(255,255,255));
  instr_text.setPosition(310,400);

  //laser shots creation
  for (int s = 0; s < 4; s++)
  {
    laser[s] = new GameObject();
    laser[s]->initialiseSprite(
      laser[s]->laser_texture, "Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
    laser[s]->direction.y = -150;
    laser[s]->visibility = false;

    laser[s]->getSprite()->setPosition(ship->getSprite()->getPosition().x, ship->getSprite()->getPosition().y);
  }

  //alien ships
  for (int x = 0; x < 10; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      alien_ship[x][y] = new GameObject();

      switch (y)
      {
        case 0:
          alien_ship[x][y]->initialiseSprite(alien_ship[x][y]->alien_texture,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlue4.png");
          break;
        case 1:
          alien_ship[x][y]->initialiseSprite(alien_ship[x][y]->alien_texture,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyRed1.png");
          break;
        case 2:
          alien_ship[x][y]->initialiseSprite(alien_ship[x][y]->alien_texture,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyGreen5.png");
          break;
        case 3:
          alien_ship[x][y]->initialiseSprite(alien_ship[x][y]->alien_texture,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack2.png");
          break;
        default:
          break;
      }
      alien_ship[x][y]->getSprite()->setPosition(x*80 + 120,70*y);
      alien_ship[x][y]->getSprite()->setScale(0.5,0.5);
      alien_ship[x][y]->direction.x = 1;
      alien_ship[x][y]->direction.y = 0;
    }
  }

  return true;
}

void Game::update(float dt)
{
  //player ship window collision
  ship->getSprite()->move(
    ship->direction.x * dt, ship->direction.y * dt);

  if (ship->getSprite()->getPosition().x >=
      window.getSize().x - ship->getSprite()->getGlobalBounds().width)
  {
    ship->getSprite()->setPosition(window.getSize().x -
    ship->getSprite()->getGlobalBounds().width,
    ship->getSprite()->getPosition().y);
  }

  if (ship->getSprite()->getPosition().x <= 0)
  {
    ship->getSprite()->setPosition(0, ship->getSprite()->getPosition().y);
  }


  //alien ship collision
  if (in_menu == false)
  {
    for (int x = 0; x < 10; x++)
    {
      for (int y = 0; y < 4; y++)
      {
        if (alien_ship[x][y]->visibility)
        {
          alien_ship[x][y]->getSprite()->move(
            alien_ship[x][y]->direction.x * speed * dt, alien_ship[x][y]->direction.y * 0 * dt);
          if (
            alien_ship[x][y]->getSprite()->getPosition().x >=
            window.getSize().x -
            alien_ship[x][y]->getSprite()->getGlobalBounds().width or
            alien_ship[x][y]->getSprite()->getPosition().x <= 0)
          {
            for (int x = 0; x < 10; x++)
            {
              for (int y = 0; y < 4; y++)
              {
                alien_ship[x][y]->getSprite()->setPosition(
                  alien_ship[x][y]->getSprite()->getPosition().x,
                  alien_ship[x][y]->getSprite()->getPosition().y + 30);
                float pre_direction = alien_ship[x][y]->direction.x;
                alien_ship[x][y]->direction.x *= -1;
                if (pre_direction != alien_ship[x][y]->direction.x)
                {
                  y_move += 1;
                }
              }
            }
          }
          if (alien_ship[x][y]->getSprite()->getGlobalBounds().intersects(ship->getSprite()->getGlobalBounds()))
          {
            in_lose = true;
          }
        }
      }
    }
  }



  for (int x = 0; x < 10; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      switch (curve_type)
      {
        case 0:

          break;
        case 1:
          alien_ship[x][y]->getSprite()->move(0, dt * 40);
          break;
        case 2:
          alien_ship[x][y]->getSprite()->setPosition(alien_ship[x][y]->getSprite()->getPosition().x, -((-y_move+(y*50 - 140)+((alien_ship[x][y]->getSprite()->getPosition().x/50)-10)*((alien_ship[x][y]->getSprite()->getPosition().x/50)-10))));
          break;
        case 3:
          alien_ship[x][y]->getSprite()->setPosition(alien_ship[x][y]->getSprite()->getPosition().x, (y * 50)+20*sin(alien_ship[x][y]->getSprite()->getPosition().x/10) + y_move);
          break;
      }
    }
  }


  for (int s = 0; s < 4; s++)
  {
    if (laser[s]->visibility)
    {
      laser[s]->getSprite()->move(0, laser[s]->direction.y * dt);
      for (int x = 0; x < 10; x++)
      {
        for (int y = 0; y < 4; y++)
        {
          if (laser[s]->getSprite()->getGlobalBounds().intersects(alien_ship[x][y]->getSprite()->getGlobalBounds()) and alien_ship[x][y]->visibility)
          {
            laser[s]->visibility = false;
            alien_ship[x][y]->visibility = false;
            alien_num -= 1;
            if (shot_num == -1)
            {
              shot_num = 3;
            }
            score += 1;
            score_text.setString("score: " + std::to_string(score));
          }
        }
      }
      if (laser[s]->getSprite()->getPosition().y < 0)
      {
        laser[s]->visibility = false;
        if (shot_num == -1)
        {
          shot_num = 3;
        }
      }

      //win the game
      if (alien_num == 0)
      {
        in_win = true;
      }
    }
  }



}

void Game::render()
{
  if (in_menu)
  {
    window.draw(play_text);
    window.draw(quit_text);
    window.draw(instr_text);
  }
  else if (in_lose)
  {
    window.draw(lose_text);
    window.draw(main_menu_text);
  }
  else if (in_win)
  {
    window.draw(win_text);
    window.draw(main_menu_text);
  }
  else if (in_game_opt)
  {
    window.draw(normal_text);
    window.draw(gravity_text);
    window.draw(quadratic_text);
    window.draw(sine_text);
  }
  else
  {
    in_menu = false;
    window.draw(score_text);
    window.draw(*ship->getSprite());
    for (int x = 0; x < 10; x++)
    {
      for (int y = 0; y < 4; y++)
      {
        if (alien_ship[x][y]->visibility)
        {
          window.draw(*alien_ship[x][y]->getSprite());
        }
      }
    }
    for (int s = 0; s < 4; s++)
    {
      if (laser[s]->visibility)
      {
        window.draw(*laser[s]->getSprite());
      }
    }
  }

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

//mapping the keys for the controls on the menu
  if (event.key.code == sf::Keyboard::W)
  {
    if (selected > 0)
    {
      selected -= 1;
    }
  }

  int game_choice = 1;

  if (in_game_opt == true)
  {
    game_choice = 3;
  }

  if (event.key.code == sf::Keyboard::S)
  {
    if (selected < game_choice)
    {
      selected += 1;
    }
  }

  if (in_menu == true)
  {
    switch (selected)
    {
      case 0:
        play_text.setString("> ENTER SPACE INVADERS");
        quit_text.setString("QUIT GAME");
        break;
      case 1:
        play_text.setString("ENTER SPACE INVADERS");
        quit_text.setString("> QUIT GAME");
        break;
      default:
        break;
    }

    if (event.key.code == sf::Keyboard::Enter and opt_change)
    {
      opt_change = false;
      switch (selected)
      {
        case 0:
          in_menu = false;
          in_game_opt = true;
          break;
        case 1:
          window.close();
          break;
        default:
          break;
      }
    }
  }


  if (in_game_opt == true)
  {
    switch (selected)
    {
      case 0:
        normal_text.setString("> NORMAL GAME");
        gravity_text.setString("GRAVITY GAME");
        quadratic_text.setString("QUADRATIC GAME");
        sine_text.setString("SINE GAME");
        break;
      case 1:
        normal_text.setString("NORMAL GAME");
        gravity_text.setString("> GRAVITY GAME");
        quadratic_text.setString("QUADRATIC GAME");
        sine_text.setString("SINE GAME");
        break;
      case 2:
        normal_text.setString("NORMAL GAME");
        gravity_text.setString("GRAVITY GAME");
        quadratic_text.setString("> QUADRATIC GAME");
        sine_text.setString("SINE GAME");
        break;
      case 3:
        normal_text.setString("NORMAL GAME");
        gravity_text.setString("GRAVITY GAME");
        quadratic_text.setString("QUADRATIC GAME");
        sine_text.setString("> SINE GAME");
        break;
      default:
        break;
    }
    if (event.key.code == sf::Keyboard::Enter and opt_change)
    {
      opt_change = false;
      switch (selected)
      {
        case 0:
          in_menu = false;
          in_game_opt = false;
          curve_type = 0;
          break;
        case 1:
          in_menu = false;
          in_game_opt = false;
          curve_type = 1;
          break;
        case 2:
          in_menu = false;
          in_game_opt = false;
          curve_type = 2;
          break;
        case 3:
          in_menu = false;
          in_game_opt = false;
          curve_type = 3;
          break;
        default:
          break;
      }
    }
  }


  //ship movement left and right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    ship->direction.x = -300.f;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    ship->direction.x = 300.f;
  }


  //quit game key
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    window.close();
  }

  //return to menu key
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab))
  {
    game_choice = 0;
    selected = 0;
    in_menu = true;
    in_win = false;
    in_lose = false;
    in_game_opt = false;
    curve_type = 5;
    score = 0;
    ship->getSprite()->setPosition(450,600);
    score_text.setString("score: " + std::to_string(score));
    for (int x = 0; x < 10; x++)
    {
      for (int y = 0; y < 4; y++)
      {
        alien_ship[x][y]->visibility = true;
        alien_ship[x][y]->getSprite()->setPosition(x*80 + 120,y*70);
      }
    }
    y_move = 0;
  }

  //key to shoot lasers
  if (in_menu == false)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and shot_num > -1)
    {
      laser[shot_num]->visibility = true;
      laser[shot_num]->getSprite()->setPosition(ship->getSprite()->getPosition().x + 45,
                                                ship->getSprite()->getPosition().y);
      shot_num -= 1;

    }
  }


}

void Game::keyReleased(sf::Event event)
{
  //keyreleased for ship movement
  if (event.key.code == sf::Keyboard::A)
  {
    ship->direction.x = -0.f;
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    ship->direction.x = 0.f;
  }

  opt_change = true;
}

void Game::lasers(float dt)
{

  //laser shots creation
  for (int s = 0; s < 4; s++)
  {
    laser[s]->direction.y -150;
    laser[s]->visibility = true;
    laser[s]->getSprite()->move(0, laser[s]->direction.y * dt);
  }

}


