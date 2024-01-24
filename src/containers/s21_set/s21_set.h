#ifndef S21_CONTAINERS_S21_SET_H_
#define S21_CONTAINERS_S21_SET_H_

#include <limits>
#include <stdexcept>
#include <utility>

#include "../s21_map/s21_map.h"
#include "../s21_map/s21_map.tpp"

#if defined(linux) || defined(__linux)
#define MAX_SIZE 2
#endif

#if __APPLE__
#define MAX_SIZE 1
#endif

using namespace std;

namespace s21 {

template <class Key>
class set {
 private:
  class obj_ {};
  s21::map<Key, obj_> m_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using size_type = size_t;
  using iterator = typename map<Key, obj_>::iterator;
  using const_iterator = typename map<Key, obj_>::const_iterator;
  set();
  ~set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  void operator=(set&& s);

  iterator begin();
  iterator end();

  const_iterator cbegin();
  const_iterator cend();

  bool empty();
  size_type size();
  size_type max_size();

  std::pair<iterator, bool> insert(const Key& key);
  void clear();
  void swap(set& other);
  void merge(set<Key>& other);
  void erase(iterator pos);

  bool contains(const Key& key);
  iterator find(const Key& key);
};
}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_H_