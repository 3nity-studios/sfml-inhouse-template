
#pragma once

#include <map>
#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Engine
{
class AssetManager
{

  private:
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;

  public:
    AssetManager()
    {
    }
    ~AssetManager()
    {
    }

    void LoadTexture(std::string name, std::string fileName);
    sf::Texture &GetTexture(std::string name);

    void LoadFont(std::string name, std::string fileName);
    sf::Font &GetFont(std::string name);

    // expand for sounds and other needs
};
} // namespace Engine