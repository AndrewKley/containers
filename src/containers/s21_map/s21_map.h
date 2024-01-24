#ifndef S21_CONTAINERS_S21_MAP_H_
#define S21_CONTAINERS_S21_MAP_H_

#include <limits>
#include <stdexcept>
#include <utility>

#if defined(linux) || defined(__linux)
#define MAX_SIZE 2
#endif

#if __APPLE__
#define MAX_SIZE 1
#endif

using namespace std;

namespace s21 {
template <class Key, class Value>
class map {
 private:
  static const bool RED_ = false;
  static const bool BLACK_ = true;
  class Node {
   public:
    Key key;
    Value value;
    Node* parent;
    Node* left;
    Node* right;
    bool color = BLACK_;

    Node(const Key& key, const Value& value, Node* parent)
        : key(key),
          value(value),
          parent(parent),
          left(nullptr),
          right(nullptr) {}
  };

 public:
  class MapIterator {
    friend class map<Key, Value>;

   protected:
    Node* node_;
    int last_;
    pair<Key, Value> val_;

   public:
    MapIterator(Node* ptr) : node_(ptr), last_(false) {
      if (node_ != nullptr) val_ = pair<Key, Value>(node_->key, node_->value);
    }
    MapIterator(Node* ptr, bool is_last) : node_(ptr), last_(is_last) {
      if (node_ != nullptr) val_ = pair<Key, Value>(node_->key, node_->value);
    }
    MapIterator& operator++();
    MapIterator operator++(int);
    pair<Key, Value>& operator*();
    pair<Key, Value>* operator->();
    bool operator!=(const MapIterator& i) const;
    bool operator==(const MapIterator& i) const;
    Node* get_node() const;
    ~MapIterator() {}
  };

  class MapConstIterator : public MapIterator {
    friend class map<Key, Value>;

   private:
    Node* node_;
    bool last_;
    pair<Key, Value> val_;

   public:
    MapConstIterator(Node* ptr) : MapIterator(ptr), node_(ptr), last_(false) {
      if (node_ != nullptr)
        pair<const Key, const Value> val_(node_->key, node_->value);
    }
    MapConstIterator(Node* ptr, bool is_last)
        : MapIterator(ptr, is_last), node_(ptr), last_(is_last) {
      if (node_ != nullptr)
        pair<const Key, const Value> val_(node_->key, node_->value);
    }
    MapConstIterator& operator++();
    const pair<Key, Value>& operator*();
    const pair<Key, Value>* operator->();
    bool operator!=(const MapConstIterator& i) const;
    ~MapConstIterator() {}
  };

 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename map<Key, Value>::MapIterator;
  using const_iterator = typename map<Key, Value>::MapConstIterator;
  using size_type = size_t;

  map();
  ~map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  void operator=(map&& m);

  Value& at(const Key& key);
  Value& operator[](const Key& key);

  bool empty();
  size_type size();
  size_type max_size();

  iterator begin();
  iterator end();

  const_iterator cbegin() const;
  const_iterator cend() const;

  std::pair<iterator, bool> insert(const pair<const Key, Value>& value);
  std::pair<iterator, bool> insert(const Key& key, const Value& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const Value& obj);
  void erase(iterator pos);
  void clear();
  void swap(map& other);
  void merge(map<Key, Value>& other);

  bool contains(const Key& key);

 private:
  Node* root_ = nullptr;
  size_type size_ = 0;

  std::pair<iterator, bool> insert_(const pair<const Key, Value>& value,
                                    bool replace);
  bool insert_(Node* n);
  Node* add_entry_(const Key& key, const Value& value, Node* parent);
  void destroy_tree_(Node* root);
  void fix_after_insertion_(Node* n);
  void fix_after_deletion_(Node* replacement);
  void set_color_(Node* node, bool color);
  void rotate_left_(Node* p);
  void rotate_right_(Node* p);
  bool color_of_(Node* n);
  Node* parent_(Node* n);
  Node* left_(Node* n);
  Node* right_(Node* n);
};
}  // namespace s21

#endif  // S21_CONTAINERS_S21_MAP_H_