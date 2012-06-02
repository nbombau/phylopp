#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "phylopp/Domain/ITreeCollection.h"
#include "MockNode.h"

using namespace Domain;
using ::testing::Test;

//adding trees to collections, and iterating through the collection
TEST(ITreeCollectionTest, AddTreeTest)
{
    ITreeCollection<TestNode> col;
    ITree<TestNode>* t1 = col.addTree();

    //recently added tree shouldn't be null
    ASSERT_FALSE(t1 == NULL);

    ListIterator<ITree<TestNode> > it = col.getIterator();

    ITree<TestNode>* tAux = it.get();

    //if we iterate through the trees of the collection, there it shouldn
    //be only one, and particularly the one added previously
    EXPECT_EQ(t1, tAux);
    EXPECT_EQ(it.count(), 1);

    col.addTree();
    col.addTree();
    col.addTree();
    col.addTree();
    col.addTree();

    ListIterator<ITree<TestNode> > it2 = col.getIterator();

    EXPECT_EQ(it2.count(), 6);
    //TODO: iterate!
}
