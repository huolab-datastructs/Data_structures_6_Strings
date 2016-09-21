#include "LIST.H"
template <class List_entry>
List<List_entry>::List()
/* 
Post: The List is initialized to be empty.
*/
{
   count = 0;
   current = first = last = NULL;
   current_position = -1;
}
 
template <class List_entry>
void List<List_entry>::clear()
/* 
Post: The List is cleared.
*/
{


   Node<List_entry> *p;

	while (first) {
		p = first->next;
		delete first;
		first = p;
	}

   count = 0;
   current = first = last = NULL;
   current_position = -1;
}
 
template <class List_entry>
int List<List_entry>::size() const
/* 
 
Post: The function returns the number of entries in the List.
 
*/

{
   return count;
}
 
template <class List_entry>
bool List<List_entry>::empty() const
/* 
 
Post: The function returns true or false according as the List is empty or not.
 
*/

{
   return count <= 0;
}
 
template <class List_entry>
bool List<List_entry>::full() const
/* 
 
Post: The function returns true or false according as the List is full or not.
 
*/

{
   return false;
}
 
template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/* 
 
Post: The action specified by function *visit
has been performed on every
entry of the List, beginning at position 0 and doing each in turn.
 
*/

{
   Node<List_entry> *to_visit = first;

   for ( ; to_visit; to_visit = to_visit->next)
      (*visit)(to_visit->entry);
}
 
template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/* 
 
Post: If the List is not full and 0 <= position <= n,
where n is the number of entries in the List,
the function succeeds:
Any entry formerly at
position and all later entries have their
position numbers increased by 1 and
x is inserted at position of the List.

 
Else:
the function fails with a diagnostic error code.
 
*/

{
   Node<List_entry> *new_node, *following, *preceding;

   if (position < 0 || position > count) return Error_code::range_error;

   if (position == 0) {
      if (count == 0) following = NULL;
      else {
         set_position(0);
         following = current;
      }
      preceding = NULL;
   }
   else {
      set_position(position - 1);
      preceding = current;
      following = preceding->next;
   }
   new_node = new Node<List_entry>(x, preceding, following);

   if (new_node == NULL) return overflow;
   if (preceding != NULL) preceding->next = new_node;
   if (following != NULL) following->back = new_node;
   current = new_node;
   current_position = position;

	if (new_node->back == NULL)
		first = new_node;
	if (new_node->next == NULL)
		last = new_node;

   count++;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/* 
 
Post: If the List is not full and 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is copied to x.
Otherwise the function fails with an error code of range_error.
 
*/

{
	if (position < 0 || position >= count) return Error_code::range_error;
   set_position(position);
   x = current->entry;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is replaced by x,
all other entries remain unchanged.
Otherwise the function fails with an error code of range_error.
 
*/

{
   if (position < 0 || position >= count) return range_error;
   set_position(position);
   current->entry = x;
   return success;
}
 
template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
/* 
 
Post: If 0 <= position < n,
where n is the number of entries in the List,
the function succeeds:
The entry in position is removed
from the List, and the entries in all later positions
have their position numbers decreased by 1.
The parameter x records a copy of
the entry formerly in position.
Otherwise the function fails with a diagnostic error code.
 
*/

{
   Node<List_entry> *old_node, *neighbor;
   if (count == 0) return fail;
   if (position < 0 || position >= count) return range_error;

   set_position(position);
   old_node = current;
   if (neighbor = current->back) neighbor->next = current->next;
   if (neighbor = current->next) {
      neighbor->back = current->back;
      current = neighbor;
   }

   else {
      current = current->back;
      current_position--;
   }

   x = old_node->entry;
   delete old_node;
   count--;

	if (current->next == NULL)
		last = current;
	if (current->back == NULL)
		first = current;

   return success;
}
 
template <class List_entry>
void List<List_entry>::set_position(int position) const
/*   
Pre:   position is a valid position in the List:
      0 <= position < count.
Post: The current Node pointer references the Node at position.
 */
{
	//checks if the current_position is to the left or the right of the position
	if (current_position <= position) {
		//if the position is in the right half or left half, (start from first or last)
		if (position >= count/2) {
			//if it's closer to the last or to the current
			if (count-position <= position-current_position) {
				current_position = count-1;
				current = last;
				for (;current_position != position;current_position--)
					current = current->back;
				//move left from last
			}
			else {

				for (;current_position != position;current_position++)
					current = current->next;
				//move to right from current
			}
		}
		//automatically knows the current will be closer
		//because it's to the left of position and in the left half
		else {
			for (;current_position != position;current_position++)
					current = current->next;
			//move to the right from current
		}
	}
	else { //to the right

		//if it's in the right half or not
		//automatically knows that it'll be closer because it's
		//to the right of it, and it's in the 2nd half
		if (position >= count/2) {
			for (;current_position != position;current_position--)
					current = current->back;
		}
		else {
			//checks if position is closer to current or the front
			if (current_position-position <= position) {
				for (;current_position != position;current_position--)
					current = current->back;
				//move to left from current
			}
			else {
				current_position = 0;
				current = first;
				for (;current_position != position;current_position++)
					current = current->next;
				//move to right from start
			}
			
		}
	}
}
 
//  ~List:  a destructor to clear the List.
/* 
 
Post: The List is empty: all entries have been removed.
 
*/

template <class List_entry>
List<List_entry>::~List()
{
   clear();
}
 
//  List:  a copy constructor
/* 
 
Post: The List is initialized to copy the parameter copy.
 
*/

template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
{
   count = copy.count;
   current_position = copy.current_position;
   Node<List_entry> *new_node, *old_node = copy.current;

   if (old_node == NULL) current = NULL;
   else {
      new_node = current = new Node<List_entry>(old_node->entry);
      while (old_node->next != NULL) {
         old_node = old_node->next;
         new_node->next = new Node<List_entry>(old_node->entry, new_node);
         new_node = new_node->next;
      }

      old_node = copy.current;
      new_node = current;
      while (old_node->back != NULL) {
         old_node = old_node->back;
         new_node->back = new Node<List_entry>(old_node->entry, NULL, new_node);
         new_node = new_node->back;
      }
   }
}
 
//  List:  overloaded assignment
/* 
 
Post: The List is assigned to copy a parameter
 
*/

template <class List_entry>
void List<List_entry>::operator =(const List<List_entry> &copy)
{
   List new_copy(copy);

   clear();
   count = new_copy.count;

   current_position = new_copy.current_position;
   current = new_copy.current;
   new_copy.count = 0;
   new_copy.current_position = 0;
   new_copy.current = NULL;
}
