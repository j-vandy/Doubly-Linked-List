/*  @author Jackson Vanderheyden */
#include <iostream>
#include <stdexcept>
using namespace std;

/* node struct */
template <class T>
struct node {
	T data;
	node<T>* next;
	node<T>* previous;
};

/* Doubly Linked List Class */
template <class T>
class DoublyLinkedList {
private:
	node<T>* head;
	node<T>* tail;
	int size;
public:
	//constructor
	DoublyLinkedList<T>() {
		head = new node<T>;
		tail = new node<T>;
		size = 0;

		//create links between head and tail
		head->next = tail;
		tail->previous = head;
	}

	//returns size of the list
	int getSize() {
		return size;
	}

	/*adds data to the front of the list by
	by creating a new node that uses data 
	(function parameter) as its payload --
	function alters the new node, head node,
	and head's next node to correctly assort
	all of the nodes' next and previous variables*/
	void addFromHead(T data) {
		node<T>* n = new node<T>;
		n->data = data;
		n->next = head->next;
		n->previous = head;

		head->next->previous = n;
		head->next = n;

		size++;
	}

	/*adds data to the end of the list by
	by creating a new node that uses data
	(function parameter) as its payload --
	function alters the new node, tail node,
	and tail's previous node to correctly assort
	all of the nodes' next and previous variables*/
	void addFromTail(T data) {
		node<T>* n = new node<T>;
		n->data = data;
		n->next = tail;
		n->previous = tail->previous;

		tail->previous->next = n;
		tail->previous = n;

		size++;
	}

	/*removes the first node from the list
	-- removes head's next node as head is 
	a dummy node and changes the next and 
	previous variables to remove any references
	-- function will return null if size is zero*/
	T removeFromHead() {
		if (size == 0) return NULL;

		T output = head->next->data;
		head->next = head->next->next;
		head->next->previous = head;
		size--;
		return output;
	}

	/*removes the last node from the list
	-- removes tail's previous node as tail is
	a dummy node and changes the next and
	previous variables to remove any references
	-- function will return null if size is zero*/
	T removeFromTail() {
		if (size == 0) return NULL;

		T output = tail->previous->data;
		tail->previous = tail->previous->previous;
		tail->previous->next = tail;
		size--;
		return output;
	}

	/*removes data from list -- loops through the 
	list starting from the head node -- function
	returns true if found otherwise returns false*/
	bool remove(T data) {
		node<T>* current = head->next;
		while (current != tail) {
			if (current->data == data) {
				current->previous->next = current->next;
				current->next->previous = current->previous;
				size--;
				return true;
			}
			current = current->next;
		}
		return false;
	}

	/*loops through the list starting from the head 
	node -- function returns true if found otherwise
	returns false*/
	bool contains(T data) {
		node<T>* current = head->next;
		while (current != tail) {
			if (current->data == data) return true;
			current = current->next;
		}
		return false;
	}

	/*retrieves the data at the specified index
	-- loops through the list starting at the head
	node -- throws invalid argument "index out of 
	bounds" if index is out of the range of acceptable
	inputs*/
	T get(int index) {
		if (index >= size || index < 0) throw invalid_argument("Index out of bounds");

		node<T>* current = head->next;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}

		return current->data;
	}

	//creates visual of linked list
	void print() {
		if (size == 0) return;
		if (size == 1) {
			cout << head->next->data << endl;
			return;
		}
		node<T>* current = head->next;
		for (int i = 0; i < size; i++) {
			cout << current->data << " ";
			if (i != size - 1) cout << "<-> ";
			current = current->next;
		}
		cout << endl;
	}
};

int main() {
	//a doubly linked list with data type char
	DoublyLinkedList<char> CHAR;
	CHAR.addFromTail('B');
	CHAR.addFromTail('C');
	CHAR.addFromTail('D');
	CHAR.addFromTail('E');
	CHAR.addFromTail('F');
	CHAR.addFromHead('A');
	cout << "Doubly Linked List of Characters: " << endl;
	CHAR.print(); //A <-> B <-> C <-> D <-> E <-> F
	cout << "List size: " << CHAR.getSize() << endl; //6
	cout << "\nElement at index 0: " << CHAR.get(0) << endl; //A
	cout << "Contains B: " << CHAR.contains('B') << endl; //1 true
	cout << "Contains Z: " << CHAR.contains('Z') << endl; //0 false

	//removing nodes
	cout << "\n**Remove first element, last element, and 'D' element**" << endl;
	CHAR.removeFromHead();
	CHAR.removeFromTail();
	CHAR.remove('D');
	CHAR.print(); //B <-> C <-> E
	cout << "List size: " << CHAR.getSize() << endl; //3

	//a doubly linked list with data type int
	DoublyLinkedList<int> INT;
	INT.addFromHead(1);
	INT.addFromHead(2);
	INT.addFromHead(3);
	cout << "\n\nDoubly Linked List of Integers: " << endl;
	INT.print(); //3 <-> 2 <-> 1
	cout << "List size: " << CHAR.getSize() << endl; //3

	return 0;
}