#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <string>
#include "tree/BinaryTree.hpp"

namespace gfx
{
///////////////////////////////////////////////////////////////
// Helper namespace, class for node graphic representation
///////////////////////////////////////////////////////////////
namespace detail
{
class TreeNode
    : public sf::Drawable
    , public sf::Transformable
{
    sf::RectangleShape              mRectangle      {};
    sf::Text                        mText;

    virtual void draw(sf::RenderTarget&, sf::RenderStates =sf::RenderStates::Default) const noexcept override;

public:
    TreeNode(const sf::String&) noexcept;
    TreeNode(sf::String&&) noexcept;

    inline sf::FloatRect getLocalBounds() const {
        return mRectangle.getLocalBounds();
    }

    sf::FloatRect getGlobalBounds() const {
        return this->getTransform().transformRect(this->getLocalBounds());
    }

private:
    void init();

};

} // namespace detail end

///////////////////////////////////////////////////////////////
// The main class: graphic reprensentaiton of a binary tree.
// Construction and drawing are recursive.
///////////////////////////////////////////////////////////////
// template <class ToStringConversion = std::to_string()>
class BinaryTree
    : public sf::Drawable
    , public sf::Transformable
{
    detail::TreeNode                mRootNode;
    std::unique_ptr<BinaryTree>     mLeftNode       {nullptr};
    std::unique_ptr<BinaryTree>     mRightNode      {nullptr};
    sf::VertexArray                 mLeftLine       {sf::PrimitiveType::Lines, 2};
    sf::VertexArray                 mRightLine      {sf::PrimitiveType::Lines, 2};

    virtual void draw(sf::RenderTarget&, sf::RenderStates =sf::RenderStates::Default) const noexcept override;

    template <typename T, class Comp>
    BinaryTree(const ::BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition, std::size_t depthLevel) noexcept;

public:
    template <typename T, class Comp>
    BinaryTree(const ::BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition ={}) noexcept;

private:
    void makeLeftLine(sf::Vector2f, sf::Vector2f);
    void makeRightLine(sf::Vector2f, sf::Vector2f);

};

///////////////////////////////////////////////////////////////
// Template methods implementation
///////////////////////////////////////////////////////////////
template <typename T, class Comp>
BinaryTree::BinaryTree(const ::BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition) noexcept
    : mRootNode {std::to_string(bt.value())}
{
    mRootNode.setPosition(rootPosition);

    const sf::Vector2f leftChildPosition = {rootPosition.x - 312, rootPosition.y + 256};
    const sf::Vector2f rightChildPosition = {rootPosition.x + 312, rootPosition.y + 256};

    if (bt.hasLeftChild()) {
        // Cannot use std::make_unique on private constructor
        mLeftNode.reset(new BinaryTree{bt.leftChild(), leftChildPosition, 1});
        this->makeLeftLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   leftChildPosition.x + mLeftNode->mRootNode.getGlobalBounds().width / 2,
            leftChildPosition.y
        });
    }

    if (bt.hasRightChild()) {
        mRightNode.reset(new BinaryTree{bt.rightChild(), rightChildPosition, 1});
        this->makeRightLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   rightChildPosition.x + mRightNode->mRootNode.getGlobalBounds().width / 2,
            rightChildPosition.y
        });
    }

}

template <typename T, class Comp>
BinaryTree::BinaryTree(const ::BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition, std::size_t depth) noexcept
    : mRootNode {std::to_string(bt.value())}
{
    mRootNode.setPosition(rootPosition);

    const sf::Vector2f leftChildPosition = {rootPosition.x - 256 + (256 / 4 * depth), rootPosition.y + 256};
    const sf::Vector2f rightChildPosition = {rootPosition.x + 256 + (256 / 4 * depth), rootPosition.y + 256};

    if (bt.hasLeftChild()) {
        mLeftNode.reset(new BinaryTree{bt.leftChild(), leftChildPosition, depth + 1});
        this->makeLeftLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   leftChildPosition.x + mLeftNode->mRootNode.getGlobalBounds().width / 2,
            leftChildPosition.y
        });
    }

    if (bt.hasRightChild()) {
        mRightNode.reset(new BinaryTree{bt.rightChild(), rightChildPosition, depth + 1});
        this->makeRightLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   rightChildPosition.x + mRightNode->mRootNode.getGlobalBounds().width / 2,
            rightChildPosition.y
        });
    }

}


} // namespace gfx end
