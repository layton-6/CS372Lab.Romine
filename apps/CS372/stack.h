// From Dr. Lewis' GitHub repository.

#pragma once
#include "seqcontainer.h"
#include "list.h"
template <typename T>
class Stack : public SeqContainer<T> {
private:
   List<T> stackList;
public:
  Stack() : SeqContainer<T>() {}
  Stack(Stack &rhs) : SeqContainer<T>(rhs) {}
  ~Stack() { }
   bool  empty() {return stackList.empty();}
   void push(T data) {stackList.push_front(data);}
   void pop() { return stackList.pop_front(); }
   T front() { return stackList.front(); }
   T back() { return stackList.back(); }
   void traverse(void (*doIt)(T &data)){
      stackList.traverse(doIt);
   };
};
