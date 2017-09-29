/* HighlyCompositeNumber.cpp 
**
** Returns a list of Highly Composite Numbers in a form of vector of custom structure, stHCNumber.
**
** NOTE: Highly Composite Number is a positive integer with more divisors than any smaller positive integer has.
** (cited from https://en.wikipedia.org/wiki/Highly_composite_number)
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
#include <algorithm>


class HCNClass
{	
	// hard-coded the primes for simplicity ... or just laziness of me. :D
	static const int NUMBER_OF_PRIMES = 6;
	static const int primorials[NUMBER_OF_PRIMES+3];    // need NUMBER_OF_PRIMES + 3 to stop recursion in a healthy way
	static const int primes[NUMBER_OF_PRIMES];
	static const int MAX_POSSIBLE = 32432400;
	
public:
	struct stHCNumber
	{
		int nNumber;          							// HighlyCompositeNumber
		int nDivisersCnt;     							// Number of divisers
		std::vector<int> vExponents;  					// exponents of each prime of the HighlyCompositeNumber. as vector for the sake of safety
	};

	// Returns the list of HighlyCompositeNumbers which is not greater than nMax
	static std::vector<stHCNumber> GetHighlyCompositeNumbers(int nMax)
	{
		std::vector<stHCNumber> vHCNs, vMultiples;        					
		
		// if exceeds the MAX_POSSIBLE, do nothing and return empty list.
		if (nMax > MAX_POSSIBLE) 
			return vHCNs;   
		
		int exponents[NUMBER_OF_PRIMES] = {0,0,0,0,0,0};	    // for internal use 
		
		recur_getMultipleOfPrimorials(&vMultiples, 0, nMax, exponents);
		
		// sort the multiples by number of divisers
		std::stable_sort(vMultiples.begin(), vMultiples.end(), [](stHCNumber a, stHCNumber b) {return a.nDivisersCnt < b.nDivisersCnt;});
		
		// sort the multiples by highly composite numbers
		std::stable_sort(vMultiples.begin(), vMultiples.end(), [](stHCNumber a, stHCNumber b) {return a.nNumber < b.nNumber;});
		
		// HighlyCompositeNumber is defined as a number which has more number of divisers than the smaller values does
		int nMaxDivCnt = 0;
		for (int i=0; i<vMultiples.size(); i++)
		{
			if (vMultiples[i].nDivisersCnt > nMaxDivCnt)
			{
				nMaxDivCnt = vMultiples[i].nDivisersCnt;
				vHCNs.push_back(vMultiples[i]);
			}
		}
		
		return vHCNs;
	}
	
private:

	// create a list of multiples of primorials. (all Highly composite numbers are multiples of primorials.)
	static void recur_getMultipleOfPrimorials(std::vector<stHCNumber>* pvPairs, int index, int num, int exponents[NUMBER_OF_PRIMES])
	{

		if (index >= NUMBER_OF_PRIMES + 3 )
		{
			std::cout << "Error in calculating multiples of primorials. Index out of range.\n";
			return;
		}
		
//std::cout << "index = " << std::to_string(index) << ",";  // for debug

		int	nMaxExpo = floor(log2(num)/log2(primorials[index]));

		// finish composing and store the result
		if (nMaxExpo == 0)
		{
			// calc number of divisers
			int divisers=1, product=1;
			std::vector<int> vExponents;
			
			for (int j=0; j<NUMBER_OF_PRIMES; j++)
			{
				divisers = divisers *(exponents[j]+1);
				product *= pow(primes[j], exponents[j]);
				vExponents.push_back(exponents[j]);
			}
			pvPairs->push_back({product, divisers, vExponents});
			return;
		}
		
		int exponents_new[NUMBER_OF_PRIMES] = {0,0,0,0,0,0};
			
		for (int i=0; i<=nMaxExpo; i++)
		{
			int num2 = num / pow(primorials[index], i);
			
			// update exponents
			for (int j=0; j<=index; j++)
				exponents_new[j] = exponents[j] + i;
			
			// add next factors
			recur_getMultipleOfPrimorials(pvPairs, index+1, num2, exponents_new);
		}
	}
	
};

// Put actual values into the const arrays
const int HCNClass::primorials[HCNClass::NUMBER_OF_PRIMES+3] 	= {2, 6, 30, 210, 2310, 30030, 510510, 9699690, 223092870};
const int HCNClass::primes[HCNClass::NUMBER_OF_PRIMES] 	 		= {2, 3, 5, 7, 11, 13}; 


int main()
{
	std::cout << "Enter the max value upto which highly composite numbers are listed: ";
	std::string strN;
	std::cin >> strN;
	int nMax = std::stoi(strN);
	
	std::vector<HCNClass::stHCNumber> vResults = HCNClass::GetHighlyCompositeNumbers(nMax);
	
	std::cout << "Found " << std::to_string(vResults.size()) << " highly composite numbers. Inside () is the number of divisers. \n";
	
	for (int i=0; i<vResults.size(); i++)
	{
		std::cout << std::to_string(i+1) << ": " << std::to_string(vResults[i].nNumber) << " (" << std::to_string(vResults[i].nDivisersCnt) << ")\n";
	}
	
	return 0;
}