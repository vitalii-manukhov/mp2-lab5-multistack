#include "stack.h"

#include "../gtest/gtest.h"

TEST(TStack, can_create_stack_with_positive_size)
{
  ASSERT_NO_THROW(TStack<int> stack(5));
}

TEST(TStack, can_create_stack_with_different_types)
{
  ASSERT_NO_THROW(TStack<int> stack_0(5));
  ASSERT_NO_THROW(TStack<char> stack_1(5));
}

TEST(TStack, cannot_create_stack_with_negative_size)
{
  ASSERT_ANY_THROW(TStack<int> stack(-5));
}

TEST(TStack, can_create_copy_of_stack)
{
  TStack<char> stack_0(5);
  for (int i = 0; i < stack_0.GetSize(); i++)
    stack_0.Put((char)i);

  ASSERT_NO_THROW(TStack<char> stack_1(stack_0));
}

TEST(TStack, top_of_copy_of_stack_equal_to_top_of_original_stack)
{
  TStack<char> stack_0(5);
  for (int i = 0; i < stack_0.GetSize(); i++)
    stack_0.Put('a' + 1);
  TStack<char> stack_1(stack_0);

  EXPECT_EQ(stack_0.Get(), stack_1.Get());
}

TEST(TStack, can_put_elem)
{
  TStack<int> stack(5);

  ASSERT_NO_THROW(stack.Put(-1));
}

TEST(TStack, can_get_elem)
{
  TStack<int> stack(5);
  stack.Put(-1);

  EXPECT_EQ(-1, stack.Get());
}

TEST(TStack, can_assign_stack)
{
  TStack<int> stack_0(5);
  TStack<int> stack_1(5);
  for (int i = 0; i < stack_0.GetSize(); i++)
    stack_0.Put((int)i);

  ASSERT_NO_THROW(stack_1 = stack_0);
}

TEST(TStack, top_of_result_of_assignemt_equal_to_top_of_original_stack)
{
  TStack<int> stack_0(5);
  TStack<int> stack_1(5);
  for (int i = 0; i < stack_0.GetSize(); i++)
    stack_0.Put(i);
  stack_1 = stack_0;

  EXPECT_EQ(stack_0.Get(), stack_1.Get());
}

TEST(TStack, can_control_empty_of_stack)
{
  TStack<int> stack(5);

  ASSERT_NO_THROW(stack.IsEmpty());
  EXPECT_EQ(1, stack.IsEmpty());
}

TEST(TStack, can_control_full_of_stack)
{
  TStack<int> stack(5);

  for (int i = 0; i < stack.GetSize(); i++)
    stack.Put(i);

  ASSERT_NO_THROW(stack.IsFull());
  EXPECT_EQ(1, stack.IsFull());
}

TEST(TStack, stack_overflow_throws_error)
{
  TStack<int> stack(3);
  stack.Put(0);
  stack.Put(1);
  stack.Put(2);

  EXPECT_EQ(1, stack.IsFull());
  ASSERT_ANY_THROW(stack.Put(3));
}

TEST(TStack, can_write_element_after_get_top_of_stack_before_stack_overflow)
{
  TStack<int> stack(3);
  stack.Put(0);
  stack.Put(1);
  stack.Put(2);

  EXPECT_EQ(1, stack.IsFull());

  stack.Get();

  ASSERT_NO_THROW(stack.Put(3));
}


