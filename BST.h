/*
   Cosimo Gonnelli

   This is the header for the tree class that manages a tree of categories
   This is the tree manager class that holds 3 types of question groups (categories)
*/

#include"category.h"


//tree node
class b_node
{
	public:
		b_node();
		~b_node();
		b_node(const category & toCopy);
		b_node *& goRight();
		b_node *& goLeft();
		void setRight(b_node * connect);
		void setLeft(b_node * connect);
		void display() const;
		int compare(const b_node * toCompare) const;
		category & getCategory();

	protected:
		b_node * right;
		b_node * left;
		category myCategory;
};

//BST manager class
class BST
{
	public:
		BST();
		~BST();
		int destroy();
		void displayAll() const;
		int insertCategory(category newCategory);
		int insertMulti(char * categoryToAdd, mChoice *& newQuestion);
		int insertTrueFalse(char * categoryToAdd, trueFalse *& newQuestion);
		int retrieve(int random, char * category, question *& found);
		
		//operator overloading implementations
		BST operator + (const category & toAdd);
		BST operator += (const category & toAdd);
		bool operator == (const category & toCompare);
		bool operator != (const category & toCompare);
		friend istream & operator >> (istream & in, category & toAdd); 
		friend ostream & operator << (ostream & out, const BST & source);

	protected:
		int destroy(b_node *& root);
		void displayAll(b_node * root) const;
		int insertCategory(b_node *& root, b_node * toAdd);
		int insertMulti(b_node *& root, char * categoryToAdd, mChoice *& toAdd);
		int insertTrueFalse(b_node *& root, char * categoryToAdd, trueFalse *& toAdd);
		int retrieve(b_node *& root, int random, char * category, question *& found);
		bool check(b_node * root, const category & toCheck);	
		bool check2(b_node * root, const category & toCheck);
		b_node * root; //pointer for the BST
};


