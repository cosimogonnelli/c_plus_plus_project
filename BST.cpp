/*
   Cosimo Gonnelli

   The purpose of this program is to read in an external data files
   of questions. The data structure used for these questions is a BST.
   Each node of the tree will hold a LLL of questions of the same 
   type (inheritance, dynamic binding, or operator overloading).
   These questions will be randomly selected by the user to create a
   test. The data structure used for the test is a DLL.
 */

#include"BST.h"

//---------------------------------b_node----------------------------

//default constructor
b_node::b_node(): right(NULL), left(NULL), myCategory(NULL)
{}

//destructor
b_node::~b_node()
{
}

//make a copy of a category
b_node::b_node(const category & toCopy)
{
	right = NULL;	
	left = NULL;	
	myCategory = toCopy;
}

//getter for right
b_node *& b_node::goRight()
{
	return right;
}

//getter for left
b_node *& b_node::goLeft()
{
	return left;
}

//set right
void b_node::setRight(b_node * connect)
{
	right = connect;
}	

//set left
void b_node::setLeft(b_node * connect)
{
	left = connect;
}

//display category
void b_node::display() const
{
	myCategory.display();
}

//compare to decide if go left or right
int b_node::compare(const b_node * toCompare) const
{
	return myCategory.compare(toCompare -> myCategory);
}

//get category
category & b_node::getCategory()
{
	return myCategory;
}

//---------------------------------BST----------------------

//default constructor
 BST::BST(): root(NULL)
 {}

 //destructor as wrapper
 BST::~BST()
{
	destroy();
}

//destroy wrapper
int BST::destroy()
{
	if(!root) return 0;

	return destroy(root);
}

//delete the tree
int BST::destroy(b_node *& root)
{
	if(!root) return 0;

	int count = destroy(root -> goLeft()) + destroy(root -> goRight()) + 1;

	delete root;
	root = NULL;

	return count;
}

//wrapper to insert a category into the tree
int BST::insertCategory(category newCategory)
{
	//create a new node obj right into the function call
	return insertCategory(root, new b_node(newCategory));
}

//insert a category
int BST::insertCategory(b_node *& root, b_node * toAdd)
{
	if(!root)
	{
		root = toAdd; //connect the two nodes
		root -> setLeft(NULL);
		root -> setRight(NULL);
		return 1;
	}

	//check if go to the right
	if(toAdd -> compare(root) >= 0)
		insertCategory(root -> goRight(), toAdd);

	//go to the left
	else
		insertCategory(root -> goLeft(), toAdd);

	return 1;
}


//wrapper to insert a question
int BST::insertMulti(char * categoryToAdd, mChoice *& newQuestion)
{
	return insertMulti(root, categoryToAdd, newQuestion);
}

//insert m. cohice
int BST::insertMulti(b_node *& root, char * categoryToAdd,  mChoice *& toAdd)
{
	if(!root) return 0;

	if(strcmp(root -> getCategory().getName(), categoryToAdd) == 0)
	{
		root -> getCategory().insertQ(toAdd); 
	}
	return insertMulti(root -> goLeft(), categoryToAdd, toAdd) + 
			insertMulti(root -> goRight(), categoryToAdd, toAdd) +1;
}

//wrapper to insert a question
int BST::insertTrueFalse(char * categoryToAdd, trueFalse *& newQuestion)
{
	return insertTrueFalse(root, categoryToAdd, newQuestion);
}

//insert true false
int BST::insertTrueFalse(b_node *& root, char * categoryToAdd, trueFalse *& toAdd)
{
	if(!root) return 0;

	if(strcmp(root -> getCategory().getName(), categoryToAdd) == 0)
	{
		root -> getCategory().insertTF(toAdd); 
	}
	return insertTrueFalse(root -> goLeft(), categoryToAdd, toAdd) + 
			insertTrueFalse(root -> goRight(), categoryToAdd, toAdd) +1;
}

//wrapper fro retrieve
int BST::retrieve(int number, char * category, question *& found)
{
	return retrieve(root, number, category, found); 
}

//retrieve a question match and supplied to the DLL
int BST::retrieve(b_node *& root, int number, char * category,question *& found)
{
	if(!root) return 0;

	if(strcmp(root -> getCategory().getName(), category) == 0)
		return root -> getCategory().retrieveQ(number, found);

	return retrieve(root -> goLeft(), number, category, found) + 
			retrieve(root -> goRight(), number, category, found); 
}

//wrapper display
void BST::displayAll() const
{
	return displayAll(root);
}

//display
void BST::displayAll(b_node * root) const
{
	if(!root) return;

	displayAll(root -> goLeft());

	root -> display();

	displayAll(root -> goRight());
}

//addition operator overloading
BST BST::operator + (const category & toAdd)
{
	BST temp;
	temp.insertCategory(toAdd);

	return temp;
}

//addition assignment operator overloading
BST BST::operator += (const category & toAdd)
{
	insertCategory(toAdd);
	return * this;
}

//relational/equality operator overloading
bool BST::operator == (const category & toCompare)
{
	if(!root) return false;

	return check(root, toCompare);
}

//functin to check if match
bool BST::check(b_node * root, const category & toCheck)
{
	if(!root) return false;

	if(root -> getCategory().compare(toCheck) == 0)
		return true;

	return check(root -> goLeft(), toCheck) + check(root -> goRight(), toCheck);
}

//relational/equality operator overloading
bool BST::operator != (const category & toCompare)
{
	if(!root) return false;

	return check2(root, toCompare);
}

//functin to check if match
bool BST::check2(b_node * root, const category & toCheck)
{
	if(!root) return false;

	if(root -> getCategory().compare(toCheck) != 0)
		return true;

	return check2(root -> goLeft(), toCheck) + check2(root -> goRight(), toCheck);
}

//insertion operator overloading
istream & operator >> (istream & in, category & toAdd)
{
	in >> toAdd;
	return in;
}

//extraction operator overloading
ostream & operator << (ostream & out, const BST & source)
{
	source.displayAll();
	return out;
}



