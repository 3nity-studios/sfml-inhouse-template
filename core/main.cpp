// #include "core/module/include/lib.hpp"
#include "config/include/game.hpp"
#include "config/include/global.hpp"

#include <iostream>
#include <string>

int main()
{

#if defined(_DEBUG)
    // auto const lib = library{};
    // auto const message = "Running" + lib.name + "version " + config.version + "!";
    // std::cout << message << '\n';

#endif
    Game();

    return 0;
}
