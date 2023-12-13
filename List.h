#ifndef LIST_H
#define LIST_H

#include "Reservation.h"

class List {
private:
    class Node {
    public:
        Reservation *info;
        Node *next;
        Node(Reservation *_info, Node *_next = nullptr);
        ~Node();
    };

    Node *first;

    static void destroy(Node *node);
    static void copy(Node *node, Node *newNode);
    static void swap(Node *prev1, Node *node1, Node *prev2, Node *node2);
    static unsigned int counter;

public:
    List();
    List(const List &list);
    List& operator=(const List &list);
    ~List();

    class ConstIterator {
      friend class List;

    private:
      const Node *ptr;
      bool pastTheEnd;
      ConstIterator(const Node *p, bool pte = false);

    public:
      ConstIterator();
      ConstIterator& operator++();
      ConstIterator operator++(int);
      const Reservation*  operator*() const;
      Reservation* const*  operator->() const;
      bool operator==(const ConstIterator& cit) const;
      bool operator!=(const ConstIterator& cit) const;
    };

    class Iterator {
        friend class List;

      private:
        Node *ptr;
        bool pastTheEnd;
        Iterator(Node *p, bool pte = false);

      public:
        Iterator();
        Iterator& operator++();
        Iterator operator++(int);
        Reservation*  operator*() const;
        Reservation**  operator->() const;
        bool operator==(const Iterator& cit) const;
        bool operator!=(const Iterator& cit) const;
    };

    Iterator begin() const;
    Iterator end() const;
    ConstIterator constBegin() const;
    ConstIterator constEnd() const;

    void insertFront(Reservation *t);
    void removeFront();
    void remove(Reservation *t);
    bool isEmpty() const;

    List searchByDate(unsigned int dateY, unsigned int dateM, unsigned int dateD);
    List searchByName(std::string pattern);
    List searchByPhone(std::string pattern);
    List searchByEmail(std::string pattern);
};

#endif // LIST_H
