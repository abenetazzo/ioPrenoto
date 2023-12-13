#include "List.h"

unsigned int List::counter = 0;

List::Node::Node(Reservation *_info, Node *_next) : info(_info), next(_next) {}

List::Node::~Node() {
    delete info;
}

void List::destroy(Node *node) {
    if (node) {
        destroy(node->next);
        delete node;
    }
}

void List::copy(Node *node, Node *newNode) {
    if (node == nullptr) {
        newNode = nullptr;
        return;
    }
    Node *ptr = node;
    newNode = new Node(ptr->info, ptr->next);
    while(ptr->next != nullptr) {
        ptr = ptr->next;
        newNode->next = new Node(ptr->info, ptr->next);
        newNode = newNode->next;
    }
}

void List::swap(Node *prev1, Node *node1, Node *prev2, Node *node2) {
    // PRE: if node1 = first then prev1 = nullptr
    //      elif node2 = first then prev2 = nullptr
    //      else prev1->next = node1 & prev2->next = node2
    if (prev1) prev1->next = node2;
    if (prev2) prev2->next = node1;
    Node *next2 = node2->next;
    node2->next = node1->next;
    node1->next = next2;
}

List::List() : first(nullptr) {}

List::List(const List &list) : first(nullptr) {
    copy(list.first, first);
}

List& List::operator=(const List &list) {
    if (this != &list) {
        destroy(first);
        copy(list.first, first);
    }
    return *this;
}

List::~List() {
    if (first) destroy(first);
}

List::ConstIterator::ConstIterator(const Node *p, bool pte): ptr(p), pastTheEnd(pte) {}

List::ConstIterator::ConstIterator(): ptr(nullptr), pastTheEnd(false) {}

List::ConstIterator& List::ConstIterator::operator++() {
  if (ptr && !pastTheEnd ) {
      if (ptr->next == nullptr) {
          ptr = ptr + 1;
          pastTheEnd = true;
      }
      else ptr = ptr->next;
  }
  return *this;
}

List::ConstIterator List::ConstIterator::operator++(int) {
  ConstIterator tmp(*this);
  if (ptr && !pastTheEnd ) {
      if (ptr->next == nullptr) {
          ptr += 1;
          pastTheEnd = true;
      }
      else ptr = ptr->next;
  }
  return tmp;
}

const Reservation*  List::ConstIterator::operator*() const {
  return ptr->info;
}

Reservation* const*  List::ConstIterator::operator->() const {
  return &(ptr->info);
}

bool List::ConstIterator::operator==(const ConstIterator& cit) const {
  return ptr == cit.ptr;
}

bool List::ConstIterator::operator!=(const ConstIterator& cit) const {
  return ptr != cit.ptr;
}

List::Iterator::Iterator(Node *p, bool pte): ptr(p), pastTheEnd(pte) {}

List::Iterator::Iterator(): ptr(nullptr), pastTheEnd(false) {}

List::Iterator& List::Iterator::operator++() {
  if (ptr && !pastTheEnd ) {
      if (ptr->next == nullptr) {
          ptr = ptr + 1;
          pastTheEnd = true;
      }
      else ptr = ptr->next;
  }
  return *this;
}

List::Iterator List::Iterator::operator++(int) {
  Iterator tmp(*this);
  if (ptr && !pastTheEnd ) {
      if (ptr->next == nullptr) {
          ptr += 1;
          pastTheEnd = true;
      }
      else ptr = ptr->next;
  }
  return tmp;
}

Reservation*  List::Iterator::operator*() const {
  return ptr->info;
}

Reservation**  List::Iterator::operator->() const {
  return &(ptr->info);
}

bool List::Iterator::operator==(const Iterator& cit) const {
  return ptr == cit.ptr;
}

bool List::Iterator::operator!=(const Iterator& cit) const {
  return ptr != cit.ptr;
}

List::Iterator List::begin() const {
  if (first != nullptr) return Iterator(first);
  return Iterator();
}

List::Iterator List::end() const {
  if(first == nullptr) return Iterator();
  Node *f = first;
  while (f->next != nullptr) f = f->next;
  return Iterator(f+1,true);
}

List::ConstIterator List::constBegin() const {
  if (first != nullptr) return ConstIterator(first);
  return ConstIterator();
}

List::ConstIterator List::constEnd() const {
  if(first == nullptr) return ConstIterator();
  Node *f = first;
  while (f->next != nullptr) f = f->next;
  return ConstIterator(f+1,true);
}

void List::insertFront(Reservation *t) {
    first = new Node(t, first);
}

void List::removeFront() {
    if (first) {
        Node *ptr = first;
        first = first->next;
        delete ptr;
    }
}

void List::remove(Reservation *t) {
    if (first) {
        Node *ptr = first, *prev = nullptr;
        while (ptr->next != nullptr && ptr->info != t) {
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr->info == t) {
            if (ptr == first) first = ptr->next;
            else prev->next = ptr->next;
            delete ptr;
        }
    }
}

bool List::isEmpty() const {
    return first == nullptr;
}

List List::searchByDate(unsigned int dateY, unsigned int dateM, unsigned int dateD) {
    List results;
    if (first != nullptr) {
        Node *node = first;
        while (node != nullptr) {
            if (dateY >= node->info->getArrDateY() && dateY <= node->info->getDepDateY())
                if (dateM >= node->info->getArrDateM() && dateM <= node->info->getDepDateM())
                    if (dateD >= node->info->getArrDateD() && dateD <= node->info->getDepDateD())
                        results.insertFront(node->info);
            node = node->next;
        }
    }
    return results;
}

List List::searchByName(std::string pattern) {
    List results;
    if (first != nullptr) {
        Node *node = first;
        while (node != nullptr) {
            if (node->info->getName().find(pattern) != std::string::npos)
                results.insertFront(node->info);
            else if (node->info->getSurname().find(pattern) != std::string::npos)
                results.insertFront(node->info);
            node = node->next;
        }
    }
    return results;
}

List List::searchByPhone(std::string pattern) {
    List results;
    if (first != nullptr) {
        Node *node = first;
        while (node != nullptr) {
            if (node->info->getPhone().find(pattern) != std::string::npos)
                results.insertFront(node->info);
            node = node->next;
        }
    }
    return results;
}

List List::searchByEmail(std::string pattern) {
    List results;
    if (first != nullptr) {
        Node *node = first;
        while (node != nullptr) {
            if (node->info->getEmail().find(pattern) != std::string::npos)
                results.insertFront(node->info);
            node = node->next;
        }
    }
    return results;
}
