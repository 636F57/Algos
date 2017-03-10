/* addition.cpp 
** Big Integer numbers addition function.
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <iostream>


// simple addition of big integers
std::string addInt(std::string strNum1, std::string strNum2)
{
	int nSign1=1, nSign2=1;
	if (strNum1[0] == '-')
	{
		strNum1.erase(0,1);
		nSign1 = -1;
	}
	if (strNum2[0] == '-')
	{
		strNum2.erase(0,1);
		nSign2 = -1;
	}
	
	if (nSign1*nSign2 < 0)
	{
/*		if (nSign1 > 0)
			return subInt(strNum1, strNum2);
		else
			return subInt(strNum2, strNum1);
		*/
		return std::string("Subtraction is not supported.");
	}
	
	int max_digit = std::max(strNum1.length(),strNum2.length());
	std::vector<int> vResult(max_digit+1, 0);
	// convert strings to int arrays
	std::vector<int> vNum1(max_digit, 0);
	std::vector<int> vNum2(max_digit, 0);
	char cTmp[2] = {0,0};
	for (int i=0; i<strNum1.length(); i++)
	{	
		cTmp[0] = strNum1[i];
		vNum1[i] = atoi(cTmp);
	}
	for (int i=0; i<strNum2.length(); i++)
	{	
		cTmp[0] = strNum2[i];
		vNum2[i] = atoi(cTmp);
	}
	
	// calculate starting from right-end to left in char arrays of strings
	int nCurrent, nTmp, nCarry, nIndex;
	for (int i=max_digit; i>=0; i--)
	{
		nIndex = i+1;
		nTmp = vNum1[i] + vNum2[i] + vResult[nIndex];
		vResult[nIndex] = nTmp % 10;
		nCarry = floor(nTmp / 10);
		while (nCarry > 0)
		{
			nTmp = vResult[nIndex-1] + nCarry;
			vResult[nIndex-1] = nTmp % 10;
			nCarry = floor(nTmp / 10);
			nIndex--;
		}
	}
	
	std::string strResult = "";
	if (nSign1 < 0)
		strResult =  "-";
	if (vResult[0] != 0)
		strResult += std::to_string(vResult[0]);
	for (int i=1; i<vResult.size(); i++)
	{
		strResult += std::to_string(vResult[i]);
	}
	
	return strResult;
}

int main()
{
	std::cout << "Enter two numbers as base-10 integers." << std::endl;
	std::string strNum1, strNum2, strResult;
	std::cin >> strNum1;
	std::cin >> strNum2;
	
	strResult = addInt(strNum1, strNum2);
	std::cout << strResult << std::endl;
	
	return 0;
}
