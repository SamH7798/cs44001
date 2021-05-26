// node class tempate used to contruct lists
// Mikhail Nesterenko
// 5/01/00

//Samuel Hills version of Collection
// 2/06/21

#ifndef LIST_HPP_
#define LIST_HPP_

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:

        node() : next_(nullptr) {}

  // functions can be inlined
  T getData()const{return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

private:
  T data_;
  node<T> *next_;
};

template <typename T>
class Collection{
public:
        Collection() : head_(nullptr) {}   // default constructor

        void add( const T); // add function
        void remove(const T); // remove function

        template <typename U>
        friend bool equal(const Collection<U>&, const Collection<U>&);  // friend equal function

        T last() const;
        void print();                                      // print
private:
        node<T>* head_;              // points that points the the beginning of the linked list
//      node<T>* tail_;
};

// member functions for node ---------------------------
//
template <typename T>
node<T>* node<T>::getNext()const{
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}
//
// member functios for Collection---------------
template<typename T>
void Collection<T>::add(T const x) {

  node<T>* temp = new node<T>();    //  temp node to store next and new data
        temp->setData(x);
        temp->setNext(head_);             //setting next and data at the head of the list
        head_ = temp;


}


template<typename T>
void Collection<T>::remove(const T val) {
  node<T>* current;                    //  delcaring 2 nodes to store desired positions in list
  node<T>* previous;
        current = head_;
        while (head_->getData() == val) {
          head_ = head_->getNext();                // makes the head the first pos where it does not equal val
        }
        while (current->getNext() != nullptr) {
                if (current->getNext()->getData() == val) {
                  previous = current->getNext();               // makes previous point to the pos where data equals val
                  current->setNext(current->getNext()->getNext());       //sets current one past the pos where data equal val
                  delete previous;                                 // deletes previous freeing memory and occurence in list

                }
                else {
                  current = current->getNext();               // goes to next pos if val is not found

                }
        }

}
template<typename U>
bool equal(const Collection<U>& x, const Collection<U>& y){             //equal
        node<U>* nx = new node<U>();                    // declares 2 new nodes to point to the head of the 2 objects
        node<U>* ny = new node<U>();
        nx = x.head_;
        ny = y.head_;
        while (nx->getNext() != nullptr || ny->getNext() != nullptr) {                // loops through both linked list
                if (nx->getData() != ny->getData()) {
                  return false;                       // returns false if one entity is not equal to the other
                }
                nx = nx->getNext();                          //    gets next pos of linked list
                ny = ny->getNext();
        }

        return true;

}
template<typename T>
T Collection<T>::last()const {

  return head_->getData();     // returns the data of the head of the linked list which is the last entity entered

}

template<typename T>
void Collection<T>::print() {
  node<T>* prt = new node<T>();              // new node to points to the head of the linked list

        prt = head_;
        while (prt != nullptr) {                     //loops through prt intill end of list
          std::cout << prt->getData() << " ";      //out puts the data in the list
          prt = prt->getNext();                    // gets to the next pos of the list

        }

}


#endif // LIST_HPP_
