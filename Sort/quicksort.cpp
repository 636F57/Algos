/* quicksort.cpp 
**
** Quick-sort library. unstable.
** can switch the pivot number between the middle of the array or a randomly choosed number of the interested array.
** Note: with random pivot (default), it runs always at N*log(N),
** with middle pivot, it runs mostly (including the best) at N*log(N), but in the worst at N*N
**
** as an additional information, this returns the number of how many comparison needed to sort the sequence.
**
** Qsort_RangeK sorts only the range [nK1, nK2] of the resulting array. good choice for faster performance when applicable.
**
**
** All compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <cmath>
#include <vector>
#include <iostream>

class QsortCls
{
private:
	static bool isLess(const int& a, const int& b, long long &lCnt)
	{
		lCnt++;
		return (a < b);
	}

	// return the number of comparisons needed between array values to sort the entire array
	// vArray is an array of integer vertices of [0,1,2,...,vArray.size()-1].
	// bRandom: true when use random value as a pivot number. use the middle of the array if false.
	static long long recur_Qsort(std::vector<int>& vArray, int nStartIndex, int nEndindex, bool bRandom = true)  
	{
		int nTmp, nPivot;
		int i= nStartIndex, j = nEndindex;
		long long lCompareCnt = 0;

		if (bRandom)
		{
			nPivot = vArray[nStartIndex + floor(rand()*(nEndindex-nStartIndex+1.0)/(RAND_MAX+1.0))];
		}
		else
		{	
			nPivot = vArray[ceil((nStartIndex+nEndindex)/2.0)];
		}
		
		do
		{
			while ( isLess(vArray[i], nPivot, lCompareCnt) )
				i++;
			while ( isLess(nPivot, vArray[j], lCompareCnt) )
				j--;
			
			if (i <= j)
			{
				nTmp = vArray[i];
				vArray[i] = vArray[j];
				vArray[j] = nTmp;
				i++;
				j--;
			}
		} while(i<=j);
		
		if (nStartIndex < j)
			lCompareCnt += recur_Qsort(vArray, nStartIndex, j);
		if (i < nEndindex)
			lCompareCnt += recur_Qsort(vArray, i, nEndindex);

		return lCompareCnt;
	}

	// return values are properly sorted only within the range of [k1, k2] of the sorted array.
	static void recur_Qsort_K(std::vector<int>& vArray, int nStartIndex, int nEndindex, int nK1, int nK2)
	{
		int nTmp, nPivot = vArray[nStartIndex + floor(rand()*(nEndindex-nStartIndex+1.0)/(RAND_MAX+1.0))];
		int i= nStartIndex, j = nEndindex;
		
		do
		{
			while ( vArray[i] < nPivot )
				i++;
			while ( nPivot < vArray[j] )
				j--;
			
			if (i <= j)
			{
				nTmp = vArray[i];
				vArray[i] = vArray[j];
				vArray[j] = nTmp;
				i++;
				j--;
			}
		} while(i<=j);
		
		if ((nStartIndex < j) && (j >= nK1))
			recur_Qsort_K(vArray, nStartIndex, j, nK1, nK2);
		if ((i < nEndindex) && (i <= nK2))
			recur_Qsort_K(vArray, i, nEndindex, nK1, nK2);

		return;
	}


public:
	QsortCls(){}
	~QsortCls(){}
	
	// Quick-sort with middle pivot
	static long long Qsort_Middle(std::vector<int>& vArray)
	{
		return recur_Qsort(vArray, 0, vArray.size()-1, false);
	}
	
	// Quick-sort with randomized pivot
	static long long Qsort(std::vector<int>& vArray)
	{
		return recur_Qsort(vArray, 0, vArray.size()-1, true);
	}

	// Quick-sort only the interested range [nK1, nK2] of the resulting array
	static void Qsort_RangeK(std::vector<int>& vArray, int nK1, int nK2)
	{
		return recur_Qsort_K(vArray, 0, vArray.size()-1, nK1, nK2);
	}
};

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
	
	long long lCnt = QsortCls::Qsort(vArray);
	
	std::cout << "The number of comparison needed to sort the seaquence : " << std::to_string(lCnt) << "\n";
	
	std::cout << "The sorted seaquence : \n";
	for (long long i=0; i<lTotal; i++)
	{
		std::cout << std::to_string(vArray[i]) << " ";
	}
	std::cout << "\n";
	
	return 0;
}