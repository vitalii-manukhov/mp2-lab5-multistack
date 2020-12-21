#include "multistack.h"
#include "../gtest/gtest.h"

TEST(TMultiStack, can_create_multistack_with_positive_length)
{
  ASSERT_NO_THROW(TMultiStack<int> ms(5, 5));
}

TEST(TMultiStack, can_create_multistack_with_different_types)
{
  ASSERT_NO_THROW(TMultiStack<int> ms1(5));
  ASSERT_NO_THROW(TMultiStack<char> ms2(5));
}

TEST(TMultiStack, cannot_create_multistack_with_negative_size)
{
  ASSERT_ANY_THROW(TMultiStack<int> stack(-5));
}

TEST(TMultiStack, can_create_copy_of_multistack)
{
  TMultiStack<int> ms1(5, 5);

  ASSERT_NO_THROW(TMultiStack<int> ms2(ms1));
}

TEST(TMultiStack, can_put_elem)
{
  TMultiStack<int> ms(5, 5);

  ASSERT_NO_THROW(ms.Put(5, 3));
}

TEST(TMultiStack, can_get_elem)
{
  TMultiStack<int> ms(5, 5);

  ms.Put(5, 3);

  EXPECT_EQ(5, ms.Get(3));
}

TEST(TMultiStack, can_assign_multistack)
{
  TMultiStack<int> ms1(5, 5);
  ms1.Put(10, 3);
  TMultiStack<int> ms2(5, 5);

  ASSERT_NO_THROW(ms2 = ms1);
  EXPECT_EQ(10, ms2.Get(3));
}

TEST(TMultiStack, can_control_empty_of_multistack)
{
  TMultiStack<int> ms(5, 5);

  ASSERT_NO_THROW(ms.IsEmpty(1));
  EXPECT_EQ(1, ms.IsEmpty(1));
}

TEST(TMultiStack, can_control_full_of_multistack)
{
  int size_1 = 10;
  int size_2 = 5;
  TMultiStack<int> ms1(5, 1);
  TMultiStack<int> ms2(size_1 * 3, 3);
  TMultiStack<int> ms3(size_2 * 5, 5);

  for (int i = 0; i < ms1.GetSize(); i++)
    ms1.Put(i, 0);

  for (int i = 0; i < size_1; i++)
    ms2.Put(i, 0);

  for (int i = 0; i < ms3.GetSize(); i++)
    ms3.Put(i, (i % 5));

  ASSERT_NO_THROW(ms1.IsFull(0));
  EXPECT_EQ(1, ms1.IsFull(0));
  ASSERT_NO_THROW(ms2.IsFull(0));
  EXPECT_EQ(1, ms2.IsFull(0));
  ASSERT_NO_THROW(ms3.IsFull(0));
  EXPECT_EQ(1, ms3.IsFull(0));
  ASSERT_NO_THROW(ms3.IsFull(1));
  EXPECT_EQ(1, ms3.IsFull(1));
  ASSERT_NO_THROW(ms3.IsFull(2));
  EXPECT_EQ(1, ms3.IsFull(2));
  ASSERT_NO_THROW(ms3.IsFull(3));
  EXPECT_EQ(1, ms3.IsFull(3));
  ASSERT_NO_THROW(ms3.IsFull(4));
  EXPECT_EQ(1, ms3.IsFull(4));
}

TEST(TMultiStack, can_get_size)
{
  TMultiStack<int> ms(10, 5);

  ASSERT_NO_THROW(ms.GetSize());
  EXPECT_EQ(10, ms.GetSize());
}

TEST(TMultiStack, can_resize_multistack)
{
  TMultiStack<int> ms(6, 3);
  
  ASSERT_NO_THROW(ms.Resize(1, 0));
}
