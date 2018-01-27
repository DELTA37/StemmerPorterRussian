add_executable(stemmer bin/stemmer.cpp)
add_library(Stemmers PorterRussian/porter_russian.cpp)
add_library(Languages Languages/russian.cpp)

target_link_libraries(stemmer Stemmers Languages)
