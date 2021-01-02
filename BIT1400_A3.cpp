/*
 ---------------
 BIT 1400
 Assignment 3
 ---------------
*/

#include <iostream>
#include <math.h>
using namespace std;

//Decimal to hex converter according to instructions
char decToHex(int num)
{
	//If used to return a decimal number for hex
	if (num < 10)
	{
		return '0' + num; 
	}
	//Else to return a character for hex
	else
	{
		return 'A' + (num - 10);
	}
}

//Hex to decimal converter according to instructions
int hexToDec(char hex, int mult)
{
	unsigned int val = 0;
	
	if (hex >= 'a' && hex <= 'f')
	{
		val = (unsigned int)10 + hex - 'a';
	}
	else if(hex >= 'A' && hex <= 'F')
	{
		val = (unsigned int)10 + hex - 'A';
	}
	else if(hex >= '0' && hex <= '9')
	{
		val = (unsigned int)hex - '0';
	}

	return val * mult;
}

void testConvert(int myNum)
{

	//quotient variable is used to save the quotient of the division
	int quotient = myNum;
	//remainder is used to store the remainder of the modulo, and is used as parameters for decToHex
	int remainder;
	//I used an array instead of four different character variables to make calculating easier
	char hexChar[5];
	//Using a sum variable to calculate decimal from hex (rewriting myValue would be too messy)
	int decSum = 0;
	//Variable used to calculate and send the mult parameter for hexToDec
	int sentMult;

	//For loop lets me use i to store characters into the hexChar array
	for (int i = 0; i < 4; i++)
	{
		remainder = quotient % 16;
		hexChar[i] = decToHex(remainder);
		quotient /= 16;
	}

	//prints hexChar[3] to hexChar[0] to reverse the values (since the hex characters were saved backwards)
	printf("The integer %i converted into hex is %c%c%c%c\n", myNum, hexChar[3], hexChar[2], hexChar[1], hexChar[0]);

	//This for loop counts down, so that it can use i to calculate hexToDec's mult parameter
	for (int i = 3; i >= 0; i--)
	{
		//Calculates from left to right, 16^3, 16^2, 16^1, 16^0 (hence the i starting at 3 and then going down)
		sentMult = pow(16, i);
		decSum += hexToDec(hexChar[i], sentMult);
	}

	//prints hexChar[3] to hexChar[0] to reverse the values (since the hex characters were saved backwards)
	printf("The hex %c%c%c%c converted into an integer is %i\n", hexChar[3], hexChar[2], hexChar[1], hexChar[0], decSum);

}

void main()
{
	//Used to save the number inputted by the user
	int numberChosen;

	printf("This program converts a decimal to a hex, then a hex back to a decimal\n");
	printf("Disclaimer: entering a decimal or a character will break the program\n");
	printf("I'm not familiar with C/C++ enough yet to prevent a user from inputting those two options\n");
	
	//Forever loop, so that the user can input as many variables as they want
	while (1)
	{
		printf("Please enter a whole number between 0 and 65535\n");
		scanf_s("%d", &numberChosen);

		//Loop to make sure the value entered is between 0 and 65535
		while (numberChosen < 0 || numberChosen > 65535)
		{

			if (numberChosen < 0 || numberChosen > 65535)
			{
				printf("Invalid number\n");
			}
		
			scanf_s("%d", &numberChosen);
		}

		testConvert(numberChosen);
	}

}

