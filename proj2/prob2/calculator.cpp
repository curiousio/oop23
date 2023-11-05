#include "calculator.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Calculator::Calculator() { inputLoop(); }

void Calculator::inputLoop() {
  string input;

  while (true) {
    cout << "Input: ";
    getline(cin, input);
    if (input == "0") {
      break;
    }

    vector<string> result = split(input, ' ');
    inf_int operand1 = inf_int(result[0].c_str());
    string op = result[1];
    inf_int operand2 = inf_int(result[2].c_str());

    if (op.compare("+") == 0) {
      cout << "Output: " << add(operand1, operand2) << endl;
    } else if (op.compare("-") == 0) {
      cout << "Output: " << sub(operand1, operand2) << endl;
    } else if (op.compare("*") == 0) {
      cout << "Output: " << mul(operand1, operand2) << endl;
    } else {
      cout << "[Error] Unsupported operator" << endl;
    }
  }
}

vector<string> Calculator::split(string str, char delim) {
  istringstream iss(str);
  string buffer;
  vector<string> result;

  while (getline(iss, buffer, delim)) {
    result.push_back(buffer);
  }

  return result;
}

inf_int Calculator::add(inf_int a, inf_int b) { return a + b; }

inf_int Calculator::sub(inf_int a, inf_int b) { return a - b; }

inf_int Calculator::mul(inf_int a, inf_int b) { return a * b; }
