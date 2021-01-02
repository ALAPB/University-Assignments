// BIT1400_A4.cpp : Grade Calculator
//
// FIRST: make a new (blank) project in visual studio and include this file as the only source file in the project
// Rename the project to be A4_CalcGrade_<YourName>_BIT1400F19
// where YourName is your first initial and last name.
//
// When you have finished the assignment, submit JUST the current cpp file to cuLearn


/***************************************************
 * UPDATE: We may not get to structures until Monday.
 * Thus you do NOT need to use a structure for the solution.
 * However, no structures mean that your functions will have a LOT of parameters
 * in some cases.
 ****************************************************/


 // MOTIVATION
 // Notice that CULearn will be effectively useless at calculating your final grade
 // Thus your job is to write functions that determine it (and thus you don't need to email
 // and ask at the end of term. :))
 // Notice you can have far more assignments and quizzes than the number counted 
 // (or fewer if you're lazy and don't do your work....not recommended)
 // thus you need both the number of assignments or quizzes and the number of those that 
 // are counted.
 //
 // Your job is to make arrays and structures (or combinations of both) that can store 
 // your grades and then calculate your quiz grade, assignment grade, and exam grades
 // then use these to calculate your final percentage grade. Finally, based on the
 // percentage grade you should output your letter grade.
 // You NEED to do this work with functions and minimize the amount of code duplication
 // Thus your functions should be re-usable for quizzes, exams, and assignments.
 // You may only have one midterm (and we won't drop it), but you could use the same structure
 // as you use for the quizzes.
 // Look for TODO comments in the code for other things you need to implement or edit.


 /*
 Part 1: pseudocode
 Write the series of steps you plan to take in order to calculate your final grade.
 You should output your final percent in the course in a useful message (not just a number)
 You should then output what that percentage grade is as a letter grade.
 Your pseudocode can be almost any format you like provided in accurately conveys how you plan to implement
 the code. Here is one possible format you can use
 1. ..............
   a .............
	 i. ..........
	 ii...........
   b .............
   c .............
 2................
 ..........

 */

#include <iostream>
#include "assert.h"
using namespace std;

// These are useful constants (you can change or add to)
// Notice they are all caps by convention to indicate the numbers can't
// be changed by the program (just by you)
const int ASSIGN_GRADES_SIZE = 10;
const int ASSIGN_GRADES_COUNTED = 8;
const int QUIZ_GRADES_SIZE = 18;
const int QUIZ_GRADES_COUNTED = 15;
const double EXAM1_PCT = 0.25;
const double EXAM2_PCT = 0.30;
const double QUIZ_PCT = 15;
const double ASSIGN_PCT = 30;

// TODO: (OPTIONAL) Define a struct that holds all data needed to calculate a type of grade (assignment, quizzes, etc)
// This struct is NOT needed but good practice if you want to try making a struct.

// TODO:
// Returns the index of the smallest value in the array(gradeArray) of size aSize
// int* gradeArray is essentially the same as int gradeArray[]
// If aSize is < 1 then return -1 (a bad index)
int minIdx(int* gradeArray, int aSize)
{
	//minPos used to return the location of the smallest number in the array
	int minPos = 0;
	//smallestNum used to compare and save the smallest variable
	int smallestNum = gradeArray[0];

	//As per the instructions
	if (aSize < 1)
	{
		return -1;
	}

	//Loop to find the smallest value in the array
	for (int i = 0; i < aSize; i++)
	{
		if (gradeArray[i] < smallestNum)
		{
			smallestNum = gradeArray[i];
			minPos = i;
		}
	}

	//Returns the index of the smallest value in the array	
	return minPos;
}

// TODO: more advanced function.
// shiftMinN will use minIdx to find the smallest number in array
// gradeArray (notice I could have used "int * gradeArray" for the same parameter)
// numGrades is the size of the grade array while numCounted is the number of grades
// we are counting.
// The key idea: what if you swapped the last element in the array with smallest
// value??  {2, 3, 1, 4, 5} would be {2, 3, 5, 4, 1}.  What if I then pretend I have
// one less value (so size = 4).  I get {2, 3, 5, 4}.  Now what if I find the min
// index of that new array and swap again? {4, 3, 5}.
// When finished shifting over the minimum numCounted values, return the size of
// the array (the returned values should be equal to numCounted).
int shiftMinN(int gradeArray[], int numGrades, int numCounted)
{
	assert(numGrades >= numCounted);
	int newSize;
	//Variable used to store the index for the minimum position
	int minPos;
	//Temp variable is used for swapping the min value with the last value in the array
	int temp = 0;
	//numDropped is the amount of quizzes/assignments dropped
	int numDropped = numGrades - numCounted;
	
	//Loop runs as many times as grades are dropped (numDropped)
	//For every run through the loop, the urrent newest value is moved to the last spot in the array
	for (int i = 0; i <= numDropped; i++) 
	{
		//Finds the location of the smallest value in the array, and returns an index location for the array
		minPos = minIdx(gradeArray, numGrades);

		//Switches the smallest value with the last value in the array
		temp = gradeArray[minPos];
		gradeArray[minPos] = gradeArray[numGrades];
		gradeArray[numGrades] = temp;

		//Reduces the size of the array looks at
		//"Deletes" the smallest value by kicking the last spot out of the array
		numGrades -= 1;
	}

	newSize = numGrades;
	return newSize;
}

//Initially was supposed to get an array to find the overall average
//Changed because i find the average for every evaluation type in typeAvg
double average(double quizAvg, double assignAvg, int test1Res, int test2Res)
{
	//finalAvg used to return the accumulated % after it's calculated
	double finalAvg;

	finalAvg = quizAvg + assignAvg + (test1Res  * EXAM1_PCT) + (test2Res * EXAM2_PCT);
	
	return finalAvg;
}

//Calculates the average grade for an evaluation type (quizzes, assignments)
double typeAvg(int gradeArray[], double weight, int counted, int outOf)
{
	//Average is sued to return the average calculated
	double average = 0;
	//Sum used to add up the quiz results, then divide by 24
	double sum = 0;

	//Adds all the numbers in the array together
	for (int i = 0; i < counted; i++)
	{
		sum += (gradeArray[i]);
	}

	average = sum / counted;
	average /= outOf;
	average *= weight;

	return average;
}

//Function provides a letter grade, from A+ to F, based on the final grade and returns it to main()
const char* calcLetterGrade(int pctGrade)
{
	//If statement to return every grade between A+ and F (Including the + and - variants)
	if (90 <= pctGrade && pctGrade <= 100)
	{
		return "A+";
	}
	if (85 <= pctGrade && pctGrade <= 89)
	{
		return "A";
	}
	if (80 <= pctGrade && pctGrade <= 84)
	{
		return "A-";
	}
	if (77 <= pctGrade && pctGrade <= 79)
	{
		return "B+";
	}
	if (73 <= pctGrade && pctGrade <= 76)
	{
		return "B";
	}
	if (70 <= pctGrade && pctGrade <= 72)
	{
		return "B-";
	}
	if (67 <= pctGrade && pctGrade <= 69)
	{
		return "C+";
	}
	if (63 <= pctGrade && pctGrade <= 66)
	{
		return "C";
	}
	if (60 <= pctGrade && pctGrade <= 62)
	{
		return "C-";
	}
	if (57 <= pctGrade && pctGrade <= 59)
	{
		return "D+";
	}
	if (53 <= pctGrade && pctGrade <= 56)
	{
		return "D";
	}
	if (50 <= pctGrade && pctGrade <= 52)
	{
		return "D-";
	}
	if (0 <= pctGrade && pctGrade <= 49)
	{
		return "F";
	}

}


//Apologies for the fact that main() is bulky
//It was more convenient to get the input in main() and then send it to the other functions
//Most of the bulk is for loops that ensure the inputted grades are valid
int main()
{
	//Variable used to display the accumulated grade so far

	struct gradeStruct
	{
		//Weight is the weight of the evaluation type on the grade
		double weight;
		//Amount is the total amount of evaluations done for any given type
		int amount;
		//Counted is the amount of evaluations kept for the average calculation
		int counted;
		//Out of is the # of possible points an evaluation can get (i.e. assignments are graded out of 100)
		int outOf;
		//The final average for an evaluation type
		double average;
	} quizzes, assignments, exam1, exam2;

	//Quiz values for gradeStruct
	quizzes.weight = QUIZ_PCT;
	quizzes.counted = QUIZ_GRADES_COUNTED;
	quizzes.amount = QUIZ_GRADES_SIZE;
	quizzes.outOf = 24;

	//Assignment values for gradeStruct
	assignments.weight = ASSIGN_PCT;
	assignments.counted = ASSIGN_GRADES_COUNTED;
	assignments.amount = ASSIGN_GRADES_SIZE;
	assignments.outOf = 100;

	//Exam1 values for gradeStruct
	exam1.weight = EXAM1_PCT;
	exam1.counted = 1;
	exam1.amount = 1;
	exam1.outOf = 100;
	exam1.average = 0;

	//Exam2 values for gradeStruct
	exam2.weight = EXAM2_PCT;
	exam2.counted = 1;
	exam2.amount = 1;
	exam2.outOf = 100;
	exam2.average = 0;
	
	//Arrays containing the grades for quizzes and assignments
	int quizArray[QUIZ_GRADES_SIZE]; // = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24 ,24, 6, 6, 24 };

	int assignArray[ASSIGN_GRADES_SIZE]; // = { 70, 57, 80, 80, 90, 70, 65, 80, 90, 80 };

	//Runs through the quiz array to get input for every value in the array
	for(int i = 0; i < QUIZ_GRADES_SIZE; i++)
	{
		cout << "Enter your quiz grade (/24) for quiz " << i + 1 << " out of " << QUIZ_GRADES_SIZE << endl;
		
		//Loop to make sure the input is valid
		while (quizArray[i] < 0 || quizArray[i] > quizzes.outOf)
		{
			cin >> quizArray[i];

				if (quizArray[i] < 0 || quizArray[i] > quizzes.outOf)
				{
					cout << "Invalid number. Please make sure it is between 0 and 24" << endl;
				}

		}
	
	}

	//Runs through the assignment array to get input for every value in the array
	for (int i = 0; i < ASSIGN_GRADES_SIZE; i++)
	{
		cout << "Enter your assignment grade (/100) for assignment " << i + 1 << " out of " << ASSIGN_GRADES_SIZE << endl;

		//Loop to make sure the input is valid
		while (assignArray[i] < 0 || assignArray[i] > assignments.outOf)
		{
			cin >> assignArray[i];

				if (assignArray[i] < 0 || assignArray[i] > assignments.outOf)
				{
					cout << "Invalid number. Please make sure it is between 0 and 100" << endl;
				}

		}

	}

	cout << "Please enter your grade for the first test (/100)" << endl;
	cin >> exam1.average;

	//Loop to make sure the input is valid
	while (exam1.average < 0 || exam1.average > exam1.outOf)
	{
		if (exam1.average < 0 || exam1.average > exam1.outOf)
		{
			cout << "Invalid number. Please make sure it is between 0 and 100" << endl;
		}

		cin >> exam1.average;
	}

	cout << "Please enter your grade for the second test (/100)" << endl;
	cin >> exam2.average;

	//Loop to make sure the input is valid 
	while (exam2.average < 0 || exam2.average > exam2.outOf)
	{
		if (exam2.average < 0 || exam2.average > exam2.outOf)
		{
			cout << "Invalid number. Please make sure it is between 0 and 100" << endl;
		}

		cin >> exam2.average;
	}


	//Call to shiftMinN to get rid of lowest quiz grades
	shiftMinN(quizArray, quizzes.amount - 1, quizzes.counted);
	//Call to shiftMinN to get rid of lowest assignment grades
	shiftMinN(assignArray, assignments.amount - 1, assignments.counted);
	//Calculating the average for the quizzes
	quizzes.average = typeAvg(quizArray, quizzes.weight, quizzes.counted, quizzes.outOf);
	//Calculating the average for the assignments
	assignments.average = typeAvg(assignArray, assignments.weight, assignments.counted, assignments.outOf);

	//Calculating the overall average for the final grade
	float accumGrade = average(quizzes.average, assignments.average, exam1.average, exam2.average);

	//Prints the final value 
	printf("Your accumulated grade in the course is %.0f\n", accumGrade);

	//TODO: get the letter grade based on finalGrade
	char* letterGrade = (char*) calcLetterGrade(accumGrade);
	//letterGrade = (char*)calcLetterGrade(finalGrade);

	// TODO: Now output your letter grade
	printf("Your final letter grade in the course will be %s\n", letterGrade);
	return 0;
}
