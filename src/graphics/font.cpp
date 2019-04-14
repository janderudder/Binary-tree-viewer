#include "graphics/font.hpp"

namespace gfx
{

namespace
{
    const sf::Font* font = nullptr;
}


const sf::Font& getFont()
{
    return *font;
}


void setFont(const sf::Font& fnt)
{
    font = &fnt;
}


} // namespace gfx end
