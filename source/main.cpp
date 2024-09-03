// // #include "core/module/include/lib.hpp"
// #include "config/include/game.hpp"
// #include "config/include/global.hpp"

// #include <iostream>
// #include <string>

// int main()
// {

// #if defined(_DEBUG)
//     // auto const lib = library{};
//     // auto const message = "Running" + lib.name + "version " + config.version + "!";
//     // std::cout << message << '\n';

// #endif
//     Game();

//     return 0;
// }

#include "SFMLOrthogonalLayer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    tmx::Map map;
    map.load("assets/demo.tmx");

    MapLayer layerZero(map, 0);
    MapLayer layerOne(map, 1);
    MapLayer layerTwo(map, 2);

    sf::Clock globalClock;
    sf::Clock wiggleClock;

    bool doWiggle = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            else if( event.type == sf::Event::KeyPressed )
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::W:
                        // toggle doWiggle
                        doWiggle = !doWiggle;
                    break;
                }
            }
        }


        sf::Time duration = globalClock.restart();
        layerZero.update(duration);

        sf::Vector2f newOffset = sf::Vector2f(0.f, 0.f);
        if (doWiggle)
        {
             newOffset = sf::Vector2f(std::cos(wiggleClock.getElapsedTime().asSeconds()) * 100.f, 0.f);
        }
        layerZero.setOffset(newOffset);
        layerOne.setOffset(newOffset);
        layerTwo.setOffset(newOffset);

        window.clear(sf::Color::Black);
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.display();
    }

    return 0;
}
