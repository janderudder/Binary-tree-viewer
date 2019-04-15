#include "graphics/BinaryTree.hpp"
#include "tree/operations.hpp"

namespace gfx
{
///////////////////////////////////////////////////////////////
// Namespace's global font handling functions.
// Set before instanciating any gfx object!
///////////////////////////////////////////////////////////////
const sf::Font& getFont()
{
    return *gfx::detail::TreeNode::mFont;
}


void setFont(const sf::Font& font)
{
    gfx::detail::TreeNode::mFont = &font;
}


///////////////////////////////////////////////////////////////
// Binary Tree Grapchic Node
///////////////////////////////////////////////////////////////
namespace detail
{
TreeNode::TreeNode(const sf::String& value) noexcept
    : mText     {value, *mFont}
{
    this->init();
}


TreeNode::TreeNode(sf::String&& value) noexcept
    : mText     {std::move(value), *mFont}
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
    // Graphic settings (could be exported)
    static const unsigned charSize = 28;
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

} // namespace detail end
} // namespace gfx end
