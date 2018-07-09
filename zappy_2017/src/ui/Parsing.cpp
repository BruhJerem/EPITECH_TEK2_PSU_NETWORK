//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ui
//

#include "Parsing.hpp"
#include <iostream>

Ui::Parsing::Parsing()
{
  /*_cmd.push_back("msz");
  _cmd.push_back("bct");
  _cmd.push_back("tna");
  _cmd.push_back("pnw");
  _cmd.push_back("ppo");
  _cmd.push_back("plv");
  _cmd.push_back("pin");
  _cmd.push_back("pex");
  _cmd.push_back("pbc");
  _cmd.push_back("pic");
  _cmd.push_back("pie");
  _cmd.push_back("pfk");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");
  _cmd.push_back("msz");*/

}

Ui::Parsing::~Parsing()
{

}

std::vector<std::vector<std::string>> Ui::Parsing::parseIt(std::string line)
{
  std::vector<std::vector<std::string>> newCmd;
  std::vector<std::string> cmd;
  size_t i = 0;
  std::string tmp;

  while (i != line.size() ) {
    if (line[i] != ' ' && line[i] != '\n')
      tmp = tmp + line[i];
    else {
      cmd.push_back(tmp);
      tmp.clear();
    }
    if (line[i] == '\n') {
      newCmd.push_back(cmd);
      cmd.clear();
    }
    i++;
  }
  return (newCmd);
}
