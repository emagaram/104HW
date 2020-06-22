#include "gtest/gtest.h"
#include "stack.h"
namespace myStack
{
    TEST(Stack, push)
    {
        Stack<int> *stack = new Stack<int>();
        stack->push(0);
        stack->push(1);
        stack->push(2);
        EXPECT_EQ(stack->size(), size_t(3));
        delete stack;
    }

    TEST(Stack, pop)
    {
        Stack<int> *stack = new Stack<int>();
        stack->push(0);
        stack->push(1);
        stack->push(2);
        stack->pop();
        stack->pop();
        stack->pop();

        EXPECT_THROW(stack->pop(), std::underflow_error);
        EXPECT_EQ(stack->size(), size_t(0));
        delete stack;
    }

    TEST(Stack, top)
    {
        Stack<int> *stack = new Stack<int>();
        stack->push(867);
        EXPECT_EQ(stack->top(), 867);
        stack->push(82);
        EXPECT_EQ(stack->top(), 82);
        delete stack;
    }
} // namespace myStack