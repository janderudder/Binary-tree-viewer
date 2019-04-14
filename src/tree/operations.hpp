#pragma once
#include <vector>
#include "tree/BinaryTree.hpp"

/**
 * Breath traversal of a binary tree,
 * returning an array of pointer to tree nodes,
 * in traversal order (top left to bottom right).
 */
template <template <class ValT, class CompT> class = BinaryTree, class ValT, class CompT =std::less<ValT>>
std::vector<const BinaryTree<ValT, CompT>*> breadthFirstTraversal(const BinaryTree<ValT, CompT>& bt)
{
    std::vector<const BinaryTree<ValT, CompT>*> nodesPointers;
    const auto nodeCount = bt.childCount() + 1;
    nodesPointers.reserve(nodeCount);
    nodesPointers.push_back(&bt);

    for (auto i=0ULL; i < nodeCount; ++i) {
        if (nodesPointers[i]->hasLeftChild())
            nodesPointers.push_back(&nodesPointers[i]->leftChild());
        if (nodesPointers[i]->hasRightChild())
            nodesPointers.push_back(&nodesPointers[i]->rightChild());
    }

    return nodesPointers;
}
