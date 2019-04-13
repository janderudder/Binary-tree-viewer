#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <string>
#include "tree/BinaryTree.hpp"

namespace gfxTrees
{
    void setFont(const sf::Font&);

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
} // namespace GfxTrees end


template <typename ValueT>
class GfxMinimalBinTree
    : public sf::Drawable
    , public sf::Transformable
{
    struct NodeWrapper {
        gfxTrees::TreeNode node;
        enum State { Set, Unset } state;
        NodeWrapper(std::string&& val, State st) noexcept : node{val}, state{st} {}
    };


    std::array<NodeWrapper, 3>  mWrappedNodes;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states =sf::RenderStates::Default) const noexcept override
    {
        states.transform *= this->getTransform();
        for (const auto& wrapper : std::as_const(mWrappedNodes)) {
            if (wrapper.state == NodeWrapper::Set)
                target.draw(wrapper.node, states);
        }
    }

public:
    GfxMinimalBinTree(ValueT&& parent, ValueT&& left, ValueT&& right) noexcept
        : mWrappedNodes {
            NodeWrapper{std::to_string(parent), NodeWrapper::Set},
            NodeWrapper{std::to_string(left), NodeWrapper::Set},
            NodeWrapper{std::to_string(right), NodeWrapper::Set}
        }
    {}

};




class GfxBinaryTree
    : public sf::Drawable
    , public sf::Transformable
{
    using TreeNode = ::gfxTrees::TreeNode;

    TreeNode                        mRootNode;
    std::unique_ptr<GfxBinaryTree>  mLeftNode       {nullptr};
    std::unique_ptr<GfxBinaryTree>  mRightNode      {nullptr};
    sf::VertexArray                 mLeftLine       {sf::PrimitiveType::Lines, 2};
    sf::VertexArray                 mRightLine      {sf::PrimitiveType::Lines, 2};

    virtual void draw(sf::RenderTarget&, sf::RenderStates =sf::RenderStates::Default) const noexcept override;

public:
    template <typename T, class Comp>
    GfxBinaryTree(const BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition, std::size_t depthLevel) noexcept;

    template <typename T, class Comp>
    GfxBinaryTree(const BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition ={}) noexcept;

private:
    void makeLeftLine(sf::Vector2f, sf::Vector2f);
    void makeRightLine(sf::Vector2f, sf::Vector2f);

};




///////////////////////////////////////////////////////////////
// Template methods implementation
///////////////////////////////////////////////////////////////
template <typename T, class Comp>
GfxBinaryTree::GfxBinaryTree(const BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition) noexcept
    : mRootNode {std::to_string(bt.value())}
{
    mRootNode.setPosition(rootPosition);

    const sf::Vector2f leftChildPosition = {rootPosition.x - 512, rootPosition.y + 256};
    const sf::Vector2f rightChildPosition = {rootPosition.x + 512, rootPosition.y + 256};

    if (bt.hasLeftChild()) {
        mLeftNode = std::make_unique<GfxBinaryTree>(bt.leftChild(), leftChildPosition, 1);
        this->makeLeftLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   leftChildPosition.x + mLeftNode->mRootNode.getGlobalBounds().width / 2,
            leftChildPosition.y
        });
    }

    if (bt.hasRightChild()) {
        mRightNode = std::make_unique<GfxBinaryTree>(bt.rightChild(), rightChildPosition, 1);
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
GfxBinaryTree::GfxBinaryTree(const BinaryTree<T, Comp>& bt, const sf::Vector2f& rootPosition, std::size_t depth) noexcept
    : mRootNode {std::to_string(bt.value())}
{
    mRootNode.setPosition(rootPosition);

    const sf::Vector2f leftChildPosition = {rootPosition.x - 256 + (256 / 4 * depth), rootPosition.y + 256};
    const sf::Vector2f rightChildPosition = {rootPosition.x + 256 + (256 / 4 * depth), rootPosition.y + 256};

    if (bt.hasLeftChild()) {
        mLeftNode = std::make_unique<GfxBinaryTree>(bt.leftChild(), leftChildPosition, depth + 1);
        this->makeLeftLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   leftChildPosition.x + mLeftNode->mRootNode.getGlobalBounds().width / 2,
            leftChildPosition.y
        });
    }

    if (bt.hasRightChild()) {
        mRightNode = std::make_unique<GfxBinaryTree>(bt.rightChild(), rightChildPosition, depth + 1);
        this->makeRightLine(
        {   rootPosition.x + mRootNode.getGlobalBounds().width / 2.f,
            rootPosition.y
        },
        {   rightChildPosition.x + mRightNode->mRootNode.getGlobalBounds().width / 2,
            rightChildPosition.y
        });
    }

}
