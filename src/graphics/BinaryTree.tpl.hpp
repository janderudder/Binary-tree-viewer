#include "./BinaryTree.hpp" // include header to help IDE figure out its things
namespace gfx
{
///////////////////////////////////////////////////////////////
// Binary Tree graphic, template implementation.
///////////////////////////////////////////////////////////////
template <typename T, class Comp>
BinaryTree::BinaryTree(const ::BinaryTree<T, Comp>& bt) noexcept
    : mRootNode     {std::to_string(bt.value())}
{
    const sf::Vector2f leftChildPosition = { -312, 256 };
    const sf::Vector2f rightChildPosition = { +312, 256};

    if (bt.hasLeftChild()) {
        // Cannot use std::make_unique on private constructor
        mLeftNode.reset(new BinaryTree{bt.leftChild(), leftChildPosition, 1});
        this->makeLeftLine(
        {   mRootNode.getGlobalBounds().width / 2.f, 0.f
        },
        {   leftChildPosition.x + mLeftNode->mRootNode.getGlobalBounds().width / 2,
            leftChildPosition.y
        });
    }

    if (bt.hasRightChild()) {
        mRightNode.reset(new BinaryTree{bt.rightChild(), rightChildPosition, 1});
        this->makeRightLine(
        {   mRootNode.getGlobalBounds().width / 2.f, 0.f
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


inline void BinaryTree::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
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


inline void BinaryTree::makeLeftLine(sf::Vector2f root, sf::Vector2f child)
{
    mLeftLine[0].position = root;
    mLeftLine[1].position = child;
    mLeftLine[0].color = sf::Color::Black;
    mLeftLine[1].color = sf::Color::Black;
}


inline void BinaryTree::makeRightLine(sf::Vector2f root, sf::Vector2f child)
{
    mRightLine[0].position = root;
    mRightLine[1].position = child;
    mRightLine[0].color = sf::Color::Black;
    mRightLine[1].color = sf::Color::Black;
}


} // namespace gfx end
