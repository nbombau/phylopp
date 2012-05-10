#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "phylopp/ITree.h"
#include "MockNode.h"

using namespace Domain;
using ::testing::Test;

typedef MockNode<Domain::Node> TestNode;

//Single node, should be root and leaf
TEST(ITreeTest, TreeCreationTest)
{
    ITree<TestNode> t;
    TestNode* n = t.getRoot();

    ASSERT_FALSE(n == NULL);
}
