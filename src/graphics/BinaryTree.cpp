#include "graphics/BinaryTree.hpp"
#include "graphics/font.hpp"
#include "tree/operations.hpp"


namespace gfx {

///////////////////////////////////////////////////////////////
// Binary Tree Grapchic Node
///////////////////////////////////////////////////////////////
namespace detail
{
TreeNode::TreeNode(const sf::String& value) noexcept
    : mText     {value, gfx::getFont()}
{
    this->init();
}


TreeNode::TreeNode(sf::String&& value) noexcept
    : mText     {std::move(value), gfx::getFont()}
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


///////////////////////////////////////////////////////////////
// BST display class
///////////////////////////////////////////////////////////////
void BinaryTree::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
    states.transform *= this->getTransform();
    target.draw(mRootNode, states);

    if (mLeftNode.get()) {
        target.draw(*mLeftNode, states);
    }

    if (mRightNode.get()) {
        target.draw(*mRightNode, states);
    }
    target.draw(mLeftLine, states);
    target.draw(mRightLine, states);
}


void BinaryTree::makeLeftLine(sf::Vector2f root, sf::Vector2f child)
{
    mLeftLine[0].position = root;
    mLeftLine[1].position = child;
    mLeftLine[0].color = sf::Color::Black;
    mLeftLine[1].color = sf::Color::Black;
}


void BinaryTree::makeRightLine(sf::Vector2f root, sf::Vector2f child)
{
    mRightLine[0].position = root;
    mRightLine[1].position = child;
    mRightLine[0].color = sf::Color::Black;
    mRightLine[1].color = sf::Color::Black;
}

} // namespace gfx end
