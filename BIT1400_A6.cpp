
#include <iostream>
#include <assert.h>

/*************************************
* DURING BREAK ASSIGNMENT:
* Everyone becomes worried about how many
* assignments we drop in the course.  I'm
* making this one an extra dropped assignment.
* Thus although I guaranteed 1 dropped assignment,
* if you do this one, you would drop another (or this one)
* Thus if you didn't do the work at the start of term, here's
* your chance to fix the problem
**************************************/

// BIT1400 Assignment 6: Chinese Animal Signs
// In this assignment we will look at a problem that is served well by the use of functions
// modular arithmetic (remainders or  the % symbol in C), and structures: 
// determining your Chinese Zodiac Animal.  Thus this assignments acts
// as a good practice for what we've already gone over before the break.
// https://en.wikipedia.org/wiki/Chinese_zodiac
// NOTE: I am also well aware that the Chinese Zodiac is not that easy to calculate because it is based on a lunar
// calendar.  Please bear with me.  It's just a weekly assignment after all.
// Your job is to do the following
// 1) Accept user input for the date of birth (given)
// 2) Store the date in a date structure that includes day, month (as a number), and year.
// 3) Pass the birth date to a function that generates a number between 1 and 12 (or 0 to 11 if you prefer)
//    This number is the zodiac number.  We will assume each year starts February 2nd and end February 1st.
//    The first acceptable zodiac number (1 or 0 depending how you count) is Feb 2, 1924-Feb1, 1925.  
//    This was the year of the rat.
// 4) Use the zodiac number to find the associated zodiac animal.
// Steps 3 and 4 COULD be combined but we won't because we will use the signs also to figure out if a friend is compatible
// with you.  The "Four Animal Trines" are signs that work well together.  For example, Rat, Dragon and Monkey are compatible
// as are Goat, Rabbit, and Pig.  These animals are exactly 4 numbers apart.  Thus we can find if someone is compatible with you
// if they are a difference of 4 or 8 for their zodiac number.
//    Eg If you are a dragon like me, a person born in July 1980 would be compatible (a monkey). 
//       Someone born Feb 1, 1984 would NOT be because their sign is a pig (the year starts Feb 2)
// 5) The friend input has been commented out.  Uncomment it and return whether your friend is compatible with you or not.

/* The zodiac animals (in order) are:
      Rat
	  Ox
	  Tiger
	  Rabbit
	  Dragon
	  Snake
	  Horse
	  Goat/Sheep
	  Monkey
	  Rooster
	  Dog
	  Pig
*/


// TODO: Define a struct that stores a person's date of birth.
struct birthdate {
	int day;
	int month;
	int year;
};

// An emum makes each of these animal names equivalent to a number (rat = 0, ox = 1).
// You can just check if zodiacNum == ox to test.  This is considered better than hard values
enum sign{rat = 0, ox, tiger, rabbit, dragon, snake, horse, goat, monkey, rooster, dog, pig};


// GIVEN: get a birthdate from the user
// and return that data to the main program.
birthdate inputBirthdate()
{
	int month;
	int day;
	int year;
	bool validDate = false;
	do {
		printf("Please write the birth month (as a number) \n");
		scanf_s("%d", &month);
		printf("Please write the birth day \n");
		scanf_s("%d", &day);
		printf("Please write the birth year \n");
		scanf_s("%d", &year);
		validDate = (month != 0) && (month <= 12);
		validDate = validDate && (day != 0 && day < 32);
	} while (!validDate);

	// TODO: put the birth data in your birthdate struct
    birthdate bd;
	//Subtracted 1924 from the year since 1924 is the first year
	//(So if you were born in 1924, that would be year 0)
	bd.year = year - 1924;
	bd.month = month;
	bd.day = day;
    return bd;
}

// Determines the zodiac number based on a given birthdate
sign getZNum(birthdate db)
{
	//Variable representing the modulo of the year
	int moduloRes = db.year % 12;

	//If statement used to use previous year's sign should the month be january 
	if (db.month == 1)
	{
		//If statement to loop back the sign around (because doing a -1 when the moduloResult is 0 would break the program)
		if (moduloRes == 0)
		{
			moduloRes = 11;
		}
		//Sets the result for the sign to the previous year's
		else
		{
			moduloRes -= 1;
		}
	}
	
	//else if used to avoid modifying moduloRes again if it had already been modified by the first if statement
	else if (db.month >= 2)
	{
		//Sets the sign to previous year's if the date is feb 1st
		if (db.month == 2 && db.day == 1)
		{
			moduloRes -= 1;
		}
	}
	
	//Returns sign based on the zodiac year year 
	switch (moduloRes)
	{
		case 0:
			return rat;
			break;
		case 1:
			return ox;
			break;
		case 2:
			return tiger;
			break;
		case 3:
			return rabbit;
			break;
		case 4:
			return dragon;
			break;
		case 5:
			return snake;
			break;
		case 6:
			return horse;
			break;
		case 7:
			return goat;
			break;
		case 8:
			return monkey;
			break;
		case 9:
			return rooster;
			break;
		case 10:
			return dog;
			break;
		case 11:
			return pig;
			break;
	}

}

// DEFINE
// getSignName gives the text name of the sign (rather than a number)
// based on the zodiacNumber (zNum). Please ignore the const char*.  Just treat
// this as text.  We will discuss pointers at a later date.
const char* getSignName(sign zNum) 
{
	switch (zNum)
	{
		case rat:
			return "rat";
			break;
		case ox:
			return "ox";
			break;
		case tiger:
			return "tiger";
			break;
		case rabbit:
			return "rabbit";
			break;
		case dragon:
			return "dragon";
			break;
		case snake:
			return "snake";
			break;
		case horse:
			return "horse";
			break;
		case goat:
			return "goat";
			break;
		case monkey:
			return "monkey";
			break;
		case rooster:
			return "rooster";
			break;
		case dog:
			return "dog";
			break;
		case pig:
			return "pig";
			break;
		default:
			return "";
	}
}

// DEFINE
// isCompatible: birthdate 1 x birthdate 2
// isCompatible(bd1, bd2) returns true if and only iff the two birthdates are compatible
// See the intructions at the top of the file for examples.
// .....

bool isCompatible(birthdate bd1, birthdate bd2)
{
	//Variables for the signs of each person)
	int sign1 = getZNum(bd1);
	int sign2 = getZNum(bd2);

	//Returns true if there is a difference of 4 between signs
	//Included -8 to avoid dealing with negative numbers (rat - 4 should be monkey, but would just give -4 instead)
	//The -8 fixes this, since monkey - 8 gives rat (8 - 8 == 0)
	if ((sign1 - 4) == sign2 || (sign2 - 4) == sign1 || (sign1 - 8) == sign2 || (sign2 - 8) == sign1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	printf("Let's find your Chinese Zodiac sign.  When were you born (only enter valid dates)? \n");
    birthdate myBD = inputBirthdate();
    sign zNum = getZNum(myBD);
    const char* myAnimal = getSignName(zNum);
    printf("Oh.  You're a %s.  How interesting. \n", myAnimal);
	
    printf("Let's find out if your friend is REALLY your friend.  When were they born? \n");
    birthdate theirBD = inputBirthdate();
    const char* theirAnimal = getSignName(getZNum(theirBD));
    printf("Oh.  Your friend is a %s.  Good to know. \n", theirAnimal);
	
    if (isCompatible(myBD, theirBD))
	{
		printf("The heavens say they are a good friend \n");
	}
	else 
	{
		printf("They are not a good friend.  Do not associate with them any more. \n");
	}
}