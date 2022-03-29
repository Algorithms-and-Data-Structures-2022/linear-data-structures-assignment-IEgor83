#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* new_node = new Node(value);
    if (size_ == 0){
      front_ = back_ = new_node;
    }
    else{
      back_->next = new_node;
      back_ = new_node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index >= 0 and index <= size_){
      if(index == 0){
        Node* new_node = new Node(value);
        new_node->next = front_;
        front_ = new_node;
        size_ += 1;
        if (size_ == 1){
          back_ = new_node;
        }
      }
      else if (index == size_){
        LinkedList::Add(value);
      }
      else {
        Node* a = new Node(value);
        a->next = LinkedList::FindNode(index);
        LinkedList::FindNode(index - 1)->next = a;
        size_ += 1;
      }
      return true;
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (LinkedList::FindNode(index) != nullptr){
      LinkedList::FindNode(index)->value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 and index < size_){
      int elem;
      if(index == 0){
        Node* a = front_->next;
        elem = front_->value;
        delete front_;
        front_ = a;
        if (size_ == 1){
          back_ = front_;
        }
      }
      else if (index == size_-1){
        elem = back_->value;
        delete back_;
        LinkedList::FindNode(index-1)->next = nullptr;
        back_ = LinkedList::FindNode(index-1);
      }
      else {
        elem = LinkedList::FindNode(index)->value;
        Node* a = LinkedList::FindNode(index)->next;
        delete LinkedList::FindNode(index);
        LinkedList::FindNode(index-1)->next = a;
      }
      size_ -= 1;
      return elem;
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /**/){
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }

    size_ = 0;
    back_ = nullptr;
    front_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (LinkedList::FindNode(index) != nullptr){
      return LinkedList::FindNode(index)->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* a = front_;
    for (int i = 0; i < size_; i++){
      if (a->value == value){
        return i;
      }
      a = a->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    if (LinkedList::IndexOf(value) != std::nullopt){
      return true;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr){
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr){
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= 0 and index < size_){
      Node* a = front_;
      for (int i = 0; i < index; i++){
        a = a->next;
      }
      return a;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment