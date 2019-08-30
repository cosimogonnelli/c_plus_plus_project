/*
   Cosimo Gonnelli 

   This is the header where the LLL of questions is mamaged. 
   Questions are organized according to their category name.
*/

#include"question.h"

#include<iostream>
#include<fstream>
#include<cstring>
#include<cctype>

using namespace std;

//LLL class node
class l_node
{
	public:
		l_node();
		~l_node();
		l_node(const question & toCopy);
		l_node(const mChoice & toCopy);
		l_node(const trueFalse & toCopy);
		question *& getQuestion();
		l_node *& goNext();
		void setNext(l_node *& connect);
		void display() const;

	protected:
		l_node * next;
		question * myQuestion; //node has a pointer of type question
};

//category class
class category
{
	public:
		category();
		category(const category & toCopy);
		category(char * name);
		~category();
		int compare(const category & toCompare) const;
		char * getName();
		int display() const;
		int insertQ(mChoice *& newQuestion);
		int insertTF(trueFalse *& newQuestion);
		int retrieveQ(int random, question *& found);

		//operator overloading
		category & operator = (const category & source);
		bool operator < (const category & toCompare);
		bool operator <= (const category & toCompare);
		bool operator > (const category & toCompare);
		bool operator >= (const category & toCompare);


	protected:
		int destroyLLL(l_node *& head); //delete the LLL
		int insertQ(l_node *& head, mChoice *& newQuestion);
		int insertTF(l_node *& head, trueFalse *& newQuestion);
		int retrieveQ(l_node *& head, int random, question *& found);
		int display(l_node * head) const;
		int countQuestion(l_node * head) const;

		char * name; //category of questions used to sort the BST
		l_node * head; //head of LLL of same questions
};

