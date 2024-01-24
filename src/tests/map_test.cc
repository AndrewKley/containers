#include <gtest/gtest.h>

#include "../containers/s21_map/s21_map.tpp"

TEST(Constructors_map, plain) {
  s21::map<int, int> m;
  ASSERT_EQ(m.size(), (size_t)0);
  ASSERT_EQ(m.empty(), true);
}

TEST(Constructors_map, init_list) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);
  s21::map<int, int> m{p1, p2, p3, p4};
  ASSERT_EQ(m.size(), (size_t)4);
  ASSERT_EQ(m.empty(), false);
  ASSERT_EQ(m[2], 20);
  ASSERT_EQ(m[3], 30);
  ASSERT_EQ(m[4], 40);
}

TEST(Constructors_map, copy_constructor) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4};
  s21::map<int, int> m2(m1);

  ASSERT_EQ(m1.size(), (size_t)4);
  ASSERT_EQ(m1.empty(), false);
  ASSERT_EQ(m1[2], 20);
  ASSERT_EQ(m1[3], 30);
  ASSERT_EQ(m1[4], 40);

  ASSERT_EQ(m2.size(), (size_t)4);
  ASSERT_EQ(m2.empty(), false);
  ASSERT_EQ(m2[2], 20);
  ASSERT_EQ(m2[3], 30);
  ASSERT_EQ(m2[4], 40);
}

TEST(Constructors_map, move_constructor) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4};
  s21::map<int, int> m2(std::move(m1));

  ASSERT_EQ(m1.size(), (size_t)0);
  ASSERT_EQ(m1.empty(), true);

  ASSERT_EQ(m2.size(), (size_t)4);
  ASSERT_EQ(m2.empty(), false);
  ASSERT_EQ(m2[2], 20);
  ASSERT_EQ(m2[3], 30);
  ASSERT_EQ(m2[4], 40);
}

TEST(Constructors_map, operator_eq) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4};
  s21::map<int, int> m2 = m1;

  ASSERT_EQ(m1.size(), (size_t)4);
  ASSERT_EQ(m1.empty(), false);
  ASSERT_EQ(m1[2], 20);
  ASSERT_EQ(m1[3], 30);
  ASSERT_EQ(m1[4], 40);

  ASSERT_EQ(m2.size(), (size_t)4);
  ASSERT_EQ(m2.empty(), false);
  ASSERT_EQ(m2[2], 20);
  ASSERT_EQ(m2[3], 30);
  ASSERT_EQ(m2[4], 40);
}

TEST(Map_access_map, at) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4};

  ASSERT_EQ(m1.at(2), 20);
  ASSERT_EQ(m1[3], 30);
  ASSERT_EQ(m1.at(4), 40);

  EXPECT_ANY_THROW(m1.at(333));
  s21::map<int, int> m;
  EXPECT_ANY_THROW(m.at(3));
  EXPECT_ANY_THROW(m[3]);
}

TEST(Capacity_map, empty_map) {
  pair<int, int> p1(1, 10);

  s21::map<int, int> m1;

  EXPECT_EQ(m1.empty(), true);
  m1.insert(p1);
  EXPECT_EQ(m1.empty(), false);
}

TEST(Capacity_map, size) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1;

  EXPECT_EQ(m1.size(), (size_t)0);
  m1.insert(p1);
  EXPECT_EQ(m1.size(), (size_t)1);
  m1.insert(p2);
  EXPECT_EQ(m1.size(), (size_t)2);
  m1.insert(p3);
  EXPECT_EQ(m1.size(), (size_t)3);
  m1.insert(p4);
  EXPECT_EQ(m1.size(), (size_t)4);
  m1.clear();
  EXPECT_EQ(m1.size(), (size_t)0);
}

TEST(Capacity_map, max_size) {
  s21::map<long, long> m1;
  std::map<long, long> m2;

  size_t max = m1.max_size();
  size_t stdrt = m2.max_size();

  EXPECT_EQ(max, stdrt);
}

TEST(Iterator_map, begin) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);

  s21::map<int, int> m1{p1, p2, p3};

  s21::map<int, int>::iterator i = m1.begin();

  EXPECT_EQ((*i).first, 1);
  EXPECT_EQ(i->second, 10);
  ++i;
  EXPECT_EQ((*i).first, 2);
  EXPECT_EQ(i->second, 20);
  ++i;
  EXPECT_EQ((*i).first, 3);
  EXPECT_EQ(i->second, 30);
  ++i;
}

TEST(Iterator_map, end) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);

  s21::map<int, int> m1{p1, p2, p3};

  s21::map<int, int>::iterator i = m1.begin();

  int a = 1;

  while (i != m1.end()) {
    ++a;
    i++;
  }

  EXPECT_EQ(a, 4);
}

TEST(Iterator_map, const_iter) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  s21::map<int, int> m1{p1, p2, p3};
  m1.insert(4, 40);
  m1.insert(11, 110);
  m1.insert(7, 70);
  m1.insert(8, 80);
  m1.insert(9, 90);
  m1.insert(12, 120);

  s21::map<int, int>::const_iterator i = m1.cbegin();

  int a = 0;
  for (; i != m1.cend(); ++i) {
    EXPECT_EQ(i->first * 10, (*i).second);
    ++a;
  }

  EXPECT_EQ(a, 9);
}

TEST(Map_modifiers_map, insert) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3};

  s21::map<int, int>::iterator i = m1.insert(p4).first;

  EXPECT_EQ(m1[4], 40);
  EXPECT_EQ(i.get_node()->parent->key, 3);

  m1.insert(4, 600);
  EXPECT_EQ(m1[4], 40);
}

TEST(Map_modifiers_map, insert_or_assign) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3};

  m1.insert(p4);

  EXPECT_EQ(m1[4], 40);

  m1.insert_or_assign(4, 600);
  EXPECT_EQ(m1[4], 600);
}

TEST(Map_modifiers_map, erase1) {
  pair<int, int> p3(3, 30);
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p5(5, 20);
  pair<int, int> p6(6, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4, p5, p6};

  s21::map<int, int>::iterator i = m1.begin();

  m1.erase(i);

  EXPECT_ANY_THROW(m1.at(1));
  EXPECT_EQ(m1.contains(1), false);
}

TEST(Map_modifiers_map, erase2) {
  pair<int, int> p3(3, 30);
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p5(5, 20);
  pair<int, int> p6(6, 30);
  pair<int, int> p4(4, 40);

  s21::map<int, int> m1{p1, p2, p3, p4, p5, p6};

  s21::map<int, int>::iterator i = m1.begin();

  m1.erase(i);

  i = m1.begin();
  ++i;
  ++i;
  ++i;
  ++i;
  m1.erase(i);
  i = m1.begin();
  ++i;
  ++i;
  m1.erase(i);

  EXPECT_EQ(m1.size(), (size_t)3);
  EXPECT_EQ(m1.contains(4), false);
}

TEST(Map_modifiers, erase3) {
  s21::map<int, int> m1;
  m1.insert(10, 10);
  m1.insert(3, 30);
  m1.insert(1, 10);
  m1.insert(2, 20);
  m1.insert(5, 20);
  m1.insert(6, 30);
  m1.insert(4, 40);
  m1.insert(11, 110);
  m1.insert(7, 70);
  m1.insert(8, 80);
  m1.insert(9, 90);
  m1.insert(12, 120);

  for (auto i = m1.begin(); i != m1.end(); i = m1.begin()) {
    m1.erase(i);
  }

  EXPECT_EQ(m1.empty(), true);
}

TEST(Map_modifiers, erase4) {
  s21::map<int, int> m1;
  m1.insert(10, 10);
  m1.insert(3, 30);
  m1.insert(1, 10);
  m1.insert(2, 20);
  m1.insert(5, 20);
  m1.insert(6, 30);
  m1.insert(4, 40);
  m1.insert(11, 110);
  m1.insert(7, 70);
  m1.insert(8, 80);
  m1.insert(9, 90);
  m1.insert(12, 120);

  while (m1.size() != (size_t)0) {
    auto i = m1.begin();
    for (int j = 0; j < static_cast<int>(m1.size()) - 3; ++j) {
      ++i;
    }
    m1.erase(i);
  }

  EXPECT_EQ(m1.empty(), true);
}

TEST(Map_modifiers, clear) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);
  pair<int, int> p5(5, 20);
  pair<int, int> p6(6, 30);

  s21::map<int, int> m1{p1, p2, p3, p4, p5, p6};

  m1.clear();

  EXPECT_EQ(m1.empty(), true);
}

TEST(Map_modifiers, swap) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(4, 40);
  pair<int, int> p5(5, 20);
  pair<int, int> p6(6, 30);

  s21::map<int, int> m1{p1, p2};
  s21::map<int, int> m2{p3, p4, p5, p6};

  m1.swap(m2);

  EXPECT_EQ(m1.contains(1), false);
  EXPECT_EQ(m1.contains(2), false);
  EXPECT_EQ(m1.contains(3), true);
  EXPECT_EQ(m1.contains(4), true);
  EXPECT_EQ(m1.size(), (size_t)4);

  EXPECT_EQ(m2.contains(3), false);
  EXPECT_EQ(m2.contains(4), false);
  EXPECT_EQ(m2.contains(1), true);
  EXPECT_EQ(m2.contains(2), true);
  EXPECT_EQ(m2.size(), (size_t)2);
}

TEST(Map_modifiers, merge) {
  pair<int, int> p1(1, 10);
  pair<int, int> p2(2, 20);
  pair<int, int> p3(3, 30);
  pair<int, int> p4(3, 9999);
  pair<int, int> p5(5, 20);
  pair<int, int> p6(6, 30);

  s21::map<int, int> m1{p1, p2, p3};
  s21::map<int, int> m2{p4, p5, p6};

  m1.merge(m2);

  EXPECT_EQ(m1.at(3), 30);
  EXPECT_EQ(m2.at(3), 9999);

  EXPECT_EQ(m1.at(5), 20);
  EXPECT_EQ(m1.at(6), 30);

  EXPECT_EQ(m1.size(), (size_t)5);
  EXPECT_EQ(m2.size(), (size_t)1);
}
