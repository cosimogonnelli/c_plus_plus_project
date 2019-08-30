/*
   Cosimo Gonnelli

   This is the headed for the actual quiz that will be crested getting
   questions from the BST. The questions will be selected randomly 
   according to the category name and a random number.
 */

#include"question.h"


//DLL node that has a pointer to a question
class d_node
{
	public:
		d_node();
		~d_node();
		d_node(const question & toCopy);
		d_node(const mChoice & toCopy);
		d_node(const trueFalse & toCopy);
		d_node *& goNext();
		d_node *& goPrevious();
		void setNext(d_node *& connect);
		void setPrevious(d_node *& connect);
		question *& getQuestion();
		void display() const;

	protected:
		d_node * next;
		d_node * previous;
		question * myQuestion;
};

//Quiz class
class DLL
{
	public:
		DLL();
		~DLL();
		int destroy();
		int insert(question *& toAdd);
		bool removeMatch(int match);
		int displayQuiz() const;

	protected:
		int destroy(d_node *& head);
		int displayQuiz(d_node * head) const;
		bool removeMatch(d_node *& head, d_node *& tail, int match);
		d_node * head;
		d_node * tail;
};


