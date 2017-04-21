/* permutation.cpp 
**
** Generates a list of all possible permutations of the given type-T array.
**
** compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <vector>
#include <deque>
#include <iostream>

template <typename T>
std::vector<std::vector<T>> recur_genPermutations(std::deque<T> dqArray)
{
	int i,j, nTmp, nArraySize = dqArray.size();
	std::vector<std::vector<T>> vPermutations;
	
	if (nArraySize == 1)
	{
		std::vector<T> vOne;
		vOne.push_back(dqArray[0]);
		vPermutations.push_back(vOne);
		return vPermutations;
	}
	
	std::vector<std::vector<T>> vTmp;
	
	for (i=0; i<nArraySize; i++)
	{
		nTmp = dqArray.front();
		dqArray.pop_front();
		vTmp = recur_genPermutations(dqArray);
		for (j=0; j<vTmp.size(); j++)
		{
			vTmp[j].push_back(nTmp);
			vPermutations.push_back(vTmp[j]);
		}
		dqArray.push_back(nTmp);
	}
	return vPermutations;
}

int main()  // sample program
{
	std::string strN;
	
	std::cout << "This will generate permutations of integer sequence [1,2,...,N]. Please enter N :";
	std::cin >> strN;
	int nN = std::stoi(strN);
	
	// create one array to generate permutations list
	std::deque<int> dqArrayOne(nN);
	for (int i=0; i<nN; i++)
		dqArrayOne[i] = i+1;
	
	std::vector<std::vector<int>> vPermutations = recur_genPermutations(dqArrayOne);

	std::cout << "The number of permutations : " << std::to_string(vPermutations.size()) << "\n";
	
	std::cout << "The permutations : \n";	
	
	for (int i=0; i<vPermutations.size(); i++)
	{
		for (int j=0; j<vPermutations[i].size(); j++)
		{
			std::cout << std::to_string(vPermutations[i][j]) << " ";
		}
		std::cout << "\n";
	}
	
	return 0;
}