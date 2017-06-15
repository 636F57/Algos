/* EulerianPath.cpp
**
** finds Eulerian Path if exists. returns as a list of vertices, which indicates the path from source to the final destination.
** This does not list up all Eulerian paths. Only return one of them even if multiple exists.
** 
** Note that all vertices number starts from 0 (inclusive), to match with the index numbers of arrays.
**
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
		int dest;			// mandatory entry
		int edgeinfo = 0;	// just for optional info about edge. remain intact in EulerianPath finder functions.
		bool used = false;	// this will change after passsed in to EulerianPath finder functions.
	};
	
private:
	// pEdge is internal use for recuring process of this function.
	static bool recur_findEulerianPath(std::vector<std::vector<edge>>& vAdjacencyList, std::vector<edge>* pvEulerianPath, bool bDirected = false, edge* pEdge = 0)
	{
		int i,j, nStartVertex;
		
		if (pEdge == 0) // first time call
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
			recur_findEulerianPath(vAdjacencyList, pvEulerianPath, bDirected, &tmpitem);
		}
		if (pEdge == 0)  // now returned to the first vertex
			pvEulerianPath->push_back({nStartVertex, -1, true});  
		else
			pvEulerianPath->push_back(*pEdge);
		return true;
	}

public:
	EulerianPath(){}
	~EulerianPath(){}
	
	// assume the entire graph is connected.
	// return false when no Eulerian path exits. pvEulerianPath is the pointer to a vector array to store the resulting path.
	// bDirected is the flag whether the graph is directed or not. default is false.
	static bool findEulerianPath(std::vector<std::vector<edge>>& vAdjacencyList, std::vector<edge>* pvEulerianPath, bool bDirected = false)
	{
		return recur_findEulerianPath(vAdjacencyList, pvEulerianPath, bDirected, 0);
	}
};

int main() 
{	
	/* sample graph
	                      /\
	                     /  \
	-------------------------
	|                   |
	|                   |
	--------------------
	*/
	
	std::vector<std::vector<EulerianPath::edge>> vAdjacencyList(6);
	vAdjacencyList[0] = {{1},{3}};
	vAdjacencyList[1] = {{0},{2}};
	vAdjacencyList[2] = {{1},{3}};
	vAdjacencyList[3] = {{0},{2},{4},{5}};
	vAdjacencyList[4] = {{3},{5}};
	vAdjacencyList[5] = {{3},{4}};
		
	std::vector<EulerianPath::edge> vEulerianPath; // this is for result

	bool bRes = EulerianPath::findEulerianPath(vAdjacencyList, &vEulerianPath);
	
	if (bRes)
	{
		std::cout << "Eulerian path found.\n";
		for (int k=0; k<vEulerianPath.size()-1; k++)
		{
			std::cout << std::to_string(vEulerianPath[k].dest) +  " -> ";
		}
		std::cout << std::to_string(vEulerianPath.back().dest) + "\n";
	}
	else
	{
		std::cout << "EulerianPath not found.\n";
	}
	
	return 0;
}