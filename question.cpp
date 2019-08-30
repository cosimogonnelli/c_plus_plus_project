/*
   Cosimo Gonnelli

	This is the file where question and type of questions are implemented.
	The question type are multiple choice and true false
 */

#include"question.h"


//---------------------------------Question-------------------------------
//default constructor
question::question(): categ(NULL), qBody(NULL), type(0), qNumber(0)
{}

//destructor 
question::~question()
{
	destroy();
}

//delete function
void question::destroy()
{
	if(categ)
	{
		delete [] categ;
		categ = NULL;
	}
	if(qBody)
	{
		delete [] qBody;
		qBody = NULL;
	}
}

//constructor with args
question::question(char * c, char * q, int ty, int qN)
{
	categ = new char[strlen(c) +1];
	strcpy(categ, c);

	qBody = new char[strlen(q) +1];
	strcpy(qBody, q);

	type = ty;

	qNumber = qN;
}
//copy constructor 
question::question(const question & toCopy): categ(NULL), qBody(NULL), type(0), qNumber(0)
{
	*this = toCopy;

	/*
	//this code is replaced by the operator overloading
	categ = new char[strlen(toCopy.categ) +1];
	strcpy(categ, toCopy.categ);

	qBody = new char[strlen(toCopy.qBody) +1];
	strcpy(qBody, toCopy.qBody);

	type = toCopy.type;

	qNumber = toCopy.qNumber;
	*/
}

//assigment operator overloading
question & question::operator = (const question & toCopy)
{
	if(this == & toCopy) return *this;

	destroy(); //delete memory

	if(toCopy.categ)
	{
		categ = new char[strlen(toCopy.categ) +1];
		strcpy(categ, toCopy.categ);
	}
	else
		categ = NULL;

	if(toCopy.qBody)
	{
		qBody = new char[strlen(toCopy.qBody) +1];
		strcpy(qBody, toCopy.qBody);
	}
	else
		qBody = NULL;
	
	if(toCopy.type)
		type = toCopy.type;

	if(toCopy.qNumber)
		qNumber = toCopy.qNumber;
	
	return *this;
}

int question::getNumber()
{ 
	return qNumber;
}

//display base class info
void question::display() const
{
	cout <<"\nCategory: " <<categ <<endl;

	cout <<"\nQuestion N: " <<qNumber <<endl;

	cout << qBody <<endl;

}

//----------------------------mChoice---------------------------------
		
//default constructor
mChoice::mChoice(): answer1(NULL),answer2(NULL),answer3(NULL),answer4(NULL)
{}

//wrapper destructor
mChoice::~mChoice()
{
	destroyM();
}

//deleting function
void mChoice::destroyM()
{
	if(answer1)
	{
		delete [] answer1;
		answer1 = NULL;
	}
	if(answer2)
	{
		delete [] answer2;
		answer2 = NULL;
	}
	if(answer3)
	{
		delete [] answer3;
		answer3 = NULL;
	}
	if(answer4)
	{
		delete [] answer4;
		answer4 = NULL;
	}
}
	
//constructor with arguments
mChoice::mChoice(char * c, char * q, int ty, int qN, char * a1, char * a2, char * a3, char * a4)
{
	categ = new char[strlen(c) +1];
	strcpy(categ, c);

	qBody = new char[strlen(q) +1];
	strcpy(qBody, q);

	type = ty;

	qNumber = qN;

	answer1 = new char[strlen(a1) +1];
	strcpy(answer1, a1);

	answer2 = new char[strlen(a2) +1];
	strcpy(answer2, a2);

	answer3 = new char[strlen(a3) +1];
	strcpy(answer3, a3);

	answer4 = new char[strlen(a4) +1];
	strcpy(answer4, a4);
}

//copy constructor
mChoice::mChoice(const mChoice & toCopy): question(toCopy)
{
	answer1 = new char[strlen(toCopy.answer1) +1];
	strcpy(answer1, toCopy.answer1);

	answer2 = new char[strlen(toCopy.answer2) +1];
	strcpy(answer2, toCopy.answer2);

	answer3 = new char[strlen(toCopy.answer3) +1];
	strcpy(answer3, toCopy.answer3);

	answer4 = new char[strlen(toCopy.answer4) +1];
	strcpy(answer4, toCopy.answer4);
}

//diplay mutliple choice question
void mChoice::display() const
{	
	cout <<"\nCategory: " <<categ <<endl;

	cout <<"\nQuestion N: " <<qNumber <<endl;

	cout << qBody <<endl;

	cout <<"\nAnswer 1: " << answer1 <<endl;

	cout <<"\nAnswer 2: " << answer1 <<endl;

	cout <<"\nAnswer 3: " << answer3 <<endl;

	cout <<"\nAnswer 4: " << answer4 <<endl;
}

//----------------------------true false---------------------------------

//constructor
trueFalse::trueFalse(): answer(true)
{}

//constructor with args.
trueFalse::trueFalse(char * c, char * q, int ty, int qN, bool a)
{
	categ = new char[strlen(c) +1];
	strcpy(categ, c);

	qBody = new char[strlen(q) +1];
	strcpy(qBody, q);

	type = ty;

	qNumber = qN;

	answer = a;
}

//copy constructor
trueFalse::trueFalse(const trueFalse & toCopy): question(toCopy)
{
	answer = toCopy.answer;
}

//display
void trueFalse::display() const
{	cout <<"\nCategory: " <<categ <<endl;

	cout <<"\nQuestion N: " <<qNumber <<endl;

	cout << qBody <<endl;

	if(answer)
		cout <<"\nAnswer: True "<<endl;
	else
		cout <<"\nAnswer: False "<<endl;
}
