#include "inf_int.h"

inf_int::inf_int() {
  this->digits = std::string();

  this->digits.push_back('0');  // default value 0
  this->length = 1;
  this->thesign = true;
}

inf_int::inf_int(int n) {
  char buffer[100];

  if (n < 0) {
    this->thesign = false;
    n = -n;
  } else {
    this->thesign = true;
  }

  int i = 0;
  while (n > 0) {
    buffer[i] = n % 10 + '0';

    n /= 10;
    i++;
  }

  if (i == 0) {
    new (this) inf_int();
  } else {
    buffer[i] = '\0';

    this->digits = std::string();
    this->length = i;
    for (int j = 0; j < i + 1; j++) {
      if (buffer[j] == '\0') {
        break;
      } else {
        this->digits.push_back(buffer[j]);
      }
    }
  }
}

inf_int::inf_int(const char* str) {
  if (str[0] == '-') {
    this->thesign = false;
  } else {
    this->thesign = true;
  }

  this->digits = std::string();
  size_t length = strlen(str);

  if (this->thesign) {
    for (int i = 0; i < length; i++) {
      this->digits.push_back(str[length - 1 - i]);
    }
    this->length = (unsigned int)length;
  } else {
    for (int i = 0; i < length - 1; i++) {
      this->digits.push_back(str[length - 1 - i]);
    }
    this->length = (unsigned int)length - 1;
  }
}

inf_int::inf_int(const inf_int& a) {
  this->digits = std::string();

  for (unsigned int i = 0; i < a.length; i++) {
    this->digits.push_back(a.digits[i]);
  }
  this->length = a.length;
  this->thesign = a.thesign;
}

inf_int::~inf_int() {
  // destructor
}

inf_int& inf_int::operator=(const inf_int& a) {
  this->digits = std::string();

  for (unsigned int i = 0; i < a.length; i++) {
    this->digits.push_back(a.digits[i]);
  }
  this->length = a.length;
  this->thesign = a.thesign;

  return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
  // 0 is always positive
  if ((a.digits == b.digits) && (a.thesign == b.thesign)) {
    return true;
  }
  return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
  return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
  if (a == b) {
    return false;
  } else {
    if (a.thesign && b.thesign) {
      return absCmp(a, b);
    } else if (!a.thesign && !b.thesign) {
      return !absCmp(a, b);
    } else {
      return a.thesign;
    }
  }
}

bool operator<(const inf_int& a, const inf_int& b) {
  if (operator>(a, b) || operator==(a, b)) {
    return false;
  } else {
    return true;
  }
}

inf_int operator+(const inf_int& a, const inf_int& b) {
  inf_int c;
  unsigned int i;
  c.digits = std::string();

  if (a.thesign == b.thesign) {
    if (a.length > b.length) {
      c.Add(a, b);
    } else {
      c.Add(b, a);
    }

    c.length = (unsigned int)c.digits.length();
    c.thesign = a.thesign;

    return c;
  } else {
    c = b;
    c.thesign = a.thesign;

    return a - c;
  }
}

inf_int operator-(const inf_int& a, const inf_int& b) {
  inf_int c;
  c.digits = std::string();

  if (absCmp(a, b)) {  // a > b
    if (a.thesign == b.thesign) {
      c.Sub(a, b);
      c.thesign = a.thesign;
    } else {
      inf_int temp = b;
      temp.thesign = a.thesign;
      c = a + temp;
    }
  } else if (a.digits == b.digits) {  // a == b
    if (a.thesign == b.thesign) {
      c = inf_int();  // return 0
    } else {
      c = a + a;
      c.thesign = a.thesign;
    }
  } else {  // a < b
    if (a.thesign == b.thesign) {
      c.Sub(b, a);
      if (a.thesign) {
        c.thesign = false;
      } else {
        c.thesign = true;
      }
    } else {
      inf_int temp = b;
      temp.thesign = a.thesign;
      c = a + temp;
    }
  }

  return c;
}

inf_int operator*(const inf_int& a, const inf_int& b) {
  inf_int c;

  if (isZero(a) || isZero(b)) {
    c = inf_int();
    return c;
  } else {
    c.digits = std::string(a.length + b.length, 0);
    if (a.thesign == b.thesign) {
      c.thesign = true;
    } else {
      c.thesign = false;
    }

    for (unsigned int i = 0; i < a.length; i++) {
      for (unsigned int j = 0; j < b.length; j++) {
        int production =
            c.digits[i + j] + (a.digits[i] - '0') * (b.digits[j] - '0');
        c.digits[i + j] = (char)production % 10;
        c.digits[i + j + 1] += production / 10;
      }
    }
    for (int i = 0; i < c.digits.length(); i++) {
      c.digits[i] += '0';
    }

    if (c.digits[c.digits.length() - 1] == '0') {
      c.digits = c.digits.substr(0, c.digits.length() - 1);
    }
    c.length = (unsigned int)c.digits.length();

    return c;
  }
}

std::ostream& operator<<(std::ostream& out, const inf_int& a) {
  if (a.thesign == false) {
    out << '-';
  }
  for (int i = a.length - 1; i >= 0; i--) {
    out << a.digits[i];
  }
  return out;
}

void inf_int::Add(const inf_int& a, const inf_int& b) {
  int carry = 0;

  for (unsigned int i = 0; i < b.length; i++) {
    int addition = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
    this->digits.push_back(addition % 10 + '0');
    carry = addition / 10;
  }

  for (unsigned int i = b.length; i < a.length; i++) {
    int addition = ((a.digits[i] - '0') + carry);
    this->digits.push_back(addition % 10 + '0');
    carry = addition / 10;
  }

  if (carry) {
    this->digits.push_back(carry + '0');
  }
}

void inf_int::Sub(const inf_int& a, const inf_int& b) {
  int carry = 0;

  for (unsigned int i = 0; i < b.length; i++) {
    int subtraction = ((a.digits[i] - '0') - (b.digits[i] - '0') - carry);
    if (subtraction < 0) {
      subtraction = subtraction + 10;
      carry = 1;
    } else {
      carry = 0;
    }
    this->digits.push_back(subtraction + '0');
  }

  for (unsigned int i = b.length; i < a.length; i++) {
    int subtraction = ((a.digits[i] - '0') - carry);
    if (subtraction < 0) {
      subtraction = subtraction + 10;
      carry = 1;
    } else {
      carry = 0;
    }
    this->digits.push_back(subtraction + '0');
  }

  unsigned int countZero = 0;
  for (unsigned int i = (unsigned int)this->digits.length() - 1; i > 0; i--) {
    if (this->digits[i] == '0') {
      countZero++;
    } else {
      break;
    }
  }
  this->digits = this->digits.substr(0, this->digits.length() - countZero);
  this->length = (unsigned int)this->digits.length();
}

bool absCmp(const inf_int& a, const inf_int& b) {
  if (a.length > b.length) {
    return true;
  } else if (a.length < b.length) {
    return false;
  } else {
    for (unsigned int i = 0; i < a.length; i++) {
      if (a.digits[i] > b.digits[i]) {
        return true;
      } else if (a.digits[i] < b.digits[i]) {
        return false;
      }
    }
    return false;
  }
}

bool isZero(const inf_int& a) {
  return (a.length == 1 && a.digits[a.length - 1] == '0' && a.thesign == true);
}
