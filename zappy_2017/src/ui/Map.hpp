//
// EPITECH PROJECT, 2018
// zappy
// File description:
// map
//

#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Sprite.hpp"

namespace Ui {

  struct slot {
    std::unordered_map<std::string, std::vector<int> > player;
  };
  typedef struct slot slot_t;

  class Map {
  public:
    Map();
    ~Map();
    void createMap(int, int);
    void removeFromMap(std::string, int, int, int);
    void addToMap(int x, int y, std::string name, int id, std::string team, int o);
    void addToMap(int, int, std::string, int);
    std::vector<std::vector<slot_t> > getMap();
    std::vector<std::vector<Sprite*> > getSpriteMap() const;
    sf::Vector2u  getSizeOfSlot() const;
    sf::Vector2f getPosOfSlot(int x, int y) const;
    void newScale(int x, int y);
    float getScale() const;
    sf::Vector2u findIndex(int, std::string);
    void newPos(int, size_t, size_t);
    void takeIt(int, int);
    void leaveIt(int, int);
    void spanwEgg(int, int, int);
  private:
    std::vector<std::vector<slot_t> > _map;
    std::vector<std::vector<Sprite*> > _spriteMap;
    float _mapScale;
    std::unordered_map<std::string, std::vector<int>> teams;
    std::unordered_map<int, sf::Vector2u> _playerPos;
    std::unordered_map<int, sf::Vector2u> _eggPos;
    std::unordered_map<int, std::string> _itemIndex;
    std::unordered_map<int, int> _playerDirection;
  };
};
