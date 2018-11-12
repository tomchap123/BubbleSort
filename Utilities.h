//Module:   Utilities.h (Template class)
//Author:   Tom Chaparas    
//Date:     October 1, 2018
//Function: Template class virtual functions
//			Useful utilities
//			CompareSize()      compares the size of 2 base types
//			TCHARtoInt()       converts a TCHAR to am integer
//			InttoTCHAR()	   converts an integer to a TCHAR
//			TCHARtoString()	   converts a TCHAR to a string
//			StringtoTCHAR()	   converts a string to a TCHAR

#pragma once
//Must include all libraries needed for functions
//Implementation code is included in this file as well

#include <string>				//string library
#include <sstream>				//string stream library

using namespace std;			//standard names

#define TCHAR_SIZE 128			//reference rather than hard-code TCHAR sizes

/////////////////////////////////////////////

//compares two items of similar basic data type
//returns -1 if first < second
//returns 0 if the items are idemtical
//returns 1 if first > second

template <class Type>
Type CompareSize(Type x, Type y)
{
	if (x < y)					//perform comparisons
		return -1;
	else if (x == y)
		return 0;
	else return 1;

}

//converts specified TCHAR into an integer, using specified base
//returns integer
//uses stoi, so invalid TCHAR returns 0 integer

template <class Type>
int TCHARtoInt(TCHAR* szIn, Type iBase)
{
	int iReturn = 0;							//return value

	if (lstrlen(szIn) != 0)						//do nothing fi nothing is entered
	{
		wstring temp(szIn);						//convert TCHAR to stream
		string str(temp.begin(), temp.end());	//convert stream to string

		iReturn = stoi(str, NULL, iBase);		//convert string to integer base (iBase)
	}
	return iReturn;								//integer return value
}
//converts integer to TCHAR
//modifies parameter TCHAR in place
//max 10 digit integer

template <class Type>
void InttoTCHAR(Type iIn, TCHAR* szIn)
{
	TCHAR szWork[10];						//produced at compile time, so must be hard-coded size

	//clear
	memset(szIn, 0, sizeof(szIn));			//blank the input TCHAR so another appends to new value

	_stprintf_s(								//printf that works with TCHARs
		szWork,								//destination TCHAR
		TEXT("%i"),							//pattern
		iIn);								//source integer

	_tcscpy_s(								//copy that works with TCHARs
		szIn,								//destination TCHAR
		10,									//max number of chars to copy
		szWork);							//source TCHAR
}

//converts TCHAR to a string
//uses pointer to string (calling code needs &string)

template <class Type>
void TCHARtoString(TCHAR* szIn, Type* strIn)
{
	strIn->erase();						//empty return string

	if (lstrlen(szIn) != 0)			//must be characters in TCHAR to store
	{
		wstring temp(szIn);					//convert TCHAR to stream
		string str(temp.begin(), temp.end());	//convert stream to string

		strIn->append(str);				//copy temp string to return string
	}
}

//converts string to a TCHAR
//modifies TCHAR in place
//returns mbstowcs_s return code
//max TCHAR_SIZE char string length

template <class Type>
size_t StringtoTCHAR(Type* strIn, TCHAR* szIn)
{
	size_t pReturnValue = 0;				//return value for mbstowcs_s

	memset(szIn, 0, sizeof(szIn));		//erase TCHAR
	
	if (strIn->length() > 0 &&			//cannot be 0 length
		strIn->length() < TCHAR_SIZE)	//cannot be larger than max TCHAR
	{
		mbstowcs_s(						//convert string to TCHAR
			&pReturnValue,				//return value
			szIn,						//destination TCHAR
			TCHAR_SIZE,					//size of destination TCHAR
			strIn->c_str(),				//source string
			TCHAR_SIZE);				//max chars to copy
	}
	return pReturnValue;				//return error code
}

