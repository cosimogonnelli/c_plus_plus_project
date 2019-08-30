/*
   Cosimo Gonnelli

   This is  the header for the question base class and derived classes:
   multiple choice and true false
 */

#ifndef QUESTION
#define QUESTION

#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>
#include<cstdlib>

using namespace std;

const int SIZE = 500;

//base class question for the pool of questions of the LLL in the BST
class question
{
	public:
	question();
	virtual ~question();
	void destroy();
	question(char * c, char * q, int ty, int qN);
	question(const question & toCopy);
	int getNumber();
	virtual void display() const;
	
	//operator overloading
	question & operator = (const question & toCopy);

	protected:
	char * categ;
	char * qBody;
	int type; //m.choice or t/f
	int qNumber;
};

//multiple choice is a question
class mChoice: public question
{
	public:
		mChoice();
		~mChoice();
		void destroyM();
		mChoice(char * c, char * q, int ty, int qN, char * a1, char * a2, char * a3, char * a4);
		mChoice(const mChoice & toCopy);
		void display() const;

	protected:
		char * answer1;
		char * answer2;
		char * answer3;
		char * answer4;
};

//true flase is a question
class trueFalse: public question
{
	public:
		trueFalse();
		trueFalse(char * c, char * q, int ty, int qN, bool a);
		trueFalse(const trueFalse & toCopy);
		void display() const;
		
	protected:
		bool answer;
};

#endif 
