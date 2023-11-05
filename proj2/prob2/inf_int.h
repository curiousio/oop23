#ifndef _INF_INT_H_
#define _INF_INT_H_

#include <iostream>

class inf_int {
 private:
  std::string digits;
  unsigned int length;
  bool thesign;  // true if positive and false if negative

  void Add(const inf_int&, const inf_int&);
  void Sub(const inf_int&, const inf_int&);
  friend bool absCmp(const inf_int&, const inf_int&);
  friend bool isZero(const inf_int&);

 public:
  inf_int();  // assign 0 as a default value
  inf_int(int);
  inf_int(const char*);
  inf_int(const inf_int&);  // copy constructor
  ~inf_int();               // destructor

  inf_int& operator=(const inf_int&);  // assignment operator

  friend bool operator==(const inf_int&, const inf_int&);
  friend bool operator!=(const inf_int&, const inf_int&);
  friend bool operator>(const inf_int&, const inf_int&);
  friend bool operator<(const inf_int&, const inf_int&);

  friend inf_int operator+(const inf_int&, const inf_int&);
  friend inf_int operator-(const inf_int&, const inf_int&);
  friend inf_int operator*(const inf_int&, const inf_int&);
  // friend inf_int operator/(const inf_int&, const inf_int&);  // not required

  friend std::ostream& operator<<(std::ostream&, const inf_int&);
  // friend istream& operator>>(istream&, inf_int&);  // not required
};

#endif
