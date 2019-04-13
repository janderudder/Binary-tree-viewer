#pragma once
#include <SFML/System.hpp>

namespace sfx {

struct Time final : public sf::Time
{
    inline void reset() {
        static_cast<sf::Time&>(*this) = sf::Time::Zero;
    }
};

}
