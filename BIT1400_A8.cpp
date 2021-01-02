#include <iostream>
#include <assert.h>

using namespace std;
#pragma warning(disable:4996)

// Note: the text file being read in is assumed to be
// TAB DELIMITED (tabs separate each field).

// You can add to these if you want to add additional courses
// (not strictly necessary)
#define BIT2400_FLAG  (1<<1)
#define ITEC5001_FLAG (1<<2)
#define BIT1400_FLAG  (1<<3)
#define ITEC2001_FLAG (1<<4)
#define ITEC2040_FLAG (1<<5)

// this struct is a text / big flag pair used in a_courseList
struct courseFlag
{
	const char* courseName;
	unsigned int flag;
};

// Modify the courses to be classes that YOUR students might
// register for.  Make sure you make a "bit flag" for each class.
// Please don't remove any of these classes.  Just add if you want.
const int NUM_COURSES = 5;
courseFlag a_courseList[NUM_COURSES] =
{ {"BIT2400", BIT2400_FLAG},
	{"ITEC5001", ITEC5001_FLAG},
	{"BIT1400", BIT1400_FLAG},
	{"ITEC2001", ITEC2001_FLAG},
	{"ITEC2040", ITEC2040_FLAG} };

const int MAX_NAME = 40;

// GIVEN: Don't modify
// the Student structure has a student name, ID
// and the courses that student has taken (stored as bits)
struct Student
{
	char a_name[MAX_NAME];
	unsigned int id;
	unsigned int cTakenFlags;
};

// GIVEN
// The set of all students read in from the text file.
struct StudentList
{
	Student* a_students;
	int numStudents;
};

////////////////////////////////////////////
// Function declarations so we don't worry about function order
int printCourses(Student stu, char* a_outTxt, int outTxtSize);
unsigned int getCourseBit(char* p_course);
StudentList readStudentFile(const char* fileName);
Student readStudentLine(char* textFileLine);
int printStudentInfo(Student stu, char* a_outTxt, int outTxtSize);
void printStudentListInfo(StudentList studentDB);

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
	//for (int i = 0; i < argc; i++)
	//{
		// If you want to just see what is in argv the line below outputs it.
		//cout << argv[i] << endl;
	//}
	// SOLUTION for A7
	char* textFile = (char*) "StudentInfo.txt";
	if (argc >= 2)
	{
		textFile = argv[1];
	}

	// Get the student information from the file
	StudentList studentDB = readStudentFile(textFile);

	// Print the student information to the screen (so you can
	// see that you did the file reading correctly)
	printStudentListInfo(studentDB);
}


// GIVEN:
// Converts a course name (char*) to the flag used to represent
// that course.
// Modify a_courseList with your courses if you add some.
// Any course name (eg "BIT1400" will be converted one of the 
// bit flags above OR will return 0.
// eg getCourseBit("BIT2400") == BIT2400_FLAG
unsigned int getCourseBit(char* p_course)
{
	for (int i = 0; i < NUM_COURSES; i++)
	{
		//If strcmp finds the strings to be identical to one of the class otions (returns 0 if identical)
		if (strcmp(p_course, a_courseList[i].courseName) == 0)
		{
			//Returns the bit flag matching the respective course
			return a_courseList[i].flag;
		}
	}
	return 0;
}

// TODO: MODIFY the function: Take a line
// of text from the textfile.  Read all relevant info for
// that student (form is: name<tab>ID<tab>Course1<tab>Course2<tab>....
// Unlike A7, we will record the courses using a series of bits (cTakenFlags)
Student readStudentLine(char* textFileLine)
{
	Student stu;

	// Fill in the function to read in the line of text.
	// Reading in the name and ID is provided.
	char* textStart = textFileLine;
	int lineLength = strlen(textFileLine);
	char* tabPos = strchr(textStart, '\t');

	// ---Get the student's name--
	// Replace the tab at tabPos with 0 so textStart
	// appears as just one small part of the line of text.
	tabPos[0] = 0;
	strcpy(stu.a_name, textStart);
	textStart = tabPos + 1;
	tabPos = strchr(textStart, '\t');

	//-- Get the student ID ----
	tabPos[0] = 0;
	stu.id = atoi(textStart);

	// Set up the start and end pointers for getting classes
	// completed. A class is ended with a \n or \t
	textStart = tabPos + 1;
	tabPos = strchr(textStart, '\t');

	// Set the flags to 0 (no courses)
	stu.cTakenFlags = 0;


	// READ IN ALL THE CLASSES TAKEN
	// Find each tab in the line.
	while ((tabPos != NULL)
		&& (tabPos <= textFileLine + lineLength))
	{
		tabPos[0] = 0;
		//TODO: Set stu's cTakenFlags variable to include the course
		// textStart should now be a single course name.
		// Use getCourseBit to get the bit and then set it
		// in cTakenFlags using a bit-wise OR
		// .......

		//Using |= to add the getCourseBit flag, as opposed to resetting cTakenFlags every time
		stu.cTakenFlags |= getCourseBit(textStart);

		// Get the next tab and update the start pos
		// tabPos could be the new line characters as well.

		textStart = tabPos + 1;
		tabPos = strchr(textStart, '\t');
	}
	// Finally, there can or is often a class at the end.
	char* nPos = strchr(textStart, '\n');
	if (nPos)
	{
		nPos[0] = 0;
	}
	// TODO:  set the cTakenFlags variable like you did in the while loop.
	// .......

	//Using |= to add the getCourseBit flag, as opposed to resetting cTakenFlags every time
	stu.cTakenFlags |= getCourseBit(textStart);

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

	FILE* filePtr;
	fopen_s(&filePtr, fileName, "r");
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
	assert(textPtr);

	int numStudentsStated = 0;
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
		stuList.numStudents = 0;
	}


	// You automatically get the next line) and make a student for each.
	// SOLUTION to A7
	while ((textPtr != NULL)
		&& (numStudentsStated > stuList.numStudents))
	{
		char* textPtr = fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);
		numLines++;
		assert(textPtr);
		Student stu = readStudentLine(txtBuffer);
		stuList.a_students[stuList.numStudents] = stu;
		stuList.numStudents++;
	}
	// One last sanity check: make sure the number of students stated
	// = the number read in.
	assert(stuList.numStudents == numStudentsStated);

	// You must close files that you've opened.
	fclose(filePtr);

	//Return the student list that you created.
	return stuList;
}


// TODO: Define printStudentListInfo so that all student
// information is output to the console window / command line
// This should be a really REALLY simple function using printStudentInfo
// a bunch of times.
void printStudentListInfo(StudentList studentDB)
{
	const int BUFFER_SIZE = 800;
	int charOutput = 0;

	//Allocating space for my array
	char* printArray = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	

	// call printStudentInfo for each student
	for (int i = 0; i < studentDB.numStudents; i++)
	{
		charOutput = printStudentInfo(studentDB.a_students[i], printArray, sizeof(char) * 60);
		// call printf with the character array to output that info to the screen.
		printf("Number of characters for %s: %i\n", studentDB.a_students[i].a_name, charOutput);
		printf("%s\n", printArray);
		cout << endl;
	}

	//I was unsure whether one of the evaluation criteria were to check to see if there were missing courses
	//So I didn't add any spare courses
	//I did notice, however, that there were some missing courses 
	//(i.e. Jean smith only having taken 1 of the course options, out of the 3 he took)
	
	// Free the dynamic character array you made
	free(printArray);

}

// TODO: simple method for printing all student info to a given string (a_outTxt)
// using sprintf
// That string can then be printed to the screen (using printf) or printed to a file (fprintf)
//.....we'll just print it to the screen to keep things simple.
// Returns: the number of characters written to a_outTxt excluding the \0 at the end
int printStudentInfo(Student stu, char* a_outTxt, int outTxtSize)
{

	//Used to move down the array as the program uses sprintf
	int printChar = 0;
	//Used to count the total number of characters added to the array
	int charOutput = 0;
	char* a_nextPos = a_outTxt;

	//Adding name and ID to the array
	printChar = sprintf(a_outTxt, "%s ", stu.a_name);
	a_nextPos = a_outTxt + printChar;
	charOutput += printChar;
	printChar = sprintf(a_nextPos, "%i ", stu.id);
	a_nextPos = a_nextPos + printChar;
	charOutput += printChar;

	//Call to printCourses to add the courses using the bitmasks
	charOutput += printCourses(stu, a_nextPos, outTxtSize);

	return charOutput;
}


// TODO: Output/print all the courses a given student has taken
// For example, if student s took BIT1400, BIT2400, and ITEC5001
// the output would be "BIT2400 ITEC5001 BIT1400"
// Also remember we have a_courseList...and that's the order the
// courses are in a_courseList if you didn't notice.
int printCourses(Student stu, char* a_outTxt, int outTxtSize)
{
	//Used to move dorn the array as the program uses sprintf
	int printChar = 0;
	//Used to count total characters outputted
	int charOutput = 0;

	char* a_nextPos = a_outTxt;
	
	
	for (int i = 0; i < NUM_COURSES; i++)
	{
		if ((stu.cTakenFlags & a_courseList[i].flag) == a_courseList[i].flag)
		{
			printChar = sprintf(a_nextPos, "%s ", a_courseList[i].courseName);
			a_nextPos = a_nextPos + printChar;
			charOutput += printChar;
		}
	}

	return charOutput;
}