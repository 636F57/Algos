/* mergesort.cpp 
**
** Merge-sort library. Stable, always run at N*log(N)
**
** return the sorted seaquence and the number of inversions found in the original seaquence
**
** compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <vector>
#include <cmath>
#include <iostream>

// vArray is an array of integer vertices of [0,1,2,...,vArray.size()-1].
long long recur_mergesort(std::vector<int>& vArray) 
{
	if (vArray.size() == 1)
		return 0;
	else
	{	
		// split and get them sorted
		int nMiddle = ceil(vArray.size()/2);
		std::vector<int> vArray1, vArray2;
		long long lCnt;
		vArray1.assign(vArray.begin(), vArray.begin()+nMiddle);
		vArray2.assign(vArray.begin()+nMiddle, vArray.end());
		lCnt = recur_mergesort(vArray1);
		lCnt += recur_mergesort(vArray2);
		
		// merge the sorted arrays
		for (int i=0, j=0, k=0; i<vArray.size(); i++)
		{
			if (j == vArray1.size())
			{
				vArray[i] = vArray2[k];
				k++;
			}
			else if (k == vArray2.size())
			{
				vArray[i] = vArray1[j];
				j++;
			}
			else if (vArray1[j] <= vArray2[k])
			{
				vArray[i] = vArray1[j];
				j++;
			}
			else
			{
				vArray[i] = vArray2[k];
				k++;
				lCnt += nMiddle - j;
			}
		}
		
		return lCnt;
	}
}

int main()
{
	std::string strN;
	
	std::cout << "Enter the length of the integer sequence." << std::endl;
	std::cin >> strN;
	long long lTotal = std::stoll(strN);
	
	std::cout << "Enter the integer seaquence separating each numbers with a space." << std::endl;
	
	std::vector<int> vArray;
	for (long long i=0; i<lTotal; i++)
	{
		std::cin >> strN;
		vArray.push_back(std::stoi(strN));
	}
	
	long long lCnt = recur_mergesort(vArray);
	
	std::cout << "The number of inversions found in the original seaquence : " << std::to_string(lCnt) << "\n";
	
	std::cout << "The sorted seaquence : \n";
	for (long long i=0; i<lTotal; i++)
	{
		std::cout << std::to_string(vArray[i]) << " ";
	}
	std::cout << "\n";
	
	return 0;
}