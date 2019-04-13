#include "graphics/GfxBinTree.hpp"
#include "tree/operations.hpp"

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
        textBounds.width + padding.x * 2,
        textBounds.height + padding.y * 2
    });

    mText.setPosition(padding.x, 0);

    mRectangle.setOutlineThickness(borderWidth);
    mRectangle.setOutlineColor(borderColor);
    mRectangle.setFillColor(backgroundColor);
}


} // namespace gfxTrees end


///////////////////////////////////////////////////////////////
// BST display class
///////////////////////////////////////////////////////////////
void GfxBinaryTree::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
    states.transform *= this->getTransform();
    target.draw(mRootNode, states);

    if (mLeftNode.get())
        target.draw(*mLeftNode, states);

    if (mRightNode.get())
        target.draw(*mRightNode, states);
}
