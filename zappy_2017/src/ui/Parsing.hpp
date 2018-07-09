//
// EPITECH PROJECT, 2018
// zappy
// File description:
// ui
//

#pragma once
#include <vector>
#include <string>

namespace Ui {
  class Parsing {
  public:
    Parsing();
    ~Parsing();
    std::vector<std::vector<std::string>> parseIt(std::string);
  };
};
