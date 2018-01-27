#include <StemmerPorterRussian/Languages/russian.h>

namespace kaspar {

const std::set<Russian::Char> Russian::vowels({L'а', L'у', L'о', L'ы', L'и', L'э', L'я', L'ю', L'ё', L'е'});
const std::set<Russian::Char> Russian::consonants({L'б', L'в', L'г', L'д', L'ж', L'з', L'й', L'к', L'л', L'м', L'н', L'п', L'р', L'с', L'т', L'ф', L'х', L'ц', L'ч', L'ш', L'щ'});

Russian::Russian(void) {
  setlocale(LC_ALL, "ru_RU.UTF-8");
}

Russian::~Russian(void) {
  setlocale(LC_ALL, "");
}

}; // kaspar
