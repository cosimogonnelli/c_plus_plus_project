/*
   Cosimo Gonnelli

   This files has the LLL node and the category methods
 */

#include"category.h"


//---------------------------------l_node-------------------------------

//default constructor
l_node::l_node(): next(NULL), myQuestion(NULL)
{}

//destructor
l_node::~l_node()
{
	if(myQuestion)
	{
		delete myQuestion;
		myQuestion = NULL;
	}
}

//make a copy of question
l_node::l_node(const question & toCopy)
{
	next = NULL;
	myQuestion = new question(toCopy);
}

//make a copy of multiple choice
l_node::l_node(const mChoice & toCopy)
{
	next = NULL;
	myQuestion = new mChoice(toCopy);
}

//make a copy of t/f 
l_node::l_node(const trueFalse & toCopy)
{
	next = NULL;
	myQuestion = new trueFalse(toCopy);
}

//getter for right
l_node *& l_node::goNext()
{
	return next;
}

//set next 
void l_node::setNext(l_node *& connect)
{
	next = connect;
}	

question *& l_node::getQuestion()
{
	return myQuestion;
}

//display a question
void l_node::display() const
{
	myQuestion -> display();
}

//-------------------------------category-----------------------------

//default constructor
category::category(): name(NULL)
{}

//copy constructor
category::category(const category & toCopy): name(NULL)
{
	*this = toCopy;

	//this code is replaced using operator overloaded
	//name = new char[strlen(toCopy.name) +1];
	//strcpy(name, toCopy.name);
}

//constructor with arguments
category::category(char * type)
{
	name = new char[strlen(type) +1];
	strcpy(name, type);
}

//destructor
category::~category()
{
	if(name)
	{
		delete [] name;
		name = NULL;
	}

	if(head)
		destroyLLL(head);
}

//delete the LLL of every category
int category::destroyLLL(l_node *& head)
{
	if(!head) return 0;

	destroyLLL(head -> goNext());

	delete head;
	head = NULL;
	return 1;
}

//assignment operator overloading
category & category::operator = (const category & source)
{
	if(this == &source) return *this;

	if(name)
		delete [] name;

	if(source.name)
	{
		name = new char[strlen(source.name) +1];
		strcpy(name, source.name);
	}
	else
		name = NULL;

	return *this;
}

//less than operator overloading
bool category::operator < (const category & toCompare)
{
	if(!head) return true;
	if(!toCompare.head) return false;

	//compare the number of questions in the categories
	if(countQuestion(head) < toCompare.countQuestion(toCompare.head))
		return true;

	return false;
}

//less than/equal operator overloading
bool category::operator <= (const category & toCompare)
{
	if(!head && !toCompare.head) return true;
	if(!head) return true;
	if(!toCompare.head) return false;

	//compare the number of questions in the categories
	if(countQuestion(head) <= toCompare.countQuestion(toCompare.head))
		return true;

	return false;
}

//greater than operator overloading
bool category::operator > (const category & toCompare)
{
	if(!head) return false;
	if(!toCompare.head) return true;

	//compare the number of questions in the categories
	if(countQuestion(head) > toCompare.countQuestion(toCompare.head))
		return true;

	return false;
}

//greater than/equal operator overloading
bool category::operator >= (const category & toCompare)
{
	if(!head && !toCompare.head) return true;
	if(!head) return false;
	if(!toCompare.head) return true;

	//compare the number of questions in the categories
	if(countQuestion(head) >= toCompare.countQuestion(toCompare.head))
		return true;

	return false;
}

//count questions in a category
int category::countQuestion(l_node * head) const
{
	if(!head) return 0;

	return countQuestion(head -> goNext()) +1;
}

//compare new category name with tree category name
int category::compare(const category & toCompare) const
{
	return strcmp(name, toCompare.name);
}

//get name
char * category::getName()
{
	return name;
}

//wrapper, add to the LLL
int category::insertQ(mChoice *& newQuestion)
{
	return insertQ(head, newQuestion);
}

//add a question to the LLL
int category::insertQ(l_node *& head, mChoice *& newQuestion)
{
	if(!head)
	{
		head = new l_node(*newQuestion);
		head -> goNext() = NULL;
		return 1;
	}
	else
	{
		//add at the beginning
		l_node * temp = new l_node(*newQuestion);
		temp -> goNext() = head;
		head = temp;
		return 1;
	}
}

//wrapper, add to the LLL
int category::insertTF(trueFalse *& newQuestion)
{
	return insertTF(head, newQuestion);
}

//add a question to the LLL
int category::insertTF(l_node *& head, trueFalse *& newQuestion)
{
	if(!head)
	{
		head = new l_node(*newQuestion);
		head -> goNext() = NULL;
		return 1;
	}
	else
	{
		//add at the beginning
		l_node * temp = new l_node(*newQuestion);
		temp -> goNext() = head;
		head = temp;
		return 1;
	}
}

//wrapper for retrieve
int category::retrieveQ(int random, question *& found)
{
	return retrieveQ(head, random, found);
}

//retrieve a question
int category::retrieveQ(l_node *& head, int random, question *& found)
{
	if(!head) return 0;

	if(head -> getQuestion() -> getNumber() == random) 
	{
		//--------------------dynamic casting---------------------
		mChoice * pM;
		trueFalse * pTF;
	
		pM = dynamic_cast < mChoice * > (head -> getQuestion());
		if(pM)
			found = new mChoice(*pM);

		pTF = dynamic_cast < trueFalse * > (head -> getQuestion());
		if(pTF)
			found = new trueFalse(*pTF);
		//---------------------------------------------------------
		return 1;
	}
	return retrieveQ(head -> goNext(), random, found);
}

//wrapper for display
int category::display() const
{
	cout <<"Category: " <<endl;
	cout <<name <<endl <<endl;

	return display(head);
}

//display LLL
int category::display(l_node * head) const
{
	if(!head) return 0;

	head -> display();

	return display(head -> goNext()) +1;
}


