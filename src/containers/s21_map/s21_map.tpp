#ifndef S21_CONTAINERS_S21_MAP_TPP_
#define S21_CONTAINERS_S21_MAP_TPP_

#include "s21_map.h"

namespace s21 {
template <class K, class V>
map<K, V>::map() : size_(0) {
  root_ = nullptr;
}

template <class K, class V>
map<K, V>::~map() {
  clear();
}

template <class K, class V>
map<K, V>::map(std::initializer_list<value_type> const& items)
    : root_(nullptr), size_(0) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <class K, class V>
map<K, V>::map(const map<K, V>& m) : size_(0) {
  for (map<K, V>::iterator it = m.cbegin(); it != m.cend(); ++it) {
    insert(it->first, it->second);
  }
}

template <class K, class V>
map<K, V>::map(map&& m) : root_(m.root_), size_(m.size_) {
  m.root_ = nullptr;
  m.size_ = 0;
}

template <class K, class V>
typename map<K, V>::size_type map<K, V>::size() {
  return size_;
}

template <class K, class V>
typename map<K, V>::size_type map<K, V>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(map<K, V>::Node) /
         MAX_SIZE;
}

template <class K, class V>
void map<K, V>::clear() {
  if (size_ != 0) destroy_tree_(root_);
  size_ = 0;
}

template <class K, class V>
bool map<K, V>::empty() {
  return size_ == 0;
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> map<K, V>::insert(const K& key,
                                                           const V& obj) {
  pair<K, V> p(key, obj);
  return insert_(p, false);
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> map<K, V>::insert(
    const pair<const K, V>& value) {
  return insert_(value, false);
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> map<K, V>::insert_or_assign(
    const K& key, const V& obj) {
  pair<K, V> p(key, obj);
  return insert_(p, true);
}

template <class K, class V>
void map<K, V>::erase(iterator pos) {
  --size_;
  Node* p = pos.get_node();

  if (p == nullptr) return;

  if (p->left != nullptr && p->right != nullptr) {
    Node* s = p->right;
    while (s->left != nullptr) {
      s = s->left;
    }
    p->key = s->key;
    p->value = s->value;
    p = s;
  }

  Node* replacement = (p->left != nullptr ? p->left : p->right);
  if (replacement != nullptr) {
    replacement->parent = p->parent;
    if (p->parent == nullptr) {
      root_ = replacement;
    } else if (p == left_(parent_(p))) {
      p->parent->left = replacement;
    } else {
      p->parent->right = replacement;
    }
    p->left = p->right = p->parent = nullptr;
    if (p->color == BLACK_) fix_after_deletion_(replacement);
    delete (p);
  } else if (p->parent == nullptr) {  // the only node
    delete p;
    root_ = nullptr;
  } else {  // no children
    if (p->color == BLACK_) {
      fix_after_deletion_(p);
    }
    if (p->parent != nullptr) {
      if (p == p->parent->left)
        p->parent->left = nullptr;
      else if (p == p->parent->right)
        p->parent->right = nullptr;
      p->parent = nullptr;
      delete p;
    }
  }
}

template <class K, class V>
void map<K, V>::swap(map& other) {
  Node* other_root = other.root_;
  other.root_ = root_;
  root_ = other_root;
  size_type s = size();
  size_ = other.size();
  other.size_ = s;
}

template <class K, class V>
void map<K, V>::merge(map<K, V>& other) {
  bool result;
  iterator iter = other.begin();
  while (iter != other.end()) {
    result = insert_(iter.get_node());
    if (result) {
      other.erase(iter);
    } else {
      ++iter;
      continue;
    }
    iter = other.begin();
  }
}

template <class K, class V>
V& map<K, V>::at(const K& key) {
  if (empty()) {
    throw std::logic_error("Map is empty");
  }
  Node* n = root_;
  do {
    if (key < n->key) {
      n = n->left;
    } else if (key > n->key) {
      n = n->right;
    } else {
      return n->value;
    }
  } while (n != nullptr);
  throw std::logic_error("No such key");
}

template <class K, class V>
V& map<K, V>::operator[](const K& key) {
  return at(key);
}

template <typename K, typename V>
bool map<K, V>::contains(const K& key) {
  if (empty()) {
    return false;
  }
  try {
    at(key);
  } catch (logic_error& e) {
    return false;
  }
  return true;
}

template <class K, class V>
typename map<K, V>::MapIterator& map<K, V>::MapIterator::operator++() {
  // delete val_;
  if (this->last_ == true) {
    return *this;
  }
  Node* cur = node_;
  Node* last = node_;
  while (last->parent != nullptr) {
    last = last->parent;
  }
  while (last->right != nullptr) {
    last = last->right;
  }
  if (node_ == last) {
    last_ = true;
    return *this;
  }
  if (cur->right != nullptr) {
    cur = cur->right;
    while (cur->left != nullptr) {
      cur = cur->left;
    }
  } else if (cur->parent != nullptr) {
    do {
      if (cur->parent == nullptr) return *this;
      cur = cur->parent;
    } while (cur->key < node_->key);
  }
  node_ = cur;
  val_ = pair<K, V>(node_->key, node_->value);
  return *this;
}

template <class K, class V>
typename map<K, V>::MapIterator map<K, V>::MapIterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class K, class V>
pair<K, V>& map<K, V>::MapIterator::operator*() {
  return val_;
}

template <class K, class V>
pair<K, V>* map<K, V>::MapIterator::operator->() {
  return &val_;
}

template <class K, class V>
bool map<K, V>::MapIterator::operator!=(const MapIterator& i) const {
  if (i.node_ == nullptr && node_ == nullptr) {
    return last_ != i.last_;
  }
  return node_->key != i.node_->key || (last_ != i.last_);
}

template <class K, class V>
bool map<K, V>::MapIterator::operator==(const MapIterator& i) const {
  if (i.node_ == nullptr && node_ == nullptr) {
    return last_ == i.last_;
  }
  return node_->key == i.node_->key && (last_ == i.last_);
}

template <class K, class V>
typename map<K, V>::MapConstIterator&
map<K, V>::MapConstIterator::operator++() {
  // delete val_;
  if (last_ == true) {
    return *this;
  }
  Node* cur = node_;
  Node* last = node_;
  while (last->parent != nullptr) {
    last = last->parent;
  }
  while (last->right != nullptr) {
    last = last->right;
  }
  if (node_ == last) {
    last_ = true;
    return *this;
  }
  if (cur->right != nullptr) {
    cur = cur->right;
    while (cur->left != nullptr) {
      cur = cur->left;
    }
  } else if (cur->parent != nullptr) {
    do {
      if (cur->parent == nullptr) return *this;
      cur = cur->parent;
    } while (cur->key < node_->key);
  }
  node_ = cur;
  val_ = pair<K, V>(node_->key, node_->value);
  return *this;
}

template <class K, class V>
bool map<K, V>::MapConstIterator::operator!=(const MapConstIterator& i) const {
  if (i.node_ == nullptr && node_ == nullptr) {
    return last_ != i.last_;
  }
  return node_->key != i.node_->key || (last_ != i.last_);
}

template <class K, class V>
const pair<K, V>& map<K, V>::MapConstIterator::operator*() {
  return val_;
}

template <class K, class V>
const pair<K, V>* map<K, V>::MapConstIterator::operator->() {
  return &val_;
}

template <class K, class V>
typename map<K, V>::Node* map<K, V>::MapIterator::get_node() const {
  return node_;
}

template <class K, class V>
typename map<K, V>::iterator map<K, V>::begin() {
  if (root_ == nullptr) {
    MapIterator i(root_, true);
    return i;
  }
  Node* n = root_;
  while (n->left != nullptr) {
    n = n->left;
  }
  MapIterator i(n);
  // i.val_ = new pair<K, V>(n->key, n->value);
  return i;
}

template <class K, class V>
typename map<K, V>::iterator map<K, V>::end() {
  if (root_ == nullptr) {
    MapIterator i(root_, true);
    return i;
  }
  Node* n = root_;
  while (n->right != nullptr) {
    n = n->right;
  }
  MapIterator i(n, true);
  // i.val_ = new pair<K, V>(n->key, n->value);
  return i;
}

template <class K, class V>
typename map<K, V>::const_iterator map<K, V>::cbegin() const {
  if (root_ == nullptr) {
    MapConstIterator i(root_, true);
    return i;
  }
  Node* n = root_;
  while (n->left != nullptr) {
    n = n->left;
  }
  MapConstIterator i(n);
  // i.val_ = new pair<const K, const V>(i, n->value);
  return i;
}

template <class K, class V>
typename map<K, V>::const_iterator map<K, V>::cend() const {
  if (root_ == nullptr) {
    MapConstIterator i(root_, true);
    return i;
  }
  Node* n = root_;
  while (n->right != nullptr) {
    n = n->right;
  }
  MapConstIterator i(n, true);
  // i.val_ = new pair<const K, const V>(n->key, n->value);
  return i;
}

template <class K, class V>
pair<typename map<K, V>::iterator, bool> map<K, V>::insert_(
    const pair<const K, V>& value, bool replace) {
  Node* cur = root_;
  if (cur == nullptr) {
    root_ = new Node(value.first, value.second, nullptr);
    size_ = 1;
    iterator itr(root_);
    pair<iterator, bool> p(itr, true);
    return p;
  }
  Node* parent = cur;
  do {
    parent = cur;
    if (value.first < cur->key) {
      cur = cur->left;
    } else if (value.first > cur->key) {
      cur = cur->right;
    } else {
      if (replace) {
        cur->value = value.second;
        break;
      } else {
        iterator itr(cur);
        pair<iterator, bool> p(itr, false);
        return p;
      }
    }
  } while (cur != nullptr);
  cur = add_entry_(value.first, value.second, parent);
  iterator itr(cur);
  pair<iterator, bool> p(itr, true);
  return p;
}

template <class K, class V>
bool map<K, V>::insert_(Node* n) {
  Node* cur = root_;
  if (cur == nullptr) {
    root_ = n;
    size_ = 1;
    return true;
  }
  Node* parent = cur;
  do {
    parent = cur;
    if (n->key < cur->key) {
      cur = cur->left;
    } else if (n->key > cur->key) {
      cur = cur->right;
    } else {
      return false;
    }
  } while (cur != nullptr);
  add_entry_(n->key, n->value, parent);
  return true;
}

template <typename K, typename V>
void map<K, V>::destroy_tree_(Node* root) {
  if (root->left != nullptr) {
    destroy_tree_(root->left);
  }
  if (root->right != nullptr) {
    destroy_tree_(root->right);
  }
  delete root;
}

template <class K, class V>
typename map<K, V>::Node* map<K, V>::add_entry_(const K& key, const V& value,
                                                Node* parent) {
  Node* n = new Node(key, value, parent);
  if (key < parent->key)
    parent->left = n;
  else
    parent->right = n;
  fix_after_insertion_(n);
  ++size_;
  return n;
}

template <class K, class V>
bool map<K, V>::color_of_(Node* n) {
  return (n == nullptr ? BLACK_ : n->color);
}

template <class K, class V>
typename map<K, V>::Node* map<K, V>::parent_(Node* n) {
  return (n == nullptr ? nullptr : n->parent);
}

template <class K, class V>
typename map<K, V>::Node* map<K, V>::left_(Node* n) {
  return (n == nullptr ? nullptr : n->left);
}

template <class K, class V>
typename map<K, V>::Node* map<K, V>::right_(Node* n) {
  return (n == nullptr ? nullptr : n->right);
}

template <class K, class V>
void map<K, V>::set_color_(Node* node, bool color) {
  if (node == nullptr) {
    return;
  } else {
    node->color = color;
  }
}

template <class K, class V>
void map<K, V>::fix_after_insertion_(Node* x) {
  x->color = RED_;

  while (x != nullptr && x != root_ && x->parent->color == RED_) {
    if (x->parent != root_ && x->parent == left_(parent_(parent_(x)))) {
      Node* uncle = right_(parent_(parent_(x)));
      if (color_of_(uncle) == RED_) {
        x->parent->color = BLACK_;
        set_color_(uncle, BLACK_);
        set_color_(parent_(parent_(x)), RED_);  // grandfather
        x = parent_(parent_(x));
      } else {
        if (x == x->parent->right) {
          x = x->parent;
          rotate_left_(x);
        }
        set_color_(parent_(x), BLACK_);
        set_color_(parent_(parent_(x)), RED_);
        rotate_right_(parent_(parent_(x)));
      }
    } else {
      Node* uncle = left_(parent_(parent_(x)));
      if (color_of_(uncle) == RED_) {
        set_color_(parent_(x), BLACK_);
        set_color_(uncle, BLACK_);
        set_color_(parent_(parent_(x)), RED_);  // grandfather
        x = parent_(parent_(x));
      } else {
        if (x == left_(parent_(x))) {
          x = parent_(x);
          rotate_right_(x);
        }
        set_color_(parent_(x), BLACK_);
        set_color_(parent_(parent_(x)), RED_);
        rotate_left_(parent_(parent_(x)));
      }
    }
  }
  root_->color = BLACK_;
}

template <class K, class V>
void map<K, V>::fix_after_deletion_(Node* x) {
  while (x != root_ && x->color == BLACK_) {
    if (x == x->parent->left) {
      Node* sib = x->parent->right;
      if (color_of_(sib) == RED_) {
        set_color_(sib, BLACK_);
        set_color_(parent_(x), RED_);
        rotate_left_(x->parent);
        sib = right_(parent_(x));
      }

      if (color_of_(left_(sib)) == BLACK_ && color_of_(right_(sib)) == BLACK_) {
        set_color_(sib, RED_);
        x = x->parent;
      } else {
        if (color_of_(right_(sib)) == BLACK_) {
          set_color_(left_(sib), BLACK_);
          set_color_(sib, RED_);
          rotate_right_(sib);
          sib = right_(parent_(x));
        }
        set_color_(sib, color_of_(parent_(x)));
        set_color_(parent_(x), BLACK_);
        set_color_(right_(sib), BLACK_);
        rotate_left_(parent_(x));
        x = root_;
      }
    } else {  // symmetric
      Node* sib = x->parent->left;
      if (color_of_(sib) == RED_) {
        set_color_(sib, BLACK_);
        set_color_(parent_(x), RED_);
        rotate_right_(parent_(x));
        sib = left_(parent_(x));
      }

      if (color_of_(left_(sib)) == BLACK_ && color_of_(right_(sib)) == BLACK_) {
        set_color_(sib, RED_);
        x = x->parent;
      } else {
        if (color_of_(left_(sib)) == BLACK_) {
          set_color_(right_(sib), BLACK_);
          set_color_(sib, RED_);
          rotate_left_(sib);
          sib = left_(parent_(sib));
        }
        set_color_(sib, color_of_(parent_(x)));
        set_color_(parent_(x), BLACK_);
        set_color_(left_(sib), BLACK_);
        rotate_right_(x->parent);
        x = root_;
      }
    }
  }
  x->color = BLACK_;
}

template <class K, class V>
void map<K, V>::rotate_left_(Node* p) {
  if (p != nullptr) {
    Node* r = right_(p);
    p->right = r->left;
    if (r->left != nullptr) {
      r->left->parent = p;
    }
    r->parent = p->parent;
    if (p->parent == nullptr) {
      root_ = r;
    } else if (p->parent->left == p) {
      p->parent->left = r;
    } else {
      p->parent->right = r;
    }
    r->left = p;
    p->parent = r;
  }
}

template <class K, class V>
void map<K, V>::rotate_right_(Node* p) {
  if (p != nullptr) {
    Node* l = left_(p);
    p->left = l->right;
    if (l->right != nullptr) {
      l->right->parent = p;
    }
    l->parent = p->parent;
    if (p->parent == nullptr)
      root_ = l;
    else if (p->parent->right == p) {
      p->parent->right = l;
    } else {
      p->parent->left = l;
    }
    l->right = p;
    p->parent = l;
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MAP_TPP_