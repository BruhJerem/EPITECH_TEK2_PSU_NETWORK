//
// EPITECH PROJECT, 2018
// zappy
// File description:
// window
//

#include "Window.hpp"

Ui::Window::Window()
{
  _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Zappy");
  _backgound = new Sprite("./media/water.png");
  _co = new ConnectionHandler();
  _map = new Map();
  _things.push_back("food");
  _things.push_back("ore1");
  _things.push_back("ore2");
  _things.push_back("ore3");
  _things.push_back("ore4");
  _things.push_back("ore5");
  _things.push_back("ore6");
  _lineToRead = "";
  //fillFuncMap();
}

Ui::Window::~Window()
{
  delete _window;
  delete _map;
  delete _backgound;
  delete _co;
}

void Ui::Window::fillFuncMap()
{
  //_funcMap["msz"] = &createMap;
}

void Ui::Window::createMap(std::vector<std::string> line)
{
  _map->createMap(atoi(line[1].c_str()), atoi(line[2].c_str()));
}

void Ui::Window::run(std::string ip, std::string port)
{
  int ret = 0;

  //_funcMap[line[0]](line);
  _co->setIpandPort(ip, port);
  std::thread th(Ui::ConnectionHandler::readSocket, &_lineToRead, _co->getSocket());
  while (_window->isOpen() && ret == 0) {
    event();
    ret = update();
    display();
  }
  _lineToRead = "seg\n";
  th.join();
}

void Ui::Window::event()
{
  sf::Event event;

  while (_window->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
          _window->close();
  }
}

int Ui::Window::update()
{
  size_t i = 0;
  std::vector<std::vector<std::string >> bigLine;
  bigLine = _parse->parseIt(_lineToRead);
  _lineToRead.clear();

  while (i != bigLine.size()) {
    std::vector<std::string> line = bigLine[i];
    if (line.size() != 0 && line[0] == "msz")
      createMap(line);
    else if (line.size() != 0 && line[0] == "pnw")
      _map->addToMap(atoi(line[3].c_str()), atoi(line[2].c_str()), "pion", atoi(line[1].c_str()), line[6], atoi(line[4].c_str()));
    else if (line.size() != 0 && line[0] == "bct")
      fillMap(line);
    else if (line.size() != 0 && line[0] == "pdi")
      removePlayer(atoi(line[1].c_str()), "pion");
    else if (line.size() != 0 && line[0] == "ppo")
      _map->newPos(atoi(line[1].c_str()), atoi(line[2].c_str()), atoi(line[3].c_str()));
    else if (line.size() != 0 && line[0] == "pgt")
      _map->takeIt(atoi(line[1].c_str()), atoi(line[2].c_str()));
    else if (line.size() != 0 && line[0] == "pdr")
      _map->leaveIt(atoi(line[1].c_str()), atoi(line[2].c_str()));
    else if (line.size() != 0 && line[0] == "enw")
      _map->leaveIt(atoi(line[1].c_str()), -1);
    else if (line.size() != 0 && line[0] == "edi")
      removePlayer(atoi(line[1].c_str()), "egg");
    else if (line.size() != 0 && line[0] == "seg")
      return 1;
    i++;
  }
  return 0;
}

void Ui::Window::removePlayer(int index, std::string name)
{
  sf::Vector2u pos;
  pos = _map->findIndex(index, name);
  _map->removeFromMap(name, pos.x, pos.y, index);
}

void Ui::Window::fillMap(std::vector<std::string> line)
{
  int x = atoi(line[2].c_str());
  int y = atoi(line[1].c_str());

  for (size_t i = 0; i != _things.size(); i++) {
    for (int nb = 0; nb != atoi(line[i + 3].c_str()); nb ++)
      _map->addToMap(x, y, _things[i], 0);
  }
}

void Ui::Window::display()
{
  std::vector<std::vector<slot_t> > map;
  int y = 0;

  map = _map->getMap();
  _window->clear();
  _backgound->draw(_window);
  for (auto l = map.begin(); l != map.end(); l++) {
    int x = 0;
    for (auto j = (*l).begin(); j != (*l).end(); j++) {
      _map->getSpriteMap()[y][x]->draw(_window);
      x++;
    }
    y++;
  }
  y = 0;
  for (auto l = map.begin(); l != map.end(); l++) {
    int x = 0;
    for (auto j = (*l).begin(); j != (*l).end(); j++) {
      spawnPlayer(map[y][x], x, y);
      x++;
    }
    y++;
  }
  _window->display();
}

void Ui::Window::spawnPlayer(slot_t slot, int x, int y)
{
  size_t other = 0;

  for (auto it = slot.player.begin(); it != slot.player.end(); ++it) {
    size_t index = 0;
    while (index != slot.player[it->first].size()) {
      Sprite tmp("./media/" + it->first + ".png");
      float decX = 0;
      float decY = 0;
      tmp.setScale(_map->getScale());
      if (other > 1) {
        decY = 1;
        decX = other - 2;
      }
      else
       decX = other;
      if (it->first != "pion") {
        decX += 1;
        decY += 1;
      }
      tmp.setPos(_map->getPosOfSlot(x, y).x + decX * (tmp.getSize().x / 1.4), _map->getPosOfSlot(x, y).y + decY * (tmp.getSize().y / 1.4));
      tmp.draw(_window);
      other++;
      index++;
    }
  }
}
