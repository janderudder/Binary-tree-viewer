#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>

namespace sfx {

sf::String wideToString(std::wstring_view wsv)
{
    #ifdef _WIN32
        return sf::String::fromUtf16(wsv.begin(), wsv.end());

    #else //! TODO: needs testing on Linux and Mac platforms
        return sf::String::fromUtf8(wsv.begin(), wsv.end());

    #endif
}

} // namespace sfx
