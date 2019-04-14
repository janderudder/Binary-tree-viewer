///////////////////////////////////////////////////////////////
//  Binary Tree class, simple implementation.
///////////////////////////////////////////////////////////////
#pragma once
#include <algorithm>
#include <memory>

///////////////////////////////////////////////////////////////
// Forward declaration
///////////////////////////////////////////////////////////////
template <typename ValueType, class Compare = std::less<ValueType>>
class BinaryTree;


namespace detail
{
///////////////////////////////////////////////////////////////
// Helper managing a node of a binary tree
///////////////////////////////////////////////////////////////
template <typename ValueType, class Compare>
struct BinTreeNode
{
    std::unique_ptr<BinaryTree<ValueType, Compare>> tree {nullptr};

    bool isTree() const {
        return tree.get();
    }

    void createTree(ValueType&& value, Compare compare) {
        tree = std::make_unique<BinaryTree<ValueType, Compare>>(
            std::forward<ValueType>(value),
            std::move(compare)
        );
    }

    void insert(ValueType&& value) {
        tree->insert(std::forward<ValueType>(value));
    }

};

} // namespace detail end


///////////////////////////////////////////////////////////////
// The binary tree class
///////////////////////////////////////////////////////////////
template <typename ValueType, class Compare>
class BinaryTree
{
    ValueType                               mValue          {};
    detail::BinTreeNode<ValueType, Compare> mLeftNode       {};
    detail::BinTreeNode<ValueType, Compare> mRightNode      {};
    Compare                                 mCompare        {Compare()};
    std::size_t                             mChildCount     {0};

public:
    constexpr BinaryTree(ValueType value, Compare compare =Compare()) noexcept
        : mValue    {value}
        , mCompare  {compare}
    {}

    void insert(ValueType&& value)
    {
        ++mChildCount;
        if (mCompare(value, mValue))
        {
            if (mLeftNode.isTree())
                mLeftNode.insert(std::forward<ValueType>(value));
            else
                mLeftNode.createTree(std::forward<ValueType>(value), mCompare);
        }else
        {
            if (mRightNode.isTree())
                mRightNode.insert(std::forward<ValueType>(value));
            else
                mRightNode.createTree(std::forward<ValueType>(value), mCompare);
        }
    }

    const ValueType& value() const
    {
        return mValue;
    }

    ValueType& value()
    {
        return mValue;
    }

    bool hasLeftChild() const
    {
        return mLeftNode.isTree();
    }

    bool hasRightChild() const
    {
        return mRightNode.isTree();
    }

    const BinaryTree& leftChild() const
    {
        return *mLeftNode.tree;
    }

    const BinaryTree& rightChild() const
    {
        return *mRightNode.tree;
    }

    auto childCount() const
    {
        return mChildCount;
    }

};
