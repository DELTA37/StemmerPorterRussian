#pragma once
#include <regex>
#include <string>
#include <StemmerPorterRussian/Languages/russian.h>

namespace kaspar {

struct PorterRussian : public Russian {
public:
  enum class Group {
    NounEnd,
    VerbEnd,
    PerfectiveGerundEnd,
    ReflexiveEnd,
    AdjectiveEnd,
    AdjectivalEnd,
    Participle1End,
    Participle2End,
    SuperlativeEnd,
    DerivationEnd
  };
public:
  static const std::set<Russian::String> NounEnd;
  static const std::set<Russian::String> VerbEnd;
  static const std::set<Russian::String> Verb1End;
  static const std::set<Russian::String> Verb2End;
  static const std::set<Russian::String> PerfectiveGerundEnd;
  static const std::set<Russian::String> PerfectiveGerund1End;
  static const std::set<Russian::String> PerfectiveGerund2End;
  static const std::set<Russian::String> ReflexiveEnd;
  static const std::set<Russian::String> AdjectiveEnd;
  static const std::set<Russian::String> ParticipleEnd;
  static const std::set<Russian::String> Participle1End;
  static const std::set<Russian::String> Participle2End;
  static const std::set<Russian::String> SuperlativeEnd;
  static const std::set<Russian::String> DerivationEnd;

public:
  PorterRussian(void);
  Russian::String operator()(Russian::String str);

private:
  size_t find_RV(Russian::String const& str);
  size_t find_R1(Russian::String const& str);
  size_t find_R2(Russian::String const& str);
  size_t cut_end(Russian::String const &str, std::set<Russian::String> const &group, size_t begin, size_t end);
};

}; // kaspar
