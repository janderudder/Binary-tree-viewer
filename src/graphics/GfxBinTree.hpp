#pragma once
#include <SFML/Graphics.hpp>
#include <array>
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
