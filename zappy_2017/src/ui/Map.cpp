//
// EPITECH PROJECT, 2018
// zappy
// File description:
// map
//

#include "Map.hpp"
#include <iostream>

Ui::Map::Map()
{
  _mapScale = 1;
  _itemIndex[-1] = "egg";
  _itemIndex[0] = "food";
  _itemIndex[1] = "ore1";
  _itemIndex[2] = "ore2";
  _itemIndex[3] = "ore3";
  _itemIndex[4] = "ore4";
  _itemIndex[5] = "ore5";
  _itemIndex[6] = "ore6";
}

Ui::Map::~Map()
{
  int y = 0;

  _map.clear();
  for (auto l = _spriteMap.begin(); l != _spriteMap.end(); l++) {
    int x = 0;
    for (auto j = (*l).begin(); j != (*l).end(); j++) {
      delete _spriteMap[y][x];
      x++;
    }
    y++;
  }
  _spriteMap.clear();
}

void Ui::Map::newScale(int x, int y)
{
  Sprite tmp("./media/ground.png");
  float ratio = 1;
  float ratio2 = 1;

  while (y * tmp.getSize().x * ratio > 1920) {
    ratio -= 0.1;
  }
  while (x * tmp.getSize().y * ratio2 > 1080) {
    ratio2 -= 0.1;
  }
  if (ratio < ratio2)
    _mapScale = ratio;
  else
    _mapScale = ratio2;
  if (_mapScale == 0)
    _mapScale = 0.1;
}

void Ui::Map::newPos(int id, size_t x, size_t y)
{
  std::string team("");

  if (_playerPos[id].x != x || _playerPos[id].y != y) {
      for (auto it = teams.begin(); it != teams.end(); it++) {
        for (size_t i = 0; i != teams[it->first].size(); i++) {
          if (id == teams[it->first][i])
            team = it->first;
        }
      }
      removeFromMap("pion", _playerPos[id].x, _playerPos[id].y, id);
      addToMap(y, x, "pion", id, team, 0);
    }
}

void Ui::Map::takeIt(int index, int i)
{
  sf::Vector2u pos = _playerPos[index];

  removeFromMap(_itemIndex[i], pos.x, pos.y, -1);
}

void Ui::Map::leaveIt(int index, int i)
{
  sf::Vector2u pos = _playerPos[index];

  addToMap(pos.y, pos.x, _itemIndex[i], -1);
}

void Ui::Map::spanwEgg(int index, int x, int y)
{
  sf::Vector2u tmp(x, y);
  addToMap(x, y, "egg", index);
  _eggPos[index] = tmp;
}

void Ui::Map::createMap(int x, int y)
{
  slot_t slot;

  newScale(x, y);
  for (auto i = 0; i != y; i++) {
    std::vector<slot_t> tmp;
    std::vector<Sprite*> tmp2;
    for (int j = 0; j != x; j++) {
      Sprite *sp = new Sprite("./media/ground.png");
      sp->setScale(_mapScale);
      sp->setPos((i * sp->getSize().y / 1.15) + (1920 / 2 - y * sp->getSize().y / 1.15 / 2) - sp->getSize().y / 1.15 / 2,
      (j * sp->getSize().x / 1.15) + (1080 / 2 - x * sp->getSize().x / 1.15 / 2) - sp->getSize().x / 1.15 / 2);
      tmp2.push_back(sp);
      tmp.push_back(slot);
    }
    _spriteMap.push_back(tmp2);
    _map.push_back(tmp);
  }
}

float Ui::Map::getScale() const
{
  return _mapScale;
}

void Ui::Map::addToMap(int x, int y, std::string name, int id, std::string team, int o)
{
    (void)o;
    _map[y][x].player[name].push_back(id);
    teams[team].push_back(id);
    _playerPos[id] = sf::Vector2u(y, x);
    _playerDirection[id] = 0;
}

void Ui::Map::addToMap(int x, int y, std::string name, int id)
{
    _map[y][x].player[name].push_back(id);
}

void Ui::Map::removeFromMap(std::string name, int x, int y, int id)
{
  _map[x][y].player[name].pop_back();
  for (auto it = teams.begin(); it != teams.end(); ++it) {
    for (size_t i = 0; i != teams[it->first].size(); i++) {
      if (teams[it->first][i] == id) {
        teams[it->first].erase(teams[it->first].begin() + i);
        if (name == "pion") {
          _playerPos.erase(id);
          _playerDirection.erase(id);
        }
        else
          _itemIndex.erase(id);
        break;
      }
    }
  }
}

sf::Vector2u Ui::Map::findIndex(int index, std::string name)
{
  if (name == "pion")
    return _playerPos[index];
  else
    return _eggPos[index];
}

std::vector<std::vector<Ui::slot_t>> Ui::Map::getMap()
{
  return _map;
}

std::vector<std::vector<Ui::Sprite*> > Ui::Map::getSpriteMap() const
{
  return _spriteMap;
}

sf::Vector2u Ui::Map::getSizeOfSlot() const
{
  return _spriteMap[0][0]->getSize();
}

sf::Vector2f Ui::Map::getPosOfSlot(int x, int y) const
{
  return sf::Vector2f(_spriteMap[y][x]->getPos());
}
