#ifndef S21_CONTAINERS_S21_SET_TPP_
#define S21_CONTAINERS_S21_SET_TPP_

#include "s21_set.h"

namespace s21 {
template <class K>
set<K>::set() : m_() {}

template <class K>
set<K>::~set() {}

template <class K>
set<K>::set(std::initializer_list<K> const& items) {
  for (auto item : items) {
    insert(item);
  }
}

template <class K>
set<K>::set(const set& s) : m_(s.m_) {
  // auto i = s.begin();
  // while (i != s.end()) {
  //   insert()
  // }
}

template <class K>
set<K>::set(set&& s) : m_(s.m_) {
  s.clear();
}

template <class K>
typename set<K>::size_type set<K>::size() {
  return m_.size();
}

template <class K>
typename set<K>::size_type set<K>::max_size() {
  return m_.max_size();
}

template <class K>
typename set<K>::iterator set<K>::begin() {
  return m_.begin();
}

template <class K>
typename set<K>::iterator set<K>::end() {
  return m_.end();
}

template <class K>
typename set<K>::const_iterator set<K>::cbegin() {
  return m_.cbegin();
}

template <class K>
typename set<K>::const_iterator set<K>::cend() {
  return m_.cend();
}

template <class K>
bool set<K>::empty() {
  return m_.empty();
}

template <class K>
std::pair<typename set<K>::iterator, bool> set<K>::insert(const K& key) {
  obj_ dummy;
  pair<iterator, bool> result = m_.insert(key, dummy);
  return result;
}

template <class K>
void set<K>::clear() {
  m_.clear();
}

template <class K>
void set<K>::swap(set& other) {
  m_.swap(other.m_);
}

template <class K>
void set<K>::merge(set& other) {
  m_.merge(other.m_);
}

template <class K>
void set<K>::erase(iterator pos) {
  m_.erase(pos);
}

template <class K>
bool set<K>::contains(const K& key) {
  return m_.contains(key);
}

template <class K>
typename set<K>::iterator set<K>::find(const K& key) {
  if (!m_.contains(key)) {
    iterator i = end();
    return i;
  }
  iterator i = insert(key).first;
  return i;
}
}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_TPP_