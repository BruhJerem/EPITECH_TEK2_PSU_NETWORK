//
// EPITECH PROJECT, 2018
// zappy
// File description:
// main ui
//

#include "Window.hpp"

int main(int av, char **ag)
{
  Ui::Window *win = new Ui::Window();

  if (av == 3) {
    win->run(ag[1], ag[2]);
  }
  delete win;
  return (0);
}
