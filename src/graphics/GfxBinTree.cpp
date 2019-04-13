#include "graphics/GfxBinTree.hpp"


namespace gfxTrees {
///////////////////////////////////////////////////////////////
// Global font
///////////////////////////////////////////////////////////////

static const sf::Font* font = nullptr;


void setFont(const sf::Font& font) {
    gfxTrees::font = &font;
}


///////////////////////////////////////////////////////////////
// Binary Tree Grapchic Node
///////////////////////////////////////////////////////////////
TreeNode::TreeNode(const sf::String& value) noexcept
    : mText     {value, *gfxTrees::font, 42}
{
    this->init();
}



TreeNode::TreeNode(sf::String&& value) noexcept
    : mText     {std::move(value), *gfxTrees::font, 42}
{
    this->init();
}



void TreeNode::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
    states.transform *= this->getTransform();
    target.draw(mRectangle, states);
    target.draw(mText, states);
}



void TreeNode::init()
{
    // Graphic settings
    static const sf::Vector2f padding = {24, 18};
    static const float borderWidth = 4;
    static const auto backgroundColor = sf::Color::Blue;
    static const auto borderColor = sf::Color::Black;

    // Set-up
    const auto textBounds = mText.getLocalBounds();

    mRectangle.setSize({
        textBounds.width + padding.x,
        textBounds.height + padding.y
    });

    mText.setPosition(padding);

    mRectangle.setOutlineThickness(borderWidth);
    mRectangle.setOutlineColor(borderColor);
    mRectangle.setFillColor(backgroundColor);

}


} // namespace gfxTrees end
