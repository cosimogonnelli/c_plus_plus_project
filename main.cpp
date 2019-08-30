/*
   Cosimo Gonnelli

   The purpose of this program is to read in an external data files
   of questions. The data structure used for these questions is a BST.
   Each node of the tree will hold a LLL of questions of the same 
   type (inheritance, dynamic binding, and operator overloading).
   These questions will be randomly selected by the user to create a
   test. The data structure used for the test is a DLL.
 */

#include"BST.h"
#include"DLL.h"
#include<iostream>


using namespace std;


//prototypes
int userMenu(BST & myBST, DLL & myQuiz);
bool readIn(BST & myBST);
int makeQuizMenu(BST & myBST, DLL & myQuiz);
int selectQuestion(BST & myBST, DLL & myQuiz);
bool removeMatch(DLL & myQuiz);


//main
int main()
{
	DLL myQuiz; //Quiz obj.
	BST myBST; //Tree of questions obj.

	readIn(myBST); 
	userMenu(myBST, myQuiz);

	return 0;
}

//User menu interface
int userMenu(BST & myBST,DLL & myQuiz)
{
	int option;

	do{
		cout << "\n\n\t|~~~~~~~~~~~~~~~ Menu ~~~~~~~~~~~~~~|\n";
		cout << "\t|                                   |\n";    
		cout << "\t|1 - Make a quiz                    |\n";
		cout << "\t|2 - Display all	            |\n";
		cout << "\t|3 - Quit                           |\n";
		cout << "\t|                                   |\n";
		cout << "\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
		cout << "\nSelect one of the above options (from 1 to 3)\n>";
		cin >> option;
		cin.ignore(100,'\n');

		if(option == 1)
		{
			makeQuizMenu(myBST, myQuiz);
		}
		else if(option == 2)
		{
			myBST.displayAll();
		}    
		else if(option == 3)
		{    
			cout <<"\nBye Bye!\n\n";
		}    
		else
		{    
			cout << "\nYou entered an invalid number! Try again!\n";
		}
	}while(option != 3); //If not quit, we loop

	return option;
}

//read in an external data file 
bool readIn(BST & myBST)
{
	char categoryToAdd[SIZE];
	char qBody[SIZE];
	int type = 0;
	int qNumber = 0;
	char a1[SIZE];
	char a2[SIZE];
	char a3[SIZE];
	char a4[SIZE];
	bool a = true; //t/f question set to true by default

	ifstream inFile;
	inFile.open("category.txt");

	bool flag = false; //tell us when we read in a file

	if(inFile)
	{
		inFile.peek();
		while(!inFile.eof())
		{
			inFile.get(categoryToAdd, SIZE, '#');
			inFile.ignore(SIZE, '#');
			inFile.ignore(SIZE, '\n');

			category * addCategory;

			addCategory = new category(categoryToAdd);
			myBST.insertCategory(*addCategory);

			delete addCategory;

			inFile.peek();
		}
		inFile.close();
		inFile.clear();
		flag = true;
	}

	inFile.open("questions.txt");

	flag = false;

	if(inFile)
	{
		inFile.peek();
		while(!inFile.eof())
		{
			inFile.get(categoryToAdd, SIZE, '#');
			inFile.ignore(SIZE, '#');

			inFile >> type;
			inFile.ignore(SIZE, '#');

			inFile >> qNumber;
			inFile.ignore(SIZE, '#');

			inFile.get(qBody, SIZE, '#');
			inFile.ignore(SIZE, '#');

			//add multiple choice
			if(type == 1)
			{	
				inFile.get(a1, SIZE, '#');
				inFile.ignore(SIZE, '#');

				inFile.get(a2, SIZE, '#');
				inFile.ignore(SIZE, '#');

				inFile.get(a3, SIZE, '#');
				inFile.ignore(SIZE, '#');

				inFile.get(a4, SIZE, '#');
				inFile.ignore(SIZE, '\n');

				mChoice * addMquestion;
				addMquestion = new mChoice(categoryToAdd, qBody, type, qNumber, a1, a2, a3, a4);
				myBST.insertMulti(categoryToAdd, addMquestion);

				delete addMquestion;
			}

			//add true false
			if(type == 2)
			{
				inFile >> a;
				inFile.ignore(SIZE, '#');
				inFile.ignore(SIZE, '\n');

				trueFalse * addTrueFalse;
				addTrueFalse = new trueFalse(categoryToAdd, qBody, type, qNumber, a);
				myBST.insertTrueFalse(categoryToAdd, addTrueFalse);

				delete addTrueFalse; 
			}
		}
	}
	cout << "\n\nA list of categories and questions has beed loaded.\n\n";
	return flag;
}

//make a quiz menu
int makeQuizMenu(BST & myBST, DLL & myQuiz)
{
	int option;

	do{
		cout << "\n\n\t|~~~~~~~~~~~~~~~ Menu ~~~~~~~~~~~~~~|\n";
		cout << "\t|                                   |\n";    
		cout << "\t|1 - Select questions to add        |\n";
		cout << "\t|2 - Display all questions          |\n";
		cout << "\t|3 - Remove a question              |\n";
		cout << "\t|4 - Quit                           |\n";
		cout << "\t|                                   |\n";
		cout << "\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
		cout << "\nSelect one of the above options (from 1 to 4)\n>";
		cin >> option;
		cin.ignore(100,'\n');

		if(option == 1)
		{
			selectQuestion(myBST, myQuiz);
		}
		else if(option == 2)
		{
			int flag = myQuiz.displayQuiz();
			if(!flag)
				cout << "\nNothing to display\n";
		}    
		else if(option == 3)
		{    
			removeMatch(myQuiz);
		}
		else if(option == 4)
		{    
			return 1;
		}    
		else
		{    
			cout << "\nYou entered an invalid number! Try again!\n";
		}
	}while(option != 4); //If not quit, we loop

	return option;
}


//select questions to make the quiz TODO seg fault when inserting NOT inheritance
int selectQuestion(BST & myBST, DLL & myQuiz)
{
	int counter = 1;
	int quantity = 0;
	char cat[SIZE];
	char response;

	do{	
		cout <<"What is the " << counter 
			<<" category to add? (Type: 'inheritance' or 'dynamic binding' or 'operator overloading')\n>";
		cin.get(cat, SIZE, '\n');
		cin.ignore(SIZE, '\n');

		cout << "How many questions from " <<cat << " do you what to add? (from 1 to 10)\n>";
		cin >> quantity;
		cin.ignore(SIZE, '\n');

		if(quantity <=0 || quantity > 10)
			cout << "Nothing to add from this category" <<endl;
		else
			for(int i = 0; i < quantity; ++i)
			{
				int random = rand() % 10; //get a random number for a rundom question 

				question * found;
				myBST.retrieve(random, cat, found);

				found -> display(); //display the retrieve obj.

				myQuiz.insert(found); //insert the retrieve obj. into the quiz

				delete found;
			}
		counter +=1;

		if(counter < 4)
		{
			cout << "\nDo you want to insert another group of questions? (y or n)\n>";
			cin.get(response);
			cin.ignore(SIZE, '\n');

			//stopping condition for insertion
			if(toupper(response) == 'N')
				return 1;
		}

	}while(counter < 4); //repeat for each category

	return 1;
}

//remove a match in the Quiz
bool removeMatch(DLL & myQuiz)
{
	int question = 0;

	cout << "What is the number of the question you want to remove?\n>";
	cin >> question;
	cin.ignore(SIZE, '\n');

	bool flag = myQuiz.removeMatch(question);

	if(!flag)
		cout << "\nMatch not found\n";

	return flag;
}




