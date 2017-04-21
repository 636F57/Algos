/* combination.cpp 
**
** Generates a list of all possible combination of choosing m elements out of the given type-T array.
**
** compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <vector>
#include <iostream>

template <typename T>
std::vector<std::vector<T>> recur_genCombinations(const T *pArray, int nArrraySize, int m)
{
	std::vector<std::vector<T>> vCombList;
	std::vector<T> vCombination(m);
	int i,j;
	
	if (m == 1)
	{
		for (i=0; i<nArrraySize; i++)
		{
			vCombination[0] = pArray[i];
			vCombList.push_back(vCombination);
		}
		return vCombList;
	}
	
	std::vector<std::vector<T>> vTmpList;
	for (i=0; i<=nArrraySize-m; i++)
	{
		vTmpList = recur_genCombinations(&pArray[i+1], nArrraySize-1-i, m-1);
		for (j=0; j<vTmpList.size(); j++)
		{
			vTmpList[j].push_back(pArray[i]);
			vCombList.push_back(vTmpList[j]);
		}
	}
	return vCombList;
}


int main()  // sample program
{
	std::string strN;
	
	std::cout << "This will generate combinations of selecting m elements out of integer sequence [1,2,...,N].\n";
	std::cout << "Enter N : ";
	std::cin >> strN;
	int nN = std::stoi(strN);
	std::cout << "Enter m : ";
	std::cin >> strN;
	int nM = std::stoi(strN);
	
	// create one array to generate permutations list
	std::vector<int> vArrayOne(nN);
	for (int i=0; i<nN; i++)
		vArrayOne[i] = i+1;
	
	std::vector<std::vector<int>> vCombList = recur_genCombinations((const int*)(vArrayOne.data()), nN, nM);
	
	std::cout << "The number of combinations : " << std::to_string(vCombList.size()) << "\n";
	
	std::cout << "The combinations : \n";	
	
	for (int i=0; i<vCombList.size(); i++)
	{
		for (int j=0; j<vCombList[i].size(); j++)
		{
			std::cout << std::to_string(vCombList[i][j]) << " ";
		}
		std::cout << "\n";
	}
	
	return 0;
}