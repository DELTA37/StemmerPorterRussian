#pragma once
#include <string>
#include <set>

namespace kaspar {

struct Russian {
public:
  typedef std::wstring String;
  typedef wchar_t Char;

public:
  static const std::set<Char> vowels; 
  static const std::set<Char> consonants; 

public:
  Russian(void);
  ~Russian(void);
};


}; // kaspar
