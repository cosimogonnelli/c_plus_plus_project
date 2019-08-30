/*
   Cosimo Gonnelli

	This is the file where DLL and the d_node are implemented
 */

#include"DLL.h"

//--------------------------------DLL----------------------------------

//default constructor
DLL::DLL(): head(NULL), tail(NULL)
{}

//destructor as wrapper
DLL::~DLL()
{	
	destroy();
}

//wrapper
int DLL::destroy()
{
	if(!head) return 0;

	tail = NULL;

	return destroy(head);
}

//function call for deliting
int DLL::destroy(d_node *& head)
{
	if(!head) return 0;

	int count = destroy(head -> goNext()) +1;

	delete head;
	head = NULL;

	return count;
}

//insert to the quiz
int DLL::insert(question *& toAdd)
{
	if(!head)
	{
		head = new d_node(*toAdd);
		head -> goNext() = NULL;
		head -> goPrevious() = NULL;
		tail = head;
		return 1;
	}
	else
	{
		//insert at the beginning
		d_node * temp = head;
		head = new d_node(*toAdd);
		head -> goPrevious() = NULL;
		head -> goNext() = temp;
		temp -> goPrevious() = head;
		return 1;
	}
	/*
	//This code can be used to add at the end recursively without the else statement code
	
	   int count = insert(head -> goNext(), toAdd) +1;

	   if(head -> goNext())
	   {
	   head -> goNext() -> goPrevious() = head;
	   }

	   return count;
	 */
}

//wrapper remove a question
bool DLL::removeMatch(int match)
{
	if(!head) return false;

	return removeMatch(head, tail, match);
}

//TODO check if works
bool DLL::removeMatch(d_node *& head, d_node *& tail, int match)
{
	if(!head) return false;

	if((head -> getQuestion() -> getNumber()) == match)
	{
		if(head == tail)
		{
			tail = tail ->goPrevious();
			delete head;
			head = NULL;
			return true;
		}

		d_node * temp = head -> goNext();
		delete head;
		head = temp;
		temp -> goPrevious() = head;
		return true;
	}
	return removeMatch(head -> goNext(), tail, match);
}

//wrapper
int DLL::displayQuiz() const
{
	return displayQuiz(head);
}

int DLL::displayQuiz(d_node * head) const
{
	if(!head) return 0;

	head -> display();

	return displayQuiz(head -> goNext()) +1;
}


//-----------------------------d_node----------------------------------

//default constructor
d_node::d_node(): next(NULL), previous(NULL), myQuestion(NULL)
{}

//destructor
d_node::~d_node()
{
	delete myQuestion;
	myQuestion = NULL;
}

//make a copy of a question
d_node::d_node(const question & toCopy)
{
	next = NULL;
	previous = NULL;
	myQuestion = new question(toCopy);
}

//make a copy of a mChoice
d_node::d_node(const mChoice & toCopy)
{
	next = NULL;
	previous = NULL;
	myQuestion = new mChoice(toCopy);
}

//make a copy of a trueFalse
d_node::d_node(const trueFalse & toCopy)
{
	next = NULL;
	previous = NULL;
	myQuestion = new trueFalse(toCopy);
}

//getter for next
d_node *& d_node::goNext()
{
	return next;
}

//getter for previous
d_node *& d_node::goPrevious()
{
	return previous;
}

//set next
void d_node::setNext(d_node *& connect)
{
	next = connect;
}	

//set previous
void d_node::setPrevious(d_node *& connect)
{
	previous = connect;
}

//get question
question *& d_node::getQuestion()
{
	return myQuestion;
}

//display
void d_node::display() const
{
	myQuestion -> display();
}
