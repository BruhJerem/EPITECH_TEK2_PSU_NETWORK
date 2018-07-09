//
// EPITECH PROJECT, 2018
// zappy
// File description:
// sprite
//

#include "Sprite.hpp"

Ui::Sprite::Sprite(std::string name) :
  _tex(), _sprite()
{
  Sprite::setTex(name);
}

Ui::Sprite::~Sprite()
{
}

void Ui::Sprite::setTex(std::string name)
{
  _tex.loadFromFile(name);
  Sprite::setSprite();
}

sf::Texture Ui::Sprite::getTex() const
{
  return _tex;
}


void Ui::Sprite::setSprite()
{
  _sprite.setTexture(_tex);
}

sf::Sprite Ui::Sprite::getSprite() const
{
  return _sprite;
}

void Ui::Sprite::setPos(float x, float y)
{
  _sprite.setPosition(x, y);
}

sf::Vector2f Ui::Sprite::getPos() const
{
  return _sprite.getPosition();
}

void Ui::Sprite::setScale(float x)
{
  _sprite.setScale(x, x);
}

void Ui::Sprite::draw(sf::RenderWindow *win)
{
  win->draw(_sprite);
}

sf::Vector2u Ui::Sprite::getSize() const
{
  sf::Vector2u tmp = _tex.getSize();

  tmp.x *= getScale();
  tmp.y *= getScale();
  return tmp;
}

float Ui::Sprite::getScale() const
{
  return _sprite.getScale().x;
}
