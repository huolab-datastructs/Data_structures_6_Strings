#include "../../C/UTILITY.H"
template <class Node_entry>
struct Node {
//  data members
   Node_entry entry;
   Node<Node_entry> *next;
   Node<Node_entry> *back;
//  constructors
   Node();
   Node(Node_entry, Node<Node_entry> *link_back = NULL,
                    Node<Node_entry> *link_next = NULL);
};
 
template <class List_entry>
class List {
public:
 
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);
   ~List();
   List(const List<List_entry> &copy);
   void operator =(const List<List_entry> &copy);
 
//  Add specifications for methods of the list ADT.
//  Add methods to replace compiler generated defaults.
protected:
//  Data members for the doubly-linked list implementation follow:
   int count;
   mutable int current_position;
   mutable Node<List_entry> *current;

//  The auxiliary function to locate list positions follows:
   void set_position(int position) const;
	Node<List_entry> *first, *last;
};
 
template <class List_entry>
Node<List_entry>::Node()
{
   next = back = NULL;
}

template <class List_entry>
Node<List_entry>::Node (List_entry data, Node<List_entry> *link_back,
                                         Node<List_entry> *link_next)
{
   entry = data;
   back = link_back;
   next = link_next;
}
