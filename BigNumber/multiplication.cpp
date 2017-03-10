/* multiplication.cpp 
** Big Integer numbers multiplication function.
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


// simple recursive multiplication of big integers
std::string multiplyInt(std::string strNum1, std::string strNum2)
{
	int nSign = 1;
	if (strNum1[0] == '-')
	{
		strNum1.erase(0,1);
		nSign *= -1;
	}
	if (strNum2[0] == '-')
	{
		strNum2.erase(0,1);
		nSign *= -1;
	}
	
	std::vector<int> vResult(strNum1.length() + strNum2.length(), 0);
	// convert strNum1 into array of integers of each digit
	std::vector<int> vNum1(strNum1.length(), 0);
	char cTmp[2]={0,0};
	for (int i=0; i<strNum1.length(); i++)
	{
		cTmp[0] = strNum1[i];
		vNum1[i] = atoi(cTmp);
	}
	
	// calculate starting from right-end to left in char array of string
	int nCurrent, nTmp, nCarry, nIndex;
	int i_max = strNum2.size()-1;
	int j_max = vNum1.size()-1;
	int res_max = vResult.size()-1;
	
	for (int i=i_max; i>=0; i--)
	{
		cTmp[0] = strNum2[i];
		nCurrent = atoi(cTmp);
		for (int j=j_max; j>=0; j--)
		{
			nIndex = res_max-(i_max-i)-(j_max-j);
			nTmp = nCurrent * vNum1[j] + vResult[nIndex];
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
	}
	
	std::string strResult = "";
	if (nSign < 0)
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
	
	strResult = multiplyInt(strNum1, strNum2);
	std::cout << strResult << std::endl;
	
	return 0;
}
