#include "DoublyLinkedList.h"

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  
  //add more
  DListNode * node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != NULL) {
      insertLast(node->obj);
      node = node->next;
    }
  }
}
// move constructor
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& dll)
{
  *this = dll;
  dll.~DoublyLinkedList();
}


// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  // use if (this != &dll)
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  
  //add more
  DListNode * node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != NULL) {
      insertLast(node->obj);
      node = node->next;
    }
  }
  return *this;
}


// move assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& dll)
{
  // use if (this != &dll)
  *this = dll;
  dll.~DoublyLinkedList();
  return *this;
}


// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{ 
    DListNode * node = new DListNode(newobj, &header, header.next);
    header.next->prev = node;
    header.next = node;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
    DListNode * node = new DListNode(newobj, trailer.prev, &trailer);
    trailer.prev->next = node;
    trailer.prev = node;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
    if(isEmpty())
      throw EmptyDLinkedListException("Empty");
    DListNode *temp = header.next;
    header.next->next->prev = &header;
    header.next = header.next->next;
    int obj = temp->obj;
    delete temp;
    return obj;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
    if(isEmpty())
      throw EmptyDLinkedListException("Empty");
    DListNode *temp = trailer.prev;
    trailer.prev->prev->next = &trailer;
    trailer.prev = trailer.prev->prev;
    int obj = temp->obj;
    delete temp;
    return obj;
}


// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    while(header.next != &trailer){
      removeFirst();
    }
}


// return the first object
int DoublyLinkedList::first() const
{ 
    return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
    return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
    DListNode * node = new DListNode(newobj, &p, p.next);
    p.next->prev = node;
    p.next = node;
}



// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
    DListNode * node = new DListNode(newobj, p.prev, &p);
    p.prev->next = node;
    p.prev = node;

}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode &p)
{
    if(p.next == &trailer)
      throw EmptyDLinkedListException("Out of Bounds");
    DListNode *temp = p.next;
    p.next->next->prev = &p;
    p.next = p.next->next;
    int obj = temp->obj;
    delete temp;
    return obj;
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode &p)
{
    if(p.prev == &header)
      throw EmptyDLinkedListException("Out of Bounds");
    DListNode *temp = p.prev;
    p.prev->prev->next = &p;
    p.prev = p.prev->prev;
    int obj = temp->obj;
    delete temp;
    return obj;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
    int sum = 0;
    DListNode *node = dll.getFirst();
    if(!dll.isEmpty()){
      while (node->next != NULL) {
        sum++;
        node = node->next;
      }
    }
    return sum;
}


// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  
  DListNode *node = dll.getFirst();
  if(!dll.isEmpty()){
    while (node->next != dll.getAfterLast()) {
      out << node->obj <<",";
      node = node->next;
    }
  out << node->obj;
  }
  return out;
}
