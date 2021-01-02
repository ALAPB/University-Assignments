#include <iostream>
#include <assert.h>

using namespace std;

// Ignore this:  Just to help make compiling easier.
#pragma warning(disable:4996)

// Note: the text file being read in is assumed to be
// TAB DELIMITED (tabs separate each field).  If you get weird
// bugs if/when you edit the text file, it might be this problem

// Change if you want to offer more than 10 courses that a student can take.
const int MAX_COURSES_AVAILABLE = 10;

// Maximum length of a student name
const int MAX_NAME = 40;
const int MAX_COURSE_NAME = 10;

// GIVEN: Don't modify
// the Student structure has a student name, ID
// and the courses that student has taken (stored as bits)
struct Student
{
	char a_name[MAX_NAME];
	unsigned int id;
	// This is an array of character arrays(aa).....an array of course names
	// For student John Smith in StudentInfo.txt, aa_coursesTaken would be something like:
	// {"BIT1400", "BIT2400","ITEC2001", <unknown>, <unknown>.....} 
	// and numCoursesTaken would be 3.
	char aa_coursesTaken[MAX_COURSES_AVAILABLE][MAX_COURSE_NAME];
	unsigned int numCoursesTaken;
};

// GIVEN
// The set of all students read in from the text file.
struct StudentList
{
	// This is a pointer.  We'll see them soon BUT
	// it essentially represents an array of students
	// so a_students[2] gets the student at index 2.
	Student* a_students;
	int numStudents;
};


// TODO: Take a line of text from the textfile.  Read all relevant info for
// that student (form is: name<tab>ID<tab>Course1<tab>Course2<tab>....
// and put those values in a student structure you will return.
// NOTE: To store text you will need to copy text from textFileLine to
// the student's character arrays. Look at the assignment instructions
// for useful functions you can call.
Student readStudentLine(char* textFileLine)
{
	Student stu;
	
	// Fill in the function to read in the line of text.
	// Reading in the name and ID is provided.
	char* textStart = textFileLine;
	int lineLength = strlen(textFileLine);
	char* tabPos = strchr(textStart, '\t');

	// ---Get the student's name--
	//Save the name string into the name array

	// Replace the tab at tabPos with 0 so textStart
	// appears as just one small part of the line of text.
	tabPos[0] = 0;
	strcpy(stu.a_name, textStart);
	textStart = tabPos + 1;
	// Find the next tab.
	tabPos = strchr(textStart, '\t');

	//-- Get the student ID ----
	tabPos[0] = 0;
	// Notice that textStart is now just a string representing a number
	// since we replace the tab with a 0. atoi now works.
	stu.id = atoi(textStart);

	// Set up the start and end pointers for getting classes
	// completed. A class is ended with a \n or \t
	
	textStart = tabPos + 1;
	tabPos = strchr(textStart, '\t');

	//stu.numCoursesTaken = 0;

	// TODO: READ IN ALL THE CLASSES TAKEN
	// You will have to repeatedly update tabPos, textStart, and replace tabs with 0s
	// just like in the example above.  You'll want to call strcpy to copy the text
	// to each class in the Student structure: stu.aa_coursesTaken[0] is the first class
	// stu.aa_coursesTaken[1] is the next.
	
	//Counter for the loop
	int i = 0;	
	
	//Loop finds the number of courses that a person has taken, and saves the courses to the aa_coursesTaken array
	//Since tabPos is used, the array runs 1 time less than the amount of classes 
	//I.e. 3 classes, but 2 tabs, so the loop only runs twice until tabPos == NULL
	while(tabPos != NULL)
	{
		tabPos[0] = 0;
		strcpy(stu.aa_coursesTaken[i], textStart);
		textStart = tabPos + 1;
		tabPos = strchr(textStart, '\t');
		i++;
	}

	//strcopy to cover the last class (loop stops 1 class early due to it using tabPos)
	//Since there will be no tabpos for the last element 
	strcpy(stu.aa_coursesTaken[i], textStart);

	//Returns i + 1 due to the way i is used for the loop
	//(i starts at 0 to save data into array [0], so would return a number 1 too low)
	stu.numCoursesTaken = i + 1;

	return stu;
}

//TODO: Open file name
// readStudentFile takes a file name, opens the file, reads
// the lines of the file one by one.  A StudentList is created
// with this information and then returned at the end.
// The first line being read in is given as a comment to help
StudentList readStudentFile(const char* fileName)
{
	const int TXT_BUFF_SIZE = 200;
	char txtBuffer[TXT_BUFF_SIZE];

	StudentList stuList;
	stuList.a_students = NULL;
	stuList.numStudents = 0;

	// TODO: How to read in a text file
	// SOLUTION
	FILE* filePtr;
	// Replace the NULL with an fopen_s call.
	filePtr = fopen(fileName, "r");

	// If the filePtr is null then we know the file does not exist
	// Exit everything.
	if (filePtr == NULL)
	{
		printf("File to read in does not exist it seems.");
		return stuList;
	}
	unsigned int numLines = 0;

	// fgets reads text until newline. Repeat until the end of the file
	// Notice there are many ways one can do this. fscanf_s also works and is useful
	// to just get a sub-part of a line (readNumLine could use scanf_s)

	// Read the first line to determine the number of nodes
	char* textPtr = fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);
	numLines++;
	assert(textPtr); //*Aborts the program if the text file is empty*

	int numStudentsStated = 0;

	//Using \t for now, since there should be a tab after any entered terms
	const char* p_equalPos = strstr(txtBuffer, "=");

	if (p_equalPos == NULL)
	{
		return stuList;
	}
	else
	{
		// Make the array of students (top line of the file)
		// atoi explanation: takes a char * (text) and 
		// converts it to an integer.  Thus atoi("5") returns 5
		// HOWEVER: atoi("num = 5") causes an error.
		numStudentsStated = atoi(p_equalPos + 1);
		assert(numStudentsStated >= 0);
		stuList.a_students = new Student[numStudentsStated];
		stuList.numStudents = numStudentsStated; // WAS 0
	}

	// TODO: read each line of the file (just keep calling fgets.
	// You automatically get the next line) and make a student for each.
	// Notice you don't know how many times you need to call fgets. You
	// just know that **fgets returns NULL if there are no more lines to read.**
	// So what looping technique do you need?
	//
	// Also TODO: Presuming you make a Student stu each time through the loop
	// please add the following line: 
	//     cout << "Student structure is size: " << sizeof(stu) << endl;
	//
	// In a comment below this line, write what the cout statement returns

	//Cout statement returns 148

	// You can comment out this cout statement once  you've run it once.
	// MORAL: Student structures are really big. This is to motivate what we will 
	// do in the next assignment

	// One last sanity check: make sure the number of students stated
	// = the number read in.
	
	assert(stuList.numStudents == numStudentsStated);

	//Index for the while loop below
	int i = 0;

	//Saves the line in the text fille into a buffer
	fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);

	//This is while loop that runs until the pointer gets to the end of the file
	while (**fgets != NULL)
	{
		
		stuList.a_students[i] = readStudentLine(textPtr);
		//txtBuffer == array, TXT_BUFF_SIZE == max size of string to be read, filePtr is the pointer to the file being opened
		fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);

		//Break to stop the loop if it ran as many times as there are students
		if (i + 1 == stuList.numStudents)
		{
			break;
		}
		i++;
	}
	
	// You must close files that you've opened.
	fclose(filePtr);

	//Return the student list that you created.
	return stuList;
}


// TODO: Output all the student information to a character array
// using the function sprintf.  You need to make sure a_studentInfo is not NULL
// and you should probably test to ensure the number of chars output isn't greater
// than the size of a_destText.
// a_destText: the character buffer to write text to using sprinf
// destArraySize : the size of a_destText.
// Student stu:  The student structure you want to write out to a_destText
// RETURNS int: the number of characters output to a_destText
//
// Notice that sprintf works like printf.  The only difference is that instead of
// outputting to the screen, the text is put in a character array....which we will
// then output to the screen.   You just need practice using sprintf. :)
// Return the number of characters written to a_studentInfo.
// If anything goes wrong (like a_studentInfo is NULL) then return 0.
// Notice that this is what sprintf returns....but you may have to call sprintf
// a bunch of times since students have taken a different number of courses
// (you need to call sprintf in a loop).  To keep adding to the character array you 
// can write something like this:
// 
//  int numChars = sprintf(a_studentInfo, "%s", ....); // Write the class name in a_studentInfo
//  a_studentInfo = a_studentInfo + numChars; // Moves the position in the array numChars positions over.
//
//  Ex: int numChars = sprintf(a_studentInfo, "%s", "BIT1400");
//      a_studentInfo = a_studentInfo + numChars;
//     means numChars = 7 (BIT1400 has 7 characters) and 
//     a_studentInfo goes from 
//     [ | | | | | | | | | |...] to 
//      ^
//     [B|I|T|2|4|0|0| | | |...] 
//                    ^  where ^ is where the next text will go in the array.
//   ....we will deep dive into pointers very soon so if you are a bit confused, we'll make
//   sure it makes sense soon.  For now, you can consider this to be magic. 
int toBufferStudentInfo(char* a_studentInfo, unsigned int destArraySize, Student stu)
{
	int totalOut = 0;
	
	if (a_studentInfo == NULL)
	{
		return 0;
	}
	
	totalOut = sprintf(a_studentInfo, "%s ", stu.a_name);
	a_studentInfo = a_studentInfo + totalOut;
	totalOut = sprintf(a_studentInfo, "%i ", stu.id);
	a_studentInfo = a_studentInfo + totalOut;

	for (int i = 0; i < stu.numCoursesTaken; i++)
	{
		totalOut = sprintf(a_studentInfo, "%s ", stu.aa_coursesTaken[i]);
		a_studentInfo = a_studentInfo + totalOut;
	}

	if (sizeof(a_studentInfo) > destArraySize)
	{
		return 0;
	}

	return totalOut;
}

// TODO: MODIFY printStudentListInfo so that all student
// information is output to the console window / command line
// This should be a relatively simple function provided you wrote
// toBufferStudentInfo.  
void printStudentListInfo(StudentList studentDB)
{
	// Some really big array of characters (the size is somewhat arbitrary.  I just
	// don't want to run out of space)
	const int STUDENT_INFO_BUFF_SIZE = MAX_COURSES_AVAILABLE * MAX_COURSE_NAME * 2;
	char a_studentInfo[STUDENT_INFO_BUFF_SIZE];
	
	// SOLUTION
	for (int i = 0; i < studentDB.numStudents; i++)
	{
		//TODO: get the student information in a_studentInfo using a function you made
		toBufferStudentInfo(a_studentInfo, STUDENT_INFO_BUFF_SIZE, studentDB.a_students[i]);
		printf("%s\n", a_studentInfo);
	}
}

// main method that takes in command line input.
// To run: 
//    1) find your .exe file that you will create using the command prompt
//       ...that is (in Windows): on the bottom left where it says "Type here to search"
//       type run.  In the run app, type cmd.  This is the command prompt.
//       Next, type cd .. to back up one directory, cd <directory> to go
//       into a directory, and dir to list everything in the directory.
//       There are a LOT of online resources on how to use cmd if you want to be fancier.
//       Linux users and Mac users: you have a similar command line with slightly
//       different commands.
//       The TAB button attempts to complete what you are writing.  Give it a try.
//    2) Make sure the text file you will read in in the same directory as the exe.
//    3) Run your program with extra arguments.  These words will be
//       stored in argv and you will have argc of these words.
//       Feel free to play around with this style of main method.
//       It comes up far more often than you might expect.
// For your code, make the second argument the name of the text file being  read in.
// Thus you might call "A7_StudentInfo_BIT1400_F19 studentData.txt"
int main(int argc, char** argv)
{
	// TODO: get the file name from the input parameters
	char* textFile = argv[1];
	
	// Get the student information from the file
	StudentList studentDB = readStudentFile(textFile);

	// Print the student information to the screen (so you can
	// see that you did the file reading correctly)
	printStudentListInfo(studentDB);
}