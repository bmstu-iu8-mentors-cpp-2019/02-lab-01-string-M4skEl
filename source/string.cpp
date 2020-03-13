// Copyright 2020 ELisey Siver <sivereliseu7@gmail.com>
#include "string.hpp"
#include <algorithm>
#include <cstring>

String::String() {
  Data = new char[0];
  size = 0;
}

String::~String() { delete[] Data; }

String::String(const String& rhs) {
  size = rhs.size;
  Data = new char[size];
  std::copy(rhs.Data, rhs.Data + size, Data);
}

String::String(const char* data) {
  size = strlen(data);
  Data = new char[size];
  std::copy(data, data + size, Data);
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

size_t String::Size() const { return size; }

bool String::Empty() const { return size == 0; }

void String::RTrim(char symbol) {
  size_t i = size - 1;
  int count = 0;
  while (Data[i] == symbol) {
    ++count;
    --i;
  }
  size = size - count;
  char* newData = new char[size];
  for (i = 0; i < size; i++) newData[i] = Data[i];
  delete[] Data;
  Data = newData;
}

void String::LTrim(char symbol) {
  size_t i = 0;
  int count = 0;
  while (Data[i] == symbol) {
    ++i;
    ++count;
  }
  size = size - count;
  char* newData = new char[size];
  for (i = 0; i < size; i++) newData[i] = Data[i + count];
  delete[] Data;
  Data = newData;
}

void String::swap(String& oth) {
  char* buf = new char[size];
  size_t len = size;
  std::copy(Data, Data + size, buf);
  delete[] Data;
  Data = new char[oth.size];
  size = oth.size;
  std::copy(oth.Data, oth.Data + size, Data);
  delete[] oth.Data;
  oth.size = len;
  oth.Data = buf;
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
  if (Data == rhs.Data) return true;
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
  size += rhs.size;
  char* buf = new char[size];
  for (size_t i = 0; i < lenght; i++) {
    buf[i] = Data[i];
  }
  for (size_t j = lenght; j < size; j++) {
    buf[j] = rhs.Data[j - lenght];
  }
  delete[] Data;
  Data = new char[size];
  std::copy(buf, buf + size, Data);
  delete[] buf;
  return *this;
}

bool String::operator<(const String& rhs) const {
  for (size_t i = 0; i < size; i++) {
    if (Data[i] < rhs.Data[i]) {
      return true;
    }
    if (Data[i] > rhs.Data[i]) {
      return false;
    }
  }
  return false;
}

String& String::operator*=(unsigned int m) {
  size_t len = size;
  char* str = new char[size];
  for (size_t i = 0; i < size; i++) str[i] = Data[i];
  delete[] Data;
  size = size * m;
  Data = new char[size];
  for (size_t i = 0; i < size; i++) {
    Data[i] = str[i % len];
  }
  delete[] str;
  return *this;
}

String operator+(const String& a, const String& b) {
  String str;
  str.size = a.size + b.size;
  delete[] str.Data;
  str.Data = new char[str.size];
  std::copy(a.Data, a.Data + a.size, str.Data);
  std::copy(b.Data, b.Data + b.size, str.Data + a.size);
  return str;
}

String operator*(const String& a, unsigned int b) {
  String str;
  str.size = a.size * b;
  delete[] str.Data;
  str.Data = new char[str.size];
  for (size_t i = 0; i < b; i++)
    std::copy(a.Data, a.Data + a.size, str.Data + i * a.size);

  return str;
}

bool operator!=(const String& a, const String& b) { return !(a == b); }

bool operator>(const String& a, const String& b) {
  return !((a < b) || (a == b));
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.size; ++i) {
    out << str.Data[i];
  }
  return out;
}
