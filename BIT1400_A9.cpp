#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

using namespace std;

#pragma warning(disable:4996)

//Structure for A9's question 2
const int MAX_NAME_LEN = 50;
struct student
{
	char name[MAX_NAME_LEN];
	unsigned int id;
	unsigned int age;
};

/*-------------------------------------------------------------------------------------------------------
										WHEEL OF FORTUNE START
-------------------------------------------------------------------------------------------------------*/

//Function that generates the clue only using & and *
char* wheelOfFortune2(char* inputArray)
{	
	//Variable to act as a pointer to the elements in clueArray2
	char arrayChar;
	
	//Creating a dynamic array to store the clue string
	char* clueArray2 = (char*)malloc(sizeof(char) * 200);

	//Pointer to the first element in clueArray2
	char* arrayIndex = clueArray2;


	if (clueArray2 != NULL)
	{
		//Loop to convert the characters in the array
		for (int i = 0; i < 200; i++)
		{
			arrayChar = *inputArray;

			if (arrayChar >= 'a' && arrayChar <= 'z')
			{
				arrayChar = toupper(arrayChar);
			}
			if (arrayChar == ' ')
			{
				arrayChar = '-';
			}
			if (arrayChar == 'A' || arrayChar == 'E' || arrayChar == 'I' || arrayChar == 'O' || arrayChar == 'U')
			{
				arrayChar = '_';
			}

			//Saving the converted character to the array
			*arrayIndex = arrayChar;

			//Moves to the next spot in the arrays
			inputArray++;
			arrayIndex++;
		}
		cout << endl;
	}
	//If the pointer is NULL, return 0;
	else
	{
		return 0;
	}

	return clueArray2;
}

//Function that generates the clue using []
char* wheelOfFortune(char * inputArray)
{
	//Array containing the converted string
	char* clueArray = (char*)malloc(sizeof(char) * 200);

	strcpy(clueArray, inputArray);
	
	//Checks to make sure the pointer to the array isn't NULL
	if (inputArray != NULL)
	{
		//Loop to convert the characters in the array
		for (int i = 0; i < 200; i++)
		{
			if (clueArray[i] >= 'a' && clueArray[i] <= 'z')
			{
				clueArray[i] = toupper(clueArray[i]);
			}
			if (clueArray[i] == ' ')
			{
				clueArray[i] = '-';
			}
			if (clueArray[i] == 'A' || clueArray[i] == 'E' || clueArray[i] == 'I' || clueArray[i] == 'O' || clueArray[i] == 'U')
			{
				clueArray[i] = '_';
			}
		}
	}
	//If the pointer to the array is NULL, just returns 0
	else
	{
		return 0;
	}

	return clueArray;
}



//Starting function for question 1 (Wheel of Fortune)
//Takes a user-inputted string and sends it to wheelOfFortune v1 and v2
//Compares and outputs the results
void wheelOfFortuneMain()
{
	//Dynamic arrays to store the string entered by the user, and the converted clue string
	char* a_inputString = (char*)malloc(sizeof(char) * 200);
	char* a_clueString = (char*)malloc(sizeof(char) * 200);

	//Array full of test strings, as instructed in A9 instructions
	char testString[3][200] =
	{ "Mashed potatoes are good", 
		"Already out of string ideas", 
		"This is a string"};
	
	//Character pointers to compare the string results from both Wheel of Fortune versions
	char* charPtr1;
	char* charPtr2;

	//Getting the user-inputted string
	cout << "Please input an answer string, to be converted to a hint string (Limited to 200 characters):" << endl;
	fgets(a_inputString, 200, stdin);
	cout << endl;

	//Using a trick I got from stackoverflow to get rid of the \n that fgets adds to the character array
	//link is https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
	//strcspm returns the location of the newline, then that locatiob in the array is set to 0
	a_inputString[strcspn(a_inputString, "\n")] = 0;

	//Call to the wheelOfFortune v1 function, saving the clue string to a_clueString
	a_clueString = wheelOfFortune(a_inputString);

	printf("The clue string is: %s\n\n", a_clueString);

	cout << "Various strings for additional tests:" << endl << endl;

	//Calling wheelOfFortune and wheelOfFortune2, sending test strings
	for (int i = 0; i < 3; i++)
	{		
		cout << "The test string being sent is:" << endl;
		cout << testString[i] << endl;
		
		//Modifying the test array using wheelOfFortune (using [])
		charPtr1 = wheelOfFortune(testString[i]);
		cout << endl;

		cout << "The clue string from wheelOfFortune is:" << endl;
		cout << charPtr1 << endl;

		//Modifying the test array using wheelOfFortune2 (only using & and *)
		//Sends the first element of every string to wheenOfFortune2
		charPtr2 = wheelOfFortune2(&testString[i][0]);

		cout << "The clue string from wheelOfFortune2 is:" << endl;
		cout << charPtr2 << endl; 
		cout << endl;

		assert(strcmp(charPtr1, charPtr2) == 0);
	}

	cout << "--------------------------------------------------------------------------------------" << endl;

	free(a_clueString);
	free(charPtr1);
	free(a_inputString);
	a_inputString = NULL;

}

/*-------------------------------------------------------------------------------------------------------
										 WHEEL OF FORTUNE END
-------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------
											NINJA EDIT START
-------------------------------------------------------------------------------------------------------*/

void ninjaParameter(student s)
{
	//Using sizeof() as per the instructions
	cout << "sizeof(s) as parameter is " << sizeof(s) << endl; //-> Gives me 60

	//Modifying the student ID according to instructions
	s.id = 11111;
}

void ninjaPointer(student* s)
{
	//Using sizeof() as per the instructions
	cout << "sizeof(s) as pointer is " << sizeof(s) << endl; //-> Gives me 4

	s->id = 22222;
}

void ninjaReference(student& s)
{
	//Using sizeof() as per the instructions
	cout << "sizeof(s) as reference is " << sizeof(s) << endl; //-> Gives me 60

	s.id = 33333;
}

void ninjaEditMain()
{
	//Creating a student, and setting values
	student s[3];

	s[0] = { "Bob Ross", 12345, 77 };
	s[1] = { "Mr Rogers", 54321, 77 };
	s[2] = { "Hello", 43110, 77 };

	//Pointer to the struct s
	student* structPointer;

	cout << endl;
	cout << "Start of the ninjaEdit question and functions." << endl;
	cout << endl;

	for (int i = 0; i < 3; i++)
	{		
		structPointer = &s[i];
		
		printf("Id before modifying: %i\n", s[i].id);
		cout << endl;

		//Passing the structure as a paramater
		ninjaParameter(s[i]);
		printf("Id after passing as parameter: %i\n", s[i].id);
		cout << endl;

		//Passing a pointer to the structure
		ninjaPointer(structPointer);
		printf("Id after passing a pointer: %i\n", s[i].id);
		cout << endl;

		//Passing the structure by reference
		ninjaReference(s[i]);
		printf("Id after passing by reference: %i\n", s[i].id);
		cout << endl;

	}
	cout << "--------------------------------------------------------------------------------------" << endl;
}

/*-------------------------------------------------------------------------------------------------------
											NINJA EDIT END
-------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------
											SIZE TEST START
-------------------------------------------------------------------------------------------------------*/

void sizeTest()
{
	cout << endl;
	cout << "Start of the sizeTest question and function" << endl;

	//Number of elements in the array
	const int NUM_FLOATS = 5;
	
	//Static array of floats, as per the instructions
	float A1[NUM_FLOATS] = { 10, 20, 30, 40, 50 };

	//Dynamic array of floats, same size as the static array
	float* A2 = (float*)malloc(sizeof(A1));

	//Dinamic array of float pointers
	float** A3 = (float**)malloc(sizeof(A1));

	//Setting the values for A2 and A3
	for (int i = 0; i < NUM_FLOATS; i++)
	{
		//Setting values according to instructions
		A2[i] = A1[i];
		A3[i] = &A1[i];

		//A3[i] prints out 0 because it contains an address, not a float
		printf("The values at index %i | A1: %3.0f | A2: %3.0f | A3: %3.0f\n", i, A1[i], A2[i], A3[i]);

	}

	cout << endl;

	//Outputting sizeof according to instructions
	printf("The size of A1 is %i\n", sizeof(A1)); //A1 is size 20
	printf("The size of A2 is %i\n", sizeof(A2)); //A2 is size 4
	printf("The size of A3 is %i\n", sizeof(A3)); //A3 is size 4

	free(A2);
	free(A3);
}

/*-------------------------------------------------------------------------------------------------------
											 SIZE TEST END
-------------------------------------------------------------------------------------------------------*/


/*
Sorry about all the random lines of code I added to my program
I like to try to format the output so everything looks nice and (relatively) organized
So any random cout << endl; or long outputs of dashes are just to organize the output a bit better
*/


int main()
{
	//Function to take user input, and convert it to a "clue" string 
	wheelOfFortuneMain();

	//Function to demonstrate and test different ways of modifying the elements of a structure
	ninjaEditMain();

	//Function that compares the size of various arrays, based on how the arrays are declared
	sizeTest();

	return 0;
}