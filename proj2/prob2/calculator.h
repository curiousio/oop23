#pragma once

#include <vector>

#include "inf_int.h"

class Calculator {
 public:
  Calculator();

  void inputLoop();
  std::vector<std::string> split(std::string, char);

  inf_int add(inf_int, inf_int);
  inf_int sub(inf_int, inf_int);
  inf_int mul(inf_int, inf_int);
};
