#include <stddef.h>
#include <list>
#include <gtest/gtest.h>

#include "phylopp/ListIterator.h"

using namespace Domain;
using ::testing::Test;

class DummyClass
{
public:
    DummyClass(int n): num(n) {}

    int getNum() const
    {
        return num;
    }
private:
    int num;
};

// Check the getters work properly
TEST(ListIteratorTest, IterationTest)
{
    DummyClass* dummy1 = new DummyClass(1);
    DummyClass* dummy2 = new DummyClass(2);
    DummyClass* dummy3 = new DummyClass(3);
    DummyClass* dummy4 = new DummyClass(4);
    DummyClass* dummy5 = new DummyClass(5);

    std::list<DummyClass*> list;
    list.push_back(dummy1);
    list.push_back(dummy2);
    list.push_back(dummy3);
    list.push_back(dummy4);
    list.push_back(dummy5);

    ListIterator<DummyClass> it(list);

    EXPECT_EQ(it.count(), 5);

    int i = 1;
    while (!it.end())
    {
        DummyClass* c = it.get();
        EXPECT_EQ(i, c->getNum());
        i++;
        it.next();
    }

    delete dummy1;
    delete dummy2;
    delete dummy3;
    delete dummy4;
    delete dummy5;
}
