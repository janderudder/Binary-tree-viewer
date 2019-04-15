#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <string>
#include "tree/BinaryTree.hpp"

namespace gfx
{
///////////////////////////////////////////////////////////////
// Namespace's global font handling functions.
// Used by TreeNode. Set before instanciating any gfx object!
///////////////////////////////////////////////////////////////
void setFont(const sf::Font&);
const sf::Font& getFont();


namespace detail
///////////////////////////////////////////////////////////////
// Helper namespace, class for node graphic representation
///////////////////////////////////////////////////////////////
{
class TreeNode
    : public sf::Drawable, public sf::Transformable
{
    sf::RectangleShape              mRectangle      {};
    sf::Text                        mText;

public:
    static inline const sf::Font*   mFont           {nullptr};  // encapsulation is kind-of slightly broken here.

    TreeNode(const sf::String&) noexcept;
    TreeNode(sf::String&&) noexcept;

    inline sf::FloatRect getLocalBounds() const {
        return mRectangle.getLocalBounds();
    }

    sf::FloatRect getGlobalBounds() const {
        return this->getTransform().transformRect(this->getLocalBounds());
    }

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates =sf::RenderStates::Default) const noexcept override;
    void init();

};

} // namespace detail end

/////////////////////////////////////////////////////////////////////
// gfx::BinaryTree class: graphic reprensentation of a binary tree.
// Construction and drawing are recursive.
/////////////////////////////////////////////////////////////////////
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
    BinaryTree(const ::BinaryTree<T, Comp>& bt) noexcept;

private:
    void makeLeftLine(sf::Vector2f, sf::Vector2f);
    void makeRightLine(sf::Vector2f, sf::Vector2f);

};


} // namespace gfx end

// Include template methods implementation
#include "./BinaryTree.tpl.hpp"
