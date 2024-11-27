add_library(utils SHARED
  input.cpp)

include_directories(.)
set_target_properties(utils PROPERTIES PUBLIC_HEADER input.hpp)