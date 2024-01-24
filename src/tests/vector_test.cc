#include "../containers/s21_vector/vector.h"

#include <gtest/gtest.h>

#include <vector>

TEST(Constructor, con1) {
  s21::vector<int> v;
  std::vector<int> e;
  EXPECT_EQ(v.size(), e.size());
  EXPECT_EQ(v.capacity(), e.capacity());
  EXPECT_EQ(v.data(), e.data());
}

TEST(Constructor, con2) {
  s21::vector<int> v(5);
  vector<int> e(5);
  EXPECT_EQ(v.size(), e.size());
  EXPECT_EQ(v.capacity(), e.capacity());
  EXPECT_NE(v.data(), nullptr);
}

TEST(Constructor, con3) {
  s21::vector<int> v(500);
  vector<int> e(500);
  EXPECT_EQ(v.size(), e.size());
  EXPECT_EQ(v.capacity(), e.capacity());
  EXPECT_NE(v.data(), nullptr);
}

TEST(Constructor, con4) {
  s21::vector<int> v(0);
  vector<int> e(0);
  EXPECT_EQ(v.size(), e.size());
  EXPECT_EQ(v.capacity(), e.capacity());
  EXPECT_NE(v.data(), e.data());
}

TEST(Constructor, con5) {
  try {
    s21::vector<int> s21_v(-1);
  } catch (std::length_error const& err) {
    EXPECT_STREQ(err.what(), "The size cannot be larger than the max size");
  }
}

TEST(Constructor, con6) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_tmp(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_tmp(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
  EXPECT_EQ(s21_tmp.empty(), std_tmp.empty());
}

TEST(Constructor, con7) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_tmp(s21_v);
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_tmp(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
  EXPECT_EQ(s21_tmp.empty(), std_tmp.empty());

  EXPECT_EQ(s21_tmp[0], std_tmp[0]);
  EXPECT_EQ(s21_tmp[1], std_tmp[1]);
  EXPECT_EQ(s21_tmp[2], std_tmp[2]);
  EXPECT_EQ(s21_tmp[3], std_tmp[3]);
  EXPECT_EQ(s21_tmp[4], std_tmp[4]);
}

TEST(Constructor, con8) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_tmp(std::move(s21_v));
  std::vector<int> std_v;
  std::vector<int> std_tmp(std::move(std_v));

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
  EXPECT_EQ(s21_tmp.empty(), std_tmp.empty());
}

TEST(Constructor, con9) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_tmp(std::move(s21_v));
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_tmp(std::move(std_v));

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
  EXPECT_EQ(s21_tmp.empty(), std_tmp.empty());

  EXPECT_EQ(s21_tmp[0], std_tmp[0]);
  EXPECT_EQ(s21_tmp[1], std_tmp[1]);
  EXPECT_EQ(s21_tmp[2], std_tmp[2]);
  EXPECT_EQ(s21_tmp[3], std_tmp[3]);
  EXPECT_EQ(s21_tmp[4], std_tmp[4]);
}

TEST(Functions, fun_reserve1) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.reserve(3);
  std_v.reserve(3);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(Functions, fun_reserve2) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.reserve(3);
  std_v.reserve(3);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_reserve3) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.reserve(0);
  std_v.reserve(0);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_reserve4) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  try {
    s21_v.reserve(-3);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "The size cannot be larger than the max size");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_reserve5) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.reserve(16);
  std_v.reserve(16);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_operator_bracket1) {
  s21::vector<int> s21_v{1, 2, 3};
  try {
    s21_v[3];
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_operator_bracket2) {
  s21::vector<int> s21_v;
  try {
    s21_v[0];
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_operator_bracket3) {
  s21::vector<int> s21_v;
  try {
    s21_v[-3];
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_operator_bracket4) {
  s21::vector<int> s21_v{1, 2, 3};
  EXPECT_EQ(s21_v[1], 2);
}

TEST(Functions, fun_at1) {
  s21::vector<int> s21_v{1, 2, 3};
  try {
    s21_v.at(3);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_at2) {
  s21::vector<int> s21_v;
  try {
    s21_v[0];
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_at3) {
  s21::vector<int> s21_v;
  try {
    s21_v[-3];
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }
}

TEST(Functions, fun_at4) {
  s21::vector<int> s21_v{1, 2, 3};
  EXPECT_EQ(s21_v[1], 2);
}

TEST(Functions, fun_clear1) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_clear2) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_clear3) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_swap1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_tmp;
  std::vector<int> std_v;
  std::vector<int> std_tmp;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  s21_tmp.swap(s21_v);
  std_tmp.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
}

TEST(Functions, fun_swap2) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_tmp;
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_tmp;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  s21_tmp.swap(s21_v);
  std_tmp.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
  ;
}

TEST(Functions, fun_swap3) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_tmp{1, 2, 3};
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_tmp{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  s21_tmp.swap(s21_v);
  std_tmp.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
}

TEST(Functions, fun_push_back1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.push_back(4);
  std_v.push_back(4);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
}

TEST(Functions, fun_push_back2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.push_back(4);
  std_v.push_back(4);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_push_back3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.push_back(4);
  std_v.push_back(4);
  s21_v.push_back(40);
  std_v.push_back(40);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_erase1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.erase(s21_v.begin());
  std_v.erase(std_v.begin());

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
}

TEST(Functions, fun_erase2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.erase(s21_v.begin() + 2);
  std_v.erase(std_v.begin() + 2);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
}

TEST(Functions, fun_erase3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
}

TEST(Functions, fun_erase4) {
  s21::vector<int> s21_v{1, 2, 3};
  s21::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  try {
    s21_v.erase(s21_v.begin() + 10);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  try {
    std_v.erase(s21_v.begin() + 10);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(Functions, fun_erase5) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  try {
    s21_v.erase(s21_v.begin());
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  try {
    std_v.erase(s21_v.begin());
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_erase6) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  try {
    s21_v.erase(s21_v.end());
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  try {
    std_v.erase(s21_v.end());
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_erase7) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  try {
    s21_v.erase(s21_v.end() - 1);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  try {
    std_v.erase(s21_v.end() - 1);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_erase8) {
  s21::vector<int> s21_v{1};
  std::vector<int> std_v{1};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_erase9) {
  s21::vector<int> s21_v{1, 2};
  std::vector<int> std_v{1, 2};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
}

TEST(Functions, fun_insert1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.insert(s21_v.begin(), 7);
  std_v.insert(std_v.begin(), 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_insert2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.insert(s21_v.begin() + 2, 7);
  std_v.insert(std_v.begin() + 2, 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_insert3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.insert(s21_v.end() - 1, 7);
  std_v.insert(std_v.end() - 1, 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_insert4) {
  s21::vector<int> s21_v{1, 2, 3};
  s21::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  try {
    s21_v.insert(s21_v.end() + 10, 7);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  try {
    std_v.insert(s21_v.end() + 10, 7);
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(), "Index out of range");
  }

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(Functions, fun_insert5) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  s21_v.insert(s21_v.begin(), 7);
  std_v.insert(s21_v.begin(), 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_insert6) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  s21_v.insert(s21_v.end(), 7);
  std_v.insert(s21_v.end(), 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_insert7) {
  s21::vector<int> s21_v;
  s21::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());

  s21_v.insert(s21_v.end() - 1, 7);
  std_v.insert(s21_v.end() - 1, 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.size());
}

TEST(Functions, fun_insert8) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.insert(s21_v.begin(), 7);
  std_v.insert(std_v.begin(), 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
}

TEST(Functions, fun_insert9) {
  s21::vector<int> s21_v{1};
  std::vector<int> std_v{1};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.insert(s21_v.begin(), 7);
  std_v.insert(std_v.begin(), 7);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
}

TEST(Functions, fun_operator_eq1) {
  s21::vector<int> s21_v{1, 2, 3};
  s21::vector<int> s21_tmp;
  std::vector<int> std_v{1, 2, 3};
  std::vector<int> std_tmp;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  s21_tmp = std::move(s21_v);
  std_tmp = std::move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  EXPECT_EQ(s21_tmp[0], std_tmp[0]);
  EXPECT_EQ(s21_tmp[1], std_tmp[1]);
  EXPECT_EQ(s21_tmp[2], std_tmp[2]);
}

TEST(Functions, fun_operator_eq2) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_tmp;
  std::vector<int> std_v;
  std::vector<int> std_tmp;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());

  s21_tmp = std::move(s21_v);
  std_tmp = std::move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_tmp.size(), std_tmp.size());
  EXPECT_EQ(s21_tmp.capacity(), std_tmp.capacity());
}

TEST(Functions, fun_shrink_to_fit1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(Functions, fun_shrink_to_fit2) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
}

TEST(Functions, fun_shrink_to_fit3) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.push_back(5);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
  EXPECT_EQ(s21_v[3], std_v[3]);
  EXPECT_EQ(s21_v[4], std_v[4]);
}
