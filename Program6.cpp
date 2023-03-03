/////////////////////////////////////////////////////////////////////////////////////////////////////
//Name: Eddie G. Pineda																			   //
//Date: 12/01/2022																				   //
//Program Statement: Design a simple linked list class with only two member functions and a        //
//                   default constructor using an appropiate definition of listNode.               //
//                   Member functions: void add(double x);                                         //
//                                     boolean isMember(double x);                                 //
//                   Default constructor: LinkedList();                                            //
//                   The add function adds a new node containing x to the front of the list, the   //
//                   isMember function tests to see if the list contains a node with the value x.  //
//                   Extra details: Add a copy constructor                                         //
//                                  Add a print member function                                    //
//                                  Add a recursive method to check for list membership            //
//                                  Add a function to remove an item from the list, and a          //
//                                  destructor: void remove(double x);                             //
//                                              ~LinkedList();                                     //
//                                  Add a member function to reverse the list: void reverse();     //
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

struct node { //Node class
	node(double val1, node* next1 = NULL) { //Overloaded constructor
		nodeVal = val1; //Sets nodeVal to val1
		nextN = next1; //Sets nextN to next1
	}
	double nodeVal; //Stores the value of a node
	node* nextN; //Next node
};

class LinkedList {
	public:
		LinkedList(); //Default constructor
		LinkedList(LinkedList&); //Copy constructor
		~LinkedList(); //Destructor
		void add(double); //Add function adds a new node containing x to the front of the list
		bool isMember(double); //isMember function tests to see if the list contains a node with the value x
		void print(); //Print function
		bool recursiveCheck(node*, double); //Recursive member function to check for list members
		void remove(double); //Removes an itemfrom the list
		void reverse(); //Reverses the order of the list

	private:
		static node* copyList(node*); //Function used to create a copy

	protected:
			node* head; //Head of the list pointer
};

LinkedList::LinkedList() { //Default constructor
	head = NULL; //Sets the head of the list to NULL
}

node * LinkedList::copyList(node* linkList) { //Function to create a copy
	if (linkList == NULL) { //If the list is empty
		return NULL;
	}
	else {
		node* tCopy = copyList(linkList->nextN); //Create a tail copy of the list through recursion
		return new node(linkList->nodeVal, tCopy); //Return an overloaded node to form the copy list
	}
}

LinkedList::LinkedList(LinkedList& temp) { //Copy constructor
	head = copyList(temp.head);
}

LinkedList::~LinkedList() { //Destructor
	node* temp = head; //Temp node to start at the head

	while (temp != NULL) { //While loop to parse until the head is empty
		node* erase = temp; //Pointer to keep track of the node to be erased
		temp = temp->nextN; //Move onto the next node
		delete erase; //Erases the past node
	}
}

void LinkedList::add(double x) {
	if (head == NULL) { //If the head node is empty
		head = new node(x); //Sets the head to the x value
	}
	else {
		head = new node(x, head); //If the head is not empty, it invokes the overloaded constructor for nodes
	}
}

bool LinkedList::isMember(double checkVal) {
	node* temp = head; //Sets a temp node to start at the head

	while (temp != NULL) { //While loop to parse until a NULL value is encountered
		if (temp->nodeVal == checkVal) { //Checks if the current value for temp is equal to the wanted value
			return true;
		}
		temp = temp->nextN; //Moves onto the next value
	}

	return false; //If no values are found and the while loop comes to an end, the function returns false
}

void LinkedList::print() { //Print function definition
	node* temp = head; //Creates a tenporary node that starts at the head of the list

	while (temp != NULL) { //While loop to parse through each node in the list
		cout << temp->nodeVal << " "; //Prints out the current value
		temp = temp->nextN; //Moves onto the next node
	}
	cout << endl;
}

bool LinkedList::recursiveCheck(node* linkList, double x) { //Uses recursion to check if a value is part of the list
	if (linkList == NULL) { //If the list is empty or at its end
		return false;
	}
	if (linkList->nodeVal == x) { //If the current node value is equal to the desired value
		return true;
	}
	else {
		return recursiveCheck(linkList->nextN, x); //Use recursion to move onto the next value and check again
	}
}

void LinkedList::remove(double x) { //Remove function definition
	node *temp, *pastN = NULL; //Create a temporary node and a node to store previously looked at values

	if (head == NULL) { //If the list is empty, stop the function
		return;
	}

	if (head->nodeVal == x) { //If the current value in the head of the list is the desired value
		temp = head; //Set temp equal to the current head
		head = head->nextN; //Set the head equal to the next node
		delete temp; //Delete temp with the desired value
	}
	else {
		temp = head; //Set temp equal to the current head
		while (temp != NULL && temp->nodeVal != x) { //While loop to parse until the desired value is found
			pastN = temp; // Set pastN equal to the current temporary node
			temp = temp->nextN; //Set the current temporary node to the next node
		}

		if (temp) { //Failsafe in case the while loop does not work
			pastN->nextN = temp->nextN; //Set pastN to the next node of temp
			delete temp; //Delete the current temp node
		}
	}
}

void LinkedList::reverse() { //Reverse function definition
	node* temp = head; //Sets temp to equal to the head of the list
	node* prev = NULL, *next = NULL; //Creates prev and next nodes

	while (temp != NULL) { //While loop to parse through the entire list
		next = temp->nextN; //Sets next to the next node of temp
		temp->nextN = prev; //Sets the next node of temp to prev, which is NULL in the first loop
		prev = temp; //Sets prev to the current temp
		temp = next; //Sets temp to the value of next
	}
	head = prev; //Sets the list equal to the reversed order
}

int main() {

	LinkedList testList; //Creates a liinkedlist
	double usrInpt; //Stores an input from the user

	testList.add(1.3); //linkedList member
	testList.add(6.5); //linkedList member
	testList.add(3.2); //linkedList member
	testList.add(4.8); //linkedList member

	LinkedList testList2(testList); //Creates a copy of the first list

	cout << "Please enter a value to check for membership in the list:" << endl;
	cin >> usrInpt; //Store chosen input value from user

	cout << "isMember function check: " << endl;
	if (testList.isMember(usrInpt)) { //If loop to check if the chosen value is a member of the list
		cout << "The value is a member of the list.\n" << endl;
	}
	else {
		cout << "The value is not a member of the list.\n" << endl;
	}

	cout << "Recursion method check: " << endl;
	if (testList.isMember(usrInpt)) { //If loop to check if the chosen value is a member of the list
		cout << "The value is a member of the list.\n" << endl;
	}
	else {
		cout << "The value is not a member of the list.\n" << endl;
	}

	cout << "Please enter a value to check for membership in the second list:" << endl;
	cin >> usrInpt; //Store chosen input value from user

	if (testList2.isMember(usrInpt)) { //If loop to check if the chosen value is a member of the list
		cout << "The value is a member of the list.\n" << endl;
	}
	else {
		cout << "The value is not a member of the list.\n" << endl;
	}

	cout << "Values in list 1: ";
	testList.print(); //Prints the values in testList
	cout << "Values in copy list: ";
	testList2.print(); //Prints the values in testList2

	cout << endl << "Removing the fourth value from the list." << endl;
	testList.remove(6.5); //Removes 6.5 from the list
	cout << "New list: ";
	testList.print(); //Prints the new testList

	testList.reverse(); //Reverses the order of the list
	testList.print(); //Prints out the reversed list

	return 0;
}