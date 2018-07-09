//
// EPITECH PROJECT, 2018
// zappy
// File description:
// window
//


#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <thread>
#include "ConnectionHandler.hpp"
#include "Sprite.hpp"
#include "Parsing.hpp"
#include "Map.hpp"

namespace Ui {
  class Window {
  public:
    Window();
    ~Window();
    void run(std::string, std::string);
  private:
    void fillMap(std::vector<std::string>);
    void createMap(std::vector<std::string>);
    void fillFuncMap();
    void event();
    int update();
    void display();
    void spawnPlayer(slot_t , int x, int y);
    void removePlayer(int, std::string);
    sf::RenderWindow *_window;
    Map *_map;
    Sprite *_backgound;
    ConnectionHandler *_co;
    Parsing *_parse;
    std::vector<std::string> _things;
    std::string _lineToRead;
    //std::unordered_map<std::string, void (*)(std::vector<std::string>)> _funcMap;
  };
};
