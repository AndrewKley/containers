#include <gtest/gtest.h>

#include "../containers/s21_set/s21_set.tpp"

TEST(Constructors_set, plain) {
  s21::set<int> s;
  ASSERT_EQ(s.size(), (size_t)0);
  ASSERT_EQ(s.empty(), true);
}

TEST(Constructors_set, init_list) {
  s21::set<int> s{1, 2, 3, 4};
  ASSERT_EQ(s.size(), (size_t)4);
  ASSERT_EQ(s.empty(), false);
}

TEST(Constructors_set, copy_constructor) {
  s21::set<int> s1{1, 2, 3, 4};
  s21::set<int> s2(s1);

  ASSERT_EQ(s1.size(), (size_t)4);
  ASSERT_EQ(s1.empty(), false);

  ASSERT_EQ(s2.size(), (size_t)4);
  ASSERT_EQ(s2.empty(), false);
}

TEST(Constructors_set, move_constructor) {
  s21::set<int> s1{1, 2, 3, 4};
  s21::set<int> s2(std::move(s1));

  ASSERT_EQ(s1.size(), (size_t)0);
  ASSERT_EQ(s1.empty(), true);

  ASSERT_EQ(s1.contains(1), false);
  ASSERT_EQ(s1.contains(2), false);
  ASSERT_EQ(s1.contains(3), false);

  ASSERT_EQ(s2.size(), (size_t)4);
  ASSERT_EQ(s2.empty(), false);
  ASSERT_EQ(s2.contains(1), true);
  ASSERT_EQ(s2.contains(2), true);
  ASSERT_EQ(s2.contains(3), true);
}

TEST(Iterator_set, common) {
  s21::set<int> s{1, 2, 4, 5, 0, 3};

  s21::set<int>::iterator i = s.begin();

  int a = 0;
  while (i != s.end()) {
    EXPECT_EQ(i->first, a);
    ++a;
    i++;
  }
  s21::set<int>::iterator ic = s.cbegin();
  a = 0;
  while (ic != s.cend()) {
    EXPECT_EQ(ic->first, a);
    ++a;
    ic++;
  }
}

TEST(Constructors_set, eq_constructor) {
  s21::set<int> s1{1, 2, 3, 4};
  s21::set<int> s2 = s1;

  ASSERT_EQ(s1.size(), (size_t)4);
  ASSERT_EQ(s1.empty(), false);
  ASSERT_EQ(s1.contains(1), true);
  ASSERT_EQ(s1.contains(2), true);
  ASSERT_EQ(s1.contains(3), true);

  ASSERT_EQ(s2.size(), (size_t)4);
  ASSERT_EQ(s2.empty(), false);
  ASSERT_EQ(s2.contains(1), true);
  ASSERT_EQ(s2.contains(2), true);
  ASSERT_EQ(s2.contains(3), true);
}

TEST(Modifiers_set, insert) {
  s21::set<int> s1;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(1);

  ASSERT_EQ(s1.size(), (size_t)3);

  ASSERT_EQ(s1.contains(1), true);
  ASSERT_EQ(s1.contains(2), true);
  ASSERT_EQ(s1.contains(3), true);
}

TEST(Modifiers_set, clear) {
  s21::set<int> s1;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(4);

  s1.clear();

  ASSERT_EQ(s1.size(), (size_t)0);

  ASSERT_EQ(s1.contains(1), false);
  ASSERT_EQ(s1.contains(2), false);
  ASSERT_EQ(s1.contains(3), false);
}

TEST(Modifiers_set, swap) {
  s21::set<int> s1;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(4);

  s21::set<int> s2{11, 22, 33, 44, 55};

  s1.swap(s2);

  ASSERT_EQ(s1.size(), (size_t)5);
  ASSERT_EQ(s1.contains(1), false);
  ASSERT_EQ(s1.contains(2), false);
  ASSERT_EQ(s1.contains(3), false);
  ASSERT_EQ(s1.contains(11), true);
  ASSERT_EQ(s1.contains(22), true);
  ASSERT_EQ(s1.contains(33), true);

  ASSERT_EQ(s2.size(), (size_t)4);
  ASSERT_EQ(s2.contains(1), true);
  ASSERT_EQ(s2.contains(2), true);
  ASSERT_EQ(s2.contains(3), true);
}

TEST(Modifiers_set, merge) {
  s21::set<int> s1;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(4);

  s21::set<int> s2{11, 22, 3, 4, 55};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), (size_t)7);
  ASSERT_EQ(s1.contains(1), true);
  ASSERT_EQ(s1.contains(2), true);
  ASSERT_EQ(s1.contains(3), true);
  ASSERT_EQ(s1.contains(11), true);
  ASSERT_EQ(s1.contains(22), true);
  ASSERT_EQ(s1.contains(55), true);

  ASSERT_EQ(s2.size(), (size_t)2);
  ASSERT_EQ(s1.contains(3), true);
  ASSERT_EQ(s1.contains(4), true);
}

TEST(Modifiers_set, erase) {
  s21::set<int> s{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

  s.erase(s.find(9));
  ASSERT_EQ(s.contains(9), false);
  s.erase(s.find(8));
  ASSERT_EQ(s.contains(8), false);
  s.erase(s.find(7));
  ASSERT_EQ(s.contains(7), false);
  s.erase(s.find(12));
  ASSERT_EQ(s.contains(12), false);
}