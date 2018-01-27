#include <StemmerPorterRussian/Languages/russian.h>
#include <StemmerPorterRussian/PorterRussian/porter_russian.h>
#include <iostream>
#include <locale>

using namespace kaspar;

int main(void) {
  PorterRussian pr;
  std::wstring text;
  std::getline(std::wcin, text);
  std::wcout << pr(text) << std::endl;
  
  return 0;
}
