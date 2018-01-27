#include <StemmerPorterRussian/PorterRussian/porter_russian.h>
#include <cctype>
#include <cwctype>
#include <algorithm>
#include <iostream>

namespace kaspar {

const std::set<Russian::String> PorterRussian::NounEnd({L"а", L"ев", L"ов", L"ие", L"ье", L"е", L"иями", L"ями", L"ами", L"еи", L"ии", L"и", L"ией", L"ей", L"ой", L"ий", L"й", L"иям", L"ям", L"ием", L"ем", L"ам", L"ом", L"о", L"у", L"ах", L"иях", L"ях", L"ы", L"ь", L"ию", L"ью", L"ю", L"ия", L"ья", L"я"});
const std::set<Russian::String> PorterRussian::ReflexiveEnd({ L"ся", L"сь" });
const std::set<Russian::String> PorterRussian::SuperlativeEnd({ L"ейше", L"ейш" });
const std::set<Russian::String> PorterRussian::Participle1End({ L"ем", L"нн", L"вш", L"ющ", L"щ"});
const std::set<Russian::String> PorterRussian::Participle2End({ L"ивш", L"ывш", L"ующ" });
const std::set<Russian::String> PorterRussian::ParticipleEnd({ L"ем", L"нн", L"вш", L"ющ", L"щ", L"ивш", L"ывш", L"ующ" });
const std::set<Russian::String> PorterRussian::AdjectiveEnd({ L"ее", L"ие", L"ые", L"ое", L"ими", L"ыми", L"ей", L"ий", L"ый", L"ой", L"ем", L"им", L"ым", L"ом", L"его", L"ого", L"ему", L"ому", L"их", L"ых", L"ую", L"юю", L"ая", L"яя", L"ою", L"ею" });
const std::set<Russian::String> PorterRussian::DerivationEnd({ L"ост", L"ость" });
const std::set<Russian::String> PorterRussian::PerfectiveGerund1End({ L"в", L"вши", L"вшись" });
const std::set<Russian::String> PorterRussian::PerfectiveGerund2End({ L"ив", L"ивши", L"ившись", L"ыв", L"ывши", L"ывшись" });
const std::set<Russian::String> PorterRussian::PerfectiveGerundEnd({ L"в", L"вши", L"вшись", L"ив", L"ивши", L"ившись", L"ыв", L"ывши", L"ывшись" });
const std::set<Russian::String> PorterRussian::Verb1End({L"ла", L"на", L"ете", L"йте", L"ли", L"й", L"л", L"ем", L"н", L"ло", L"но", L"ет", L"ют", L"ны", L"ть", L"ешь", L"нно" });
const std::set<Russian::String> PorterRussian::Verb2End({ L"ила", L"ыла", L"ена", L"ейте", L"уйте", L"ите", L"или", L"ыли", L"ей", L"уй", L"ил", L"ыл", L"им", L"ым", L"ен", L"ило", L"ыло", L"ено", L"ят", L"ует", L"уют", L"ит", L"ыт", L"ены", L"ить", L"ыть", L"ишь", L"ую", L"ю" });
const std::set<Russian::String> PorterRussian::VerbEnd({L"ла", L"на", L"ете", L"йте", L"ли", L"й", L"л", L"ем", L"н", L"ло", L"но", L"ет", L"ют", L"ны", L"ть", L"ешь", L"нно", L"ила", L"ыла", L"ена", L"ейте", L"уйте", L"ите", L"или", L"ыли", L"ей", L"уй", L"ил", L"ыл", L"им", L"ым", L"ен", L"ило", L"ыло", L"ено", L"ят", L"ует", L"уют", L"ит", L"ыт", L"ены", L"ить", L"ыть", L"ишь", L"ую", L"ю" });


PorterRussian::PorterRussian(void) : Russian() {}

size_t PorterRussian::find_RV(Russian::String const& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (Russian::vowels.count(str[i]) > 0) {
      return i + 1;
    }
  }
  return -1;
}

size_t PorterRussian::find_R1(Russian::String const& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (Russian::vowels.count(str[i]) > 0) {
      for (size_t j = i + 1; j < str.size(); ++j) {
        if (Russian::vowels.count(str[j]) == 0) {
          return j + 1;
        }
      }
      break;
    }
  }
  return -1;
}

size_t PorterRussian::find_R2(Russian::String const& str) {
  size_t pos = find_R1(str);

  for (size_t i = pos; i < str.size(); ++i) {
    if (Russian::vowels.count(str[i]) > 0) {
      for (size_t j = i + 1; j < str.size(); ++j) {
        if (Russian::vowels.count(str[j]) == 0) {
          return j + 1;
        }
      }
      break;
    }
  }
  return -1;
}


inline size_t _cut_end(Russian::Char const *cstr, size_t size, std::set<Russian::String> const &group) {
  for (size_t i = 0; i < size; ++i) {
    if (group.count(&(cstr[i])) > 0) {
      return i;
    }
  }
  return -1;
}

size_t PorterRussian::cut_end(Russian::String const& str, std::set<Russian::String> const &group, size_t begin, size_t end) {
  return _cut_end(str.c_str() + begin, end - begin, group);
}

Russian::String PorterRussian::operator()(Russian::String str) {
  std::transform(str.begin(), str.end(), str.begin(), std::towlower);
  size_t rv = find_RV(str);
  if (rv == -1) {
    return str;
  }

  // step 1
  size_t pos = str.size();
  size_t tmp = -1;
  if (pos >= rv + 1) {
    if (tmp == -1) {
      tmp = cut_end(str, PerfectiveGerundEnd, rv, pos);
      tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
    }
    
    
    if (tmp == -1) {
      tmp = cut_end(str, ReflexiveEnd, rv, pos);
      tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
    }


    if (tmp == -1) {
      size_t tmp2;
      tmp = cut_end(str, AdjectiveEnd, rv, pos);
      tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
      if (tmp == -1) {
        tmp = cut_end(str, ParticipleEnd, rv, pos);
        tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
      } else {
        tmp2 = cut_end(str, ParticipleEnd, rv, tmp);
        tmp2 += (tmp2 != -1) * rv; // if -1 do nothing else add rv
        tmp = (tmp2 == -1) ? tmp : tmp2;
      }
    }
    
    if (tmp == -1) {
      tmp = cut_end(str, VerbEnd, rv, pos);
      tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
    }

    if (tmp == -1) {
      tmp = cut_end(str, NounEnd, rv, pos);
      tmp += (tmp != -1) * rv; // if -1 do nothing else add rv
    }

    pos = (tmp == -1) ? pos : tmp;
  }
  // step 2
  if ((pos >= rv + 1) && (pos >= 1) && (str[pos - 1] == L'и')) {
    --pos;
  }

  // step 3
  size_t r2 = find_R2(str);
  if (pos >= r2 + 1) {
    tmp = -1;
    tmp = (r2 != -1) ? cut_end(str, DerivationEnd, r2, pos) : tmp;
    tmp += (tmp != -1 && r2 != -1) * r2; // if -1 do nothing else add r2

    pos = (tmp == -1) ? pos : tmp;
  }

  // step 4
  if (pos >= rv + 1) {
    if (((pos >= 1) && (str[pos - 1] == L'ь')) || ((pos >= 2) && (str[pos - 1] == str[pos - 2]) && (str[pos - 1] == L'н'))) {
      --pos;
    } else {
      tmp = cut_end(str, SuperlativeEnd, rv, pos);
      pos = (tmp == -1) ? pos : tmp + rv;
      if ((pos >= rv + 1) && (pos >= 2) && (str[pos - 1] == str[pos - 2]) && (str[pos - 1] == L'н')) {
        --pos;
      }
    }
  }

  return str.substr(0, pos);
}

}; // kaspar
