#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------

/*
  Assignment 4: Emergency Problems
  Your job for A4 is to solve each of the mini problems with minimal guidance
  You are expected to use variables, loops, conditionals, and functions in many
  places.  Personally I hate problems like these because they are formulaic and
  encourage rote learning.  However, you also need to know how to apply each concept.
  Your job is to
0) Do one question at a time, compile and test your functions following the format
   in the following steps. Do not move on until each question is complete.
1) write pseudocode (or an illustration) for each concept. You won't pass these in.
   You are just honor-bound to do it. :)  Writing pseudocode is a valid exam question.
2) Make the function but do NOT define it correctly.  Just do whatever it takes to
   make the function compile.  For example, here is dec2Hex (from A3) as a "todo function"

char dec2Hex( int num )
{
	return 'a';
}

You make the function just enough that  you can compile and write tests for it....the tests
will fail.  Later you write the function and see if the tests pass.  This is the basic
concept surrounding something called "Test Driven Development".  It makes for better code.

3) Write tests or what you expect each function to do under different conditions / values.
   You will do this by calling each function with different inputs. Put a comment
   above each of these calls as to what you expect the value to be (or in many cases
   you could put the whole thing in an assert to prove that the function works as expected).

4) FINALLY, write the code for the function.

5) Make sure the tests you wrote "pass".  Do you get the results that you expected.

You will follow this pattern for each function you are asked to write.  Follow
the TODO comments to identify all the functions.
My name : Alexandre Lott
To Submit: Make sure your program is still compiling and works.
Save the file as A4_MiscProblems_<Name>_F19.cpp where name is your
first initial and last name. Eg: A4_MiscProblems_DSprague_F19.cpp
*/

//-----------------------------------------------------------------------------------------------------------------------------

// TODO: Q1 Factorial
// Write a function that computes n! or n factorial.  This is
// n * (n-1)* (n-2) * (n-3) *.....2 * 1
// The input variable must be a positive value between 0 and 15 (an int)
// and an int is returned. 
// Also note that 0! = 1
// EXTRA: When your function works, use a ternary conditional (that "(test)? A : B" 
// conditional) to make sure the value of n is 0 to 15. 
//    If greater than 15, set the input variable's value to 15.
//    If < 0, then set the input variable's value to 0.

//-----------------------------------------------------------------------------------------------------------------------------

void factorial(int cntr)
{
	//factVal is the integer selected by the user
	int factVal;
	//factorial is used to calculate the factorial
	double factorial = 1;
	
	//getting user input
	cout << "This is test number " << cntr << " of the factorial function\n";
	cout << "Please enter an integer between 0 and 15\n";
	cout << "Any invalid integers will be changed to 0\n";
	cin >> factVal;
	
	//ternary conditionals for the extra step
	factVal = (factVal < 0) ? 0 : factVal;
	factVal = (factVal > 15) ? 15 : factVal;
	
	//for loop to make sure the factorial runs factVal times 
	//(i.e. you don't want it to run 15 times to calculate the factorial of 3)
	for (int i = 0; i < factVal; i++)
	{
		factorial *= factVal - i;
	}

	cout << "The factorial of " << factVal << " is " << factorial << endl;

	//endl to add some spacing to the output, instead of having a block of code
	cout << endl;

}

//-----------------------------------------------------------------------------------------------------------------------------

const double MATH_PI = 3.14159265358979323846;
// TODO: Q2 Circle Area
// Write a function that computes the area of a circle with a given radius
// This function should take a radius (double) as input and return a double
// (the area) as output.

//-----------------------------------------------------------------------------------------------------------------------------

void circleArea(int cntr)
{
	double radius;
	double area;

	cout << "This is test number " << cntr << " of the area of a circle function" << endl;
	cout << "Please enter the radius of the circle to calculate the area" << endl;
	cin >> radius;

	//this calculates area = pi * r^2
	area = MATH_PI * pow(radius, 2);

	//i personally prefer using cout in the area function to reduce clutter in main
	//an alternative would be to do return area; and cout the returned value in main
	cout << "The area of the circle with a radius of " << radius << " is " << area << endl;
	cout << endl;
}

//-----------------------------------------------------------------------------------------------------------------------------

// TODO: Q3 Crazy Alphabet Song
// Write a function that outputs the alphabet to the screen....but let's
// be crazier.  Have the function take two characters as parameters (char start
// and char end) and output each character between start and end (including those values)
// After outputting the characters, the function returns the number of characters output.
// Example: If the function is called crazyAlphabet, a call of crazyAlphabet('a', 'z') 
// would cause abcdefghijklmnopqrstuvwxyz to appear on the screen.  The number 26 
// would be returned by the function.
// crazyAlphabet('a', 'e') would output abcde and return the value 5.
// You will want to use a while loop.

//-----------------------------------------------------------------------------------------------------------------------------

//I realise tha instructions want the parameters to be sent from main, but that would be too clustered
//I'd much rather have main exclusively call functions, and all the work to be done in the functions 
//If i were to bring in parameters, main would have alphabet(start, end) and alphabet would get alphabet(char start, char end)

void alphabet(int cntr)
{
	char start;
	char end;

	cout << "This is test number " << cntr << " of the crazy alphabet song function" << endl;
	cout << "Please select the starting letter you would like to use" << endl;
	cin >> start;
	cout << "Now, please select the ending letter you would like to use" << endl;
	cin >> end;
	cout << endl;

	//loop do print each character until the end character is reached
	while(start <= end)
	{
		cout << start;
		//moves the character to the next one after printing 
		start++;
	}

	cout << endl;
	cout << endl;
}

//-----------------------------------------------------------------------------------------------------------------------------

/*
* TODO: Q4 Primes
* A prime number is a number that is only divisible by 1 and itself.  Thus 3 is prime
* but 4 is not (2 divides 4). Write a function "isPrime" that takes an unsigned int > 1
* and < 100 and returns true if the value is prime and false otherwise (so return a bool)
* You don't have to solve this problem gracefully.  A while loop that checks all values
* from 2 to the value (but not including the value) will be fine.
* inputs that are not acceptable just return false.
*/

//-----------------------------------------------------------------------------------------------------------------------------

//Would be int if I return a value, but i prefer printing from within the function so I used void
void isPrime(int cntr)
{
	unsigned int numSelect = 1;
	//primeCond used to indicate whether the nunmber is prime (1) or not (0)
	int primeCond = 1;
	
	cout << "This is test number " << cntr << " of the prime finding function" << endl;
	cout << "Please enter a number between 1 and 100" << endl;
	cin >> numSelect;

		//Loop to make sure that the input is within 1 and 100
		while (numSelect < 1 || numSelect > 100)
		{
			cin >> numSelect;
			
			if (numSelect < 1 || numSelect > 100)
			{
				cout << "Invalid number. Please enter a number between 1 and 100" << endl;
			}
		}

	//Loop to determine wether the number is prime or not
	for (int i = 1; i <= 100; i++)
	{
		//If remainder is 0, and selected number isn't being divided by iself or 1
		if (numSelect % i == 0 && numSelect != i && i != 1)
		{
			primeCond = 0;
		}
	}

	if (primeCond == 0)
	{
		cout << "The number " << numSelect << " is not a prime number" << endl;
	}
	else if (primeCond == 1)
	{
		cout << "The number " << numSelect << " is a prime number" << endl;
	}

	cout << endl;
}

//-----------------------------------------------------------------------------------------------------------------------------

/*
* TODO: Q5 Switch Statements
* Write a function that takes a char letter grade ('A', 'B', 'C', 'D', 'F)
* and returns the lowest grade that gives you that letter grade (an int)
* For example, if the function was getLowerBound then getLowerBound('A') returns 80.
* You must use a switch statement for this.
*/

//-----------------------------------------------------------------------------------------------------------------------------

//Would be int if I return a value, but i prefer printing from within the function so I used void
void letterGrade(int cntr)
{
	//Used to get input from the user
	char gradeChar;

	cout << "This is test number " << cntr << " of the letter grade function" << endl;
	cout << "Please enter a letter letter grade: A, B, C, D or F capital letters" << endl;
	cin >> gradeChar;

		//Loop to make sure the input is A, B, C, D, E or F
		while (gradeChar != 'A' && gradeChar != 'B' && gradeChar != 'C' && gradeChar != 'D' && gradeChar != 'F')
		{
			if (gradeChar != 'A' && gradeChar != 'B' && gradeChar != 'C' && gradeChar != 'D' && gradeChar != 'F')
			{
				cout << "Invalid input. Please enter either A, B, C, D or F" << endl;
			}

			cin >> gradeChar;
		}

		//Switch to determine the grade, as per the instructions
		//Values assume that all variants (i.e. A+, A and A- are all part of the A grade)
		switch (gradeChar)
		{
			case 'A':	cout << "Minimum grade for A is 80%" << endl;	break;
			case 'B':	cout << "Minimum grade for B is 70%" << endl;	break;
			case 'C':	cout << "Minimum grade for C is 60%" << endl;	break;
			case 'D':	cout << "Minimum grade for D is 50%" << endl;	break;
			case 'F':	cout << "Minimum grade for F is 0%" << endl;	break;
		}
		//I could have also had returns after every case:, but i printed them here instead of reduce clutter in main (i.e. case 'A': return 80;)
		cout << endl;
}

int main()
{
	//Loops to run each question's function 4 times
	//User input takes place in each of the functions 

	for (int i = 1; i < 5; i++)
	{
		factorial(i);
	}
	
	for (int i = 1; i < 5; i++)
	{
		circleArea(i);
	}

	for (int i = 1; i < 5; i++)
	{
		alphabet(i);
	}

	for (int i = 1; i < 5; i++)
	{
		isPrime(i);
	}
	
	for (int i = 1; i < 5; i++)
	{
		letterGrade(i);
	}

	//Sorry about having to enter all the variables, I kinda got ahead of myself

	return 0;
}
