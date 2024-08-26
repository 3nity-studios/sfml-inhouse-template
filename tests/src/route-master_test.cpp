#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "route-master" ? 0 : 1;
}
