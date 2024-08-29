#pragma once

#include "config/include/game.hpp"
#include "config/include/global.hpp"
#include "gui/include/state.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class MainMenuState : public Engine::State
{
  public:
    MainMenuState(GameDataRef data);
    //~MainMenuState() = default;

    void initState();
    void updateInputs();
    void updateState(float dt __attribute__((unused)));
    void drawState(float dt __attribute__((unused)));

  private:
    GameDataRef _data;
};
