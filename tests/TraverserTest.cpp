#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "phylopp/Domain/INode.h"
#include "phylopp/Domain/ITreeCollection.h"
#include "phylopp/Domain/ITree.h"
#include "phylopp/Traversal/Traverser.h"
#include "phylopp/Traversal/NodeVisitor.h"
#include "MockNode.h"

using namespace Domain;
using namespace Traversal;
using ::testing::Test;

class TagAction
{
public:
    VisitAction visitNode(TestNode* n)
    {
        n->visited = true;
        return ContinueTraversing;
    }
};

struct AlwaysTruePredicate
{
    bool operator()(TestNode* /*node*/) const
    {
        return true;
    }
};

/**
*  Traverse Down Tests
*/

//traverse  Down a tree that has only the root
TEST(TraverserTest, TreaverseOnlyRootTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(&t, a);

    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
}

//traverse Down a tree passing the tree itself
TEST(TraverserTest, TraverseTreeDownTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    //build a three levels tree
    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c1->addChild<TestNode>();
    TestNode* c2c2 = c1->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(&t, a);

    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
    ASSERT_TRUE(c1->visited);
    ASSERT_TRUE(c2->visited);
    ASSERT_TRUE(c3->visited);
    ASSERT_TRUE(c4->visited);
    ASSERT_TRUE(c5->visited);

    ASSERT_TRUE(c1c1->visited);
    ASSERT_TRUE(c1c2->visited);
    ASSERT_TRUE(c1c3->visited);
    ASSERT_TRUE(c1c4->visited);

    ASSERT_TRUE(c2c1->visited);
    ASSERT_TRUE(c2c2->visited);
}

//traverse Down a tree passing the root node.
TEST(TraverserTest, TraverseRootNodeDownTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c1->addChild<TestNode>();
    TestNode* c2c2 = c1->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(n, a);

    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
    ASSERT_TRUE(c1->visited);
    ASSERT_TRUE(c2->visited);
    ASSERT_TRUE(c3->visited);
    ASSERT_TRUE(c4->visited);
    ASSERT_TRUE(c5->visited);

    ASSERT_TRUE(c1c1->visited);
    ASSERT_TRUE(c1c2->visited);
    ASSERT_TRUE(c1c3->visited);
    ASSERT_TRUE(c1c4->visited);

    ASSERT_TRUE(c2c1->visited);
    ASSERT_TRUE(c2c2->visited);
}

//traverse Down a tree passing a non-root and non-leaf node
TEST(TraverserTest, TraverseMiddleNodeDownTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c2->addChild<TestNode>();
    TestNode* c2c2 = c2->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(c2, a);

    ASSERT_FALSE(n->visited);
    ASSERT_FALSE(c1->visited);
    ASSERT_TRUE(c2->visited);
    ASSERT_FALSE(c3->visited);
    ASSERT_FALSE(c4->visited);
    ASSERT_FALSE(c5->visited);

    ASSERT_FALSE(c1c1->visited);
    ASSERT_FALSE(c1c2->visited);
    ASSERT_FALSE(c1c3->visited);
    ASSERT_FALSE(c1c4->visited);

    ASSERT_TRUE(c2c1->visited);
    ASSERT_TRUE(c2c2->visited);
}

//traverse Down a tree passing a leaf node
TEST(TraverserTest, TraverseLeafNodeDownTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c2->addChild<TestNode>();
    TestNode* c2c2 = c2->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(c1c2, a);

    ASSERT_FALSE(n->visited);
    ASSERT_FALSE(c1->visited);
    ASSERT_FALSE(c2->visited);
    ASSERT_FALSE(c3->visited);
    ASSERT_FALSE(c4->visited);
    ASSERT_FALSE(c5->visited);

    ASSERT_FALSE(c1c1->visited);
    ASSERT_TRUE(c1c2->visited);
    ASSERT_FALSE(c1c3->visited);
    ASSERT_FALSE(c1c4->visited);

    ASSERT_FALSE(c2c1->visited);
    ASSERT_FALSE(c2c2->visited);
}

/**
*  Traverse Up Tests
*/

//traverse up a tree passing a leaf node
TEST(TraverserTest, TraverseLeafUpTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c2->addChild<TestNode>();
    TestNode* c2c2 = c2->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseAncestors(c1c2, a);

    ASSERT_TRUE(n->visited);
    ASSERT_TRUE(c1->visited);
    ASSERT_FALSE(c2->visited);
    ASSERT_FALSE(c3->visited);
    ASSERT_FALSE(c4->visited);
    ASSERT_FALSE(c5->visited);

    ASSERT_FALSE(c1c1->visited);
    ASSERT_TRUE(c1c2->visited);
    ASSERT_FALSE(c1c3->visited);
    ASSERT_FALSE(c1c4->visited);

    ASSERT_FALSE(c2c1->visited);
    ASSERT_FALSE(c2c2->visited);
}

//traverse up a tree passing a middle node
TEST(TraverserTest, TraverseMiddleNodeUpTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c2->addChild<TestNode>();
    TestNode* c2c2 = c2->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseAncestors(c1, a);


    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
    ASSERT_TRUE(c1->visited);
    ASSERT_FALSE(c2->visited);
    ASSERT_FALSE(c3->visited);
    ASSERT_FALSE(c4->visited);
    ASSERT_FALSE(c5->visited);

    ASSERT_FALSE(c1c1->visited);
    ASSERT_FALSE(c1c2->visited);
    ASSERT_FALSE(c1c3->visited);
    ASSERT_FALSE(c1c4->visited);

    ASSERT_FALSE(c2c1->visited);
    ASSERT_FALSE(c2c2->visited);
}

//traverse up a tree passing a root node
TEST(TraverserTest, TraverseRootUpTest)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c2->addChild<TestNode>();
    TestNode* c2c2 = c2->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseAncestors(n, a);


    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
    ASSERT_FALSE(c1->visited);
    ASSERT_FALSE(c2->visited);
    ASSERT_FALSE(c3->visited);
    ASSERT_FALSE(c4->visited);
    ASSERT_FALSE(c5->visited);

    ASSERT_FALSE(c1c1->visited);
    ASSERT_FALSE(c1c2->visited);
    ASSERT_FALSE(c1c3->visited);
    ASSERT_FALSE(c1c4->visited);

    ASSERT_FALSE(c2c1->visited);
    ASSERT_FALSE(c2c2->visited);
}

//traverse Down a tree passing the tree itself
TEST(TraverserTest, TraverseTreePostOrder)
{
    ITree<TestNode> itree;
    Domain::ITree<TestNode>& t = itree;
    TestNode* n = t.getRoot();

    //build a three levels tree
    TestNode* c1 = n->addChild<TestNode>();
    TestNode* c2 = n->addChild<TestNode>();
    TestNode* c3 = n->addChild<TestNode>();
    TestNode* c4 = n->addChild<TestNode>();
    TestNode* c5 = n->addChild<TestNode>();

    TestNode* c1c1 = c1->addChild<TestNode>();
    TestNode* c1c2 = c1->addChild<TestNode>();
    TestNode* c1c3 = c1->addChild<TestNode>();
    TestNode* c1c4 = c1->addChild<TestNode>();

    TestNode* c2c1 = c1->addChild<TestNode>();
    TestNode* c2c2 = c1->addChild<TestNode>();

    Traverser<TestNode, TagAction, AlwaysTruePredicate> traverser;
    TagAction a;
    traverser.traverseDescendants(&t, a);

    //all nodes should have been visited
    ASSERT_TRUE(n->visited);
    ASSERT_TRUE(c1->visited);
    ASSERT_TRUE(c2->visited);
    ASSERT_TRUE(c3->visited);
    ASSERT_TRUE(c4->visited);
    ASSERT_TRUE(c5->visited);

    ASSERT_TRUE(c1c1->visited);
    ASSERT_TRUE(c1c2->visited);
    ASSERT_TRUE(c1c3->visited);
    ASSERT_TRUE(c1c4->visited);

    ASSERT_TRUE(c2c1->visited);
    ASSERT_TRUE(c2c2->visited);
}
