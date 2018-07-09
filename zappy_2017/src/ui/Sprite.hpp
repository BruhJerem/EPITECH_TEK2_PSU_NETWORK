//
// EPITECH PROJECT, 2018
// zappy
// File description:
// sprite
//

#pragma once
#include <SFML/Graphics.hpp>


namespace Ui {
  class Sprite
  {
  public:
    Sprite(std::string name);
    ~Sprite();
    void setTex(std::string name);
    sf::Texture getTex() const;
    void setSprite();
    sf::Sprite getSprite() const;
    void setPos(float x, float y);
    void setScale(float x);
    float getScale() const;
    sf::Vector2f getPos() const;
    void draw(sf::RenderWindow*);
    sf::Vector2u getSize() const;
  private:
    sf::Texture	_tex;
    sf::Sprite _sprite;
  };
};
