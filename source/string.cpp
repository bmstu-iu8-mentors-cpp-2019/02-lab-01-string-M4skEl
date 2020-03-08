// Copyright 2020 ELisey Siver <sivereliseu7@gmail.com>
#include "string.hpp"
#include <cstring>

String::String() {
  Data = new char[0];
  size = 0;
}
String::~String() {
  delete[] Data;
  size = 0;
}
String::String(const String& rhs) {
  size = rhs.size;
  Data = new char[size];
  for (size_t i = 0; i < size; i++) Data[i] = rhs.Data[i];
}

String::String(const char* data) {
  size = strlen(data) - 1;
  Data = new char[size];
  for (size_t i = 0; i < size; i++) Data[i] = data[i];
}
size_t String::Find(const String& substr) const {
  for (size_t i = 0; i < size; i++) {
    if (Data[i] == substr.Data[0]) {
      for (size_t j = 0; j < substr.size; j++) {
        if (Data[i + j] != substr[j]) break;
        if (j == substr.size - 1) return i;
      }
    }
  }
  return -1;
}
void String::Replace(char oldSymbol, char newSymbol) {
  for (size_t i = 0; i < size; i++) {
    if (Data[i] == oldSymbol) Data[i] = newSymbol;
  }
}
size_t String::Size() const { return strlen(Data)-1; }
bool String::Empty() const {
  if (size == 0)
    return true;
  else
    return false;
}
void String::RTrim(char symbol) {
  char* newData = new char[size];
  for (size_t i = 0; i < size; i++) newData[i] = Data[i];
  // std::copy(Data, &Data[size - 1], &newData[0]);
  size_t i = size - 1;
  int count = 0;
  while (newData[i] == symbol) {
    ++count;
    --i;
  }
  delete[] Data;
  size = size - count;
  Data = new char[size];
  for (size_t j = 0; j < size; j++) {
    Data[j] = newData[j];
  }
}
void String::LTrim(char symbol) {
  char* newData = new char[size];
  for (size_t i = 0; i < size; i++) newData[i] = Data[i];
  // std::copy(Data, &Data[size - 1], &newData[0]);
  size_t i = 0, count = 0;
  while (newData[i] == symbol) {
    i++;
    count++;
  }
  delete[] Data;
  size = size - count;
  Data = new char[size];
  for (size_t j = 0; j < size; j++) {
    Data[j] = newData[j + count];
  }
}
void String::swap(String& oth) {
  char* buf = new char[size];
  int len = size;
  for (size_t i = 0; i < size; i++) buf[i] = Data[i];
  delete[] Data;
  Data = new char[oth.size];
  size = oth.size;
  for (size_t i = 0; i < size; i++) Data[i] = oth.Data[i];
  delete[] oth.Data;
  oth.size = len;
  oth.Data = new char[oth.size];
  for (size_t i = 0; i < oth.size; i++) oth.Data[i] = buf[i];
}
String& String::operator=(const String& rhs) {
  delete[] Data;
  size = rhs.size;
  Data = new char[size];
  for (size_t i = 0; i < size; i++) Data[i] = rhs.Data[i];
  return *this;
}
char String::operator[](size_t index) const { return Data[index]; }
char& String::operator[](size_t index) { return Data[index]; }
bool String::operator==(const String& rhs) const {
  size_t count = 0;
  if (size == rhs.size) {
    for (size_t i = 0; i < size; i++) {
      count++;
      if (Data[i] != rhs.Data[i]) break;
    }
    if (count == size) return true;
  }
  return false;
}
String& String::operator+=(const String& rhs) {
  size_t lenght = size;
  size = size + rhs.size;
  char* buf = new char[size];
  for (size_t i = 0; i < lenght; i++) {
    buf[i] = Data[i];
  }
  for (size_t j = lenght; j < size; j++) {
    buf[j] = rhs.Data[j];
  }
  delete[] Data;
  Data = new char[size];
  for (size_t i = 0; i < size; i++) Data[i] = buf[i];
  return *this;
}
bool String::operator<(const String& rhs) const {
  for (size_t i = 0; i < size; i++) {
    if (Data[i] > rhs.Data[i]) {
      return true;
    }
    if (Data[i] < rhs.Data[i]) {
      return false;
    }
  }
  return false;
}
String& String::operator*=(unsigned int m) {
  // String str = String(Data);
  size_t len = size;
  char* str = new char[size];
  for (size_t i = 0; i < size; i++) str[i] = Data[i];
  delete[] Data;
  size = size * m;
  Data = new char[size];
  for (size_t i = 0; i < size + 1; i++) {
    Data[i] = str[i % len];
  }
  return *this;
}
String operator+(const String& a, const String& b) {
  String str;
  str += a;
  str += b;
  return str;
}
String operator*(const String& a, unsigned int b) {
  String str;
  for (size_t i = 0; i < b; i++) {
    str += a;
  }
  return str;
}
bool operator!=(const String& a, const String& b) {
  if (a == b) {
    return false;
  } else {
    return true;
  }
}
bool operator>(const String& a, const String& b) {
  if ((a < b) || (a == b))
    return false;
  else
    return true;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.size; ++i) {
    out << str.Data[i];
  }
  return out;
}
