/* EulerianPath.cpp
**
** finds Eulerian Path if exists. returns as a list of vertices, which indicates the path from source to the final destination.
**
** 
** Note that all vertices number starts from 0 (inclusive), to match with the index numbers of arrays.
**
** worked find in original projects but not tested after extracted to here. (I must check...)
**
** All compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <vector>
#include <iostream>

class EulerianPath
{
public:
	struct edge
	{
		int dest;
		int edgeindex;
		bool used = false;
	};
	
private:
	// pEdge is internal use for recuring process of this function.
	static bool recur_findEulerianPath(std::vector<std::vector<edge>>& vAdjacencyList, std::vector<edge>* pvEulearianPath, bool bDirected = false, edge* pEdge = 0)
	{
		int i,j, nStartVertex;
		
		if (pEdge == 0)
			nStartVertex = -1;
		else
			nStartVertex = pEdge->dest;
			
		// if this is called first time, check if the eulerian path exits, then set the nStartVertex (if there's a special vertex, should start with it)
		if (nStartVertex == -1)  
		{
			if (!bDirected)
			{
				// there should be at most two vertices which has odd degree
				int cnt = 0;
				for (i=0; i<vAdjacencyList.size(); i++)
				{
					if (vAdjacencyList[i].size() % 2 == 1)
					{	
						nStartVertex = i;
						cnt++;
					}
				}
				if (cnt > 2)
					return false;
				if (cnt == 0)
					nStartVertex = 0;
			}
			else
			{
				std::vector<int> vCount(vAdjacencyList.size(),0); // list of deg_out for all vertices
				for (i=0; i<vAdjacencyList.size(); i++)
				{
					for (j=0; j<vAdjacencyList[i].size(); j++)
					{
						vCount[vAdjacencyList[i][j].dest] += 1;
					}
				}
				// there must be at most one couple of vertices which has +1 and -1 difference between deg_in and deg_out.
				int nDegDifference = 0;
				bool bFirst = true;
				for (i=0; i<vAdjacencyList.size(); i++)
				{
					if (vAdjacencyList[i].size() == vCount[i])
						continue;
					
					if (nDegDifference == 0)
					{
						if (bFirst)
						{
							nDegDifference = vAdjacencyList[i].size() - vCount[i];
							nStartVertex = i;
							bFirst = false;
						}
						else
							return false;
					}
					else 
					{
						nDegDifference += vAdjacencyList[i].size() - vCount[i];
						if (nDegDifference != 0)
							return false;
					}	
				}
				if (nDegDifference != 0)
					return false;
					
				if (nStartVertex == -1)
					nStartVertex = 0;		
			}
		}
		
		edge tmpitem;

		for (i=0; i<vAdjacencyList[nStartVertex].size(); i++)
		{
			tmpitem = vAdjacencyList[nStartVertex][i];
			if (tmpitem.used)
				continue;

			// mark the edge as used
			vAdjacencyList[nStartVertex][i].used = true;
			if (!bDirected)
			{
				for (j=0; j<vAdjacencyList[tmpitem.dest].size(); j++)
				{
					if (vAdjacencyList[tmpitem.dest][j].dest == nStartVertex)
						vAdjacencyList[tmpitem.dest][j].used = true;
				}
			}
			recur_findEulerianPath(vAdjacencyList, pvEulearianPath, bDirected, &tmpitem);
		}
		if (pEdge == 0)
			pvEulearianPath->push_back({nStartVertex, -1, true});
		else
			pvEulearianPath->push_back(*pEdge);
		return true;
	}

public:
	EulerianPath(){}
	~EulerianPath(){}
	
	// assume the entire graph is connected.
	// return false when no Eulerian path exits. pvEulearianPath is the pointer to a vector array to store the resulting path.
	// bDirected is the flag whether the graph is directed or not. default is false.
	static bool findEulerianPath(std::vector<std::vector<edge>>& vAdjacencyList, std::vector<edge>* pvEulearianPath, bool bDirected = false)
	{
		return recur_findEulerianPath(vAdjacencyList, pvEulearianPath, bDirected, 0);
	}
};

int main()  // sample program needs to be complete...
{	
	std::vector<std::vector<EulerianPath::edge>> vAdjacencyList;
	/*-- create vAdjacencyList  here --*/
	
	std::vector<EulerianPath::edge> vEulearianPath; // this is for result
	bool bRes = EulerianPath::findEulerianPath(vAdjacencyList, &vEulearianPath);
	
	return 0;
}