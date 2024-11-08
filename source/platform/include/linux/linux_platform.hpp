#ifndef UTIL_LINUX_PLATFORM_HPP
#define UTIL_LINUX_PLATFORM_HPP

#include "platform/include/iplatform.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowHandle.hpp>

namespace util
{
struct LinuxPlatform : IPlatform
{
    LinuxPlatform();

    void setIcon(const sf::WindowHandle &inHandle) final;
    void toggleFullscreen(const sf::WindowHandle &inHandle, const sf::Uint32 inStyle, const bool inWindowed,
                          const sf::Vector2u &inResolution) final;
    float getScreenScalingFactor(const sf::WindowHandle &inHandle) final;
    int getRefreshRate(const sf::WindowHandle &inHandle) final;
};
} // namespace util

#endif // UTIL_LINUX_PLATFORM_HPP
