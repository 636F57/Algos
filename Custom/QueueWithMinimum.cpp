/* QueueWithMinimum.cpp 
**
** Custom class of queue which can return the minimum value of the queue anytime. 
** Run very fast at armitised O(1) for query minimum
**
** compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <deque>
#include <cmath>
#include <iostream>


class QueueMin
{
	struct mypair
	{
		int value;
		int min;
	};

private:	
	std::deque<mypair> vQueue; 
	int nCheckedIndex = 0; // index < nCheckedIndex: min = min_of_mypairs[0,nCheckedIndex). index >= nCheckedIndex: min = min_of_mypairs[nCheckedIndex,end of queue]
	
public:
	QueueMin(){}
	~QueueMin(){}
	
	int back()
	{
		return vQueue.back().value;
	}
	
	int front()
	{
		return vQueue.front().value;
	}
	
	int operator[] (int i)
	{
		return vQueue[i].value;
	}
	
	int size()
	{
		return vQueue.size();
	}
	
	void clear()
	{
		vQueue.clear();
	}
	
	void resize(int size)
	{
		vQueue.resize(size);
	}
	
	void push_back(int nNum)
	{
		if ((vQueue.size() == 0) || (vQueue.size() == nCheckedIndex+1))
			vQueue.push_back({nNum,nNum});
		else
			vQueue.push_back({nNum, std::min(nNum, vQueue.back().min)});
	}
	
	// return the popped value
	int pop_front()
	{
		if (nCheckedIndex == 0)  // renew the mins of newly added pairs with the min found by comparing backward
		{
			vQueue.back().min = vQueue.back().value;
			for (int j=vQueue.size()-2; j>=0; j--)
			{
				vQueue[j].min = std::min(vQueue[j].value, vQueue[j+1].min);
			}
			nCheckedIndex = vQueue.size() - 1;
		}
		
		mypair pairFront = vQueue.front();
		vQueue.pop_front();
		
		if(nCheckedIndex > 0)
			nCheckedIndex--;			
		
		return pairFront.value;
	}
	
	// return the minimum value of current queue
	int queryMin()
	{
		int nMin = vQueue.front().min;
		if (vQueue.size() > nCheckedIndex + 1)
			nMin = std::min(nMin, vQueue.back().min);

		return nMin;
	}
};

int main()  // sample program
{
	std::string strN;
	QueueMin qmQueue;
	
	std::cout<< "Demonstration of QueueMin class.\n";
	
	for (int i=0; i<5; i++)
	{
		std::cout << "Enter integer : ";
		std::cin >> strN;
		qmQueue.push_back(std::stoi(strN));
		
		std::cout << "Current Queue : \n";
		for (int j=0; j<qmQueue.size(); j++)
			std::cout << qmQueue[j] << " ";
		
		std::cout << "\nThe minimum value in the queue is : " << qmQueue.queryMin() << "\n";
	}
	
	std::cout << "End\n";	
	
	return 0;
}
