/* Depth-First-Search library
**
** contains IsConnectedGraph, HasCycle, getCycles, and getDistances as utility method functions.
**
** IsConnectedGraph: returns whether the graph is a connected graph or not
** HasCycle: returns whether the entire graph includes at least one cycle or not
** getCycles: returns a list of cycles contained in the entire graph
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
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>


class DepthFirstSearch
{
private:
	// return a list of vertex indexes which are connected to the one indicated by nStartVertex
	static std::vector<int> recur_connectedverticesByDFS(std::vector<std::vector<int>> vAdjacencyList, int nStartVertex,
															std::vector<int> *pvConnectedVertex = 0)
	{
		std::vector<int> vConnectedVertex, vTmp;
		if (pvConnectedVertex == 0)
		{
			vConnectedVertex.assign(1, nStartVertex);
			pvConnectedVertex = &vConnectedVertex;
		}
		else
			pvConnectedVertex->push_back(nStartVertex);
			
		int i,j, nVertex;
		bool bFound;
		
		for (i=0; i<vAdjacencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjacencyList[nStartVertex][i];
			// check if the vertex is already in the list
			bFound = false;
			for (j=0; j<pvConnectedVertex->size(); j++)
			{
				if (nVertex == (*pvConnectedVertex)[j])
				{
					bFound = true;
					break;
				}
			}
			// if havent checked then check it by recursive call
			if (!bFound)
			{
				vTmp = recur_connectedverticesByDFS(vAdjacencyList, nVertex, pvConnectedVertex);
				pvConnectedVertex->insert(vConnectedVertex.end(), vTmp.begin(), vTmp.end());
			}
		}
		return vConnectedVertex;
	}

	// return if the connected part (which includes nStartVertex) of the graph contains at least one cycle
	static bool recur_hasCycleByDFS(std::vector<std::vector<int>> vAdjacencyList, int nStartVertex, std::vector<int> *pvVertexStatus)
	{
		(*pvVertexStatus)[nStartVertex] = 1;

		int i,j, nVertex, nStatus; 
		
		for (i=0; i<vAdjacencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjacencyList[nStartVertex][i];
			
			// check if the vertex is already visited
			nStatus = (*pvVertexStatus)[nVertex];
			if (nStatus == 1)
				return true;
			else if (nStatus == 2)
				continue;
			else
			{
				if ( recur_hasCycleByDFS(vAdjacencyList, nVertex, pvVertexStatus) )
					return true;
			}
		}
		(*pvVertexStatus)[nStartVertex] = 2;
		return false;
	}

	// return a list of cycles contained in the connected part (which includes nStartVertex) of the graph
	static std::vector<std::vector<int>> recur_getCyclesByDFS(std::vector<std::vector<int>> vAdjacencyList, int nStartVertex, 
																std::vector<int> *pvVertexStatus, std::vector<int> *pvChecking = 0)
	{
		(*pvVertexStatus)[nStartVertex] = 1;

		std::vector<int> vChecking, vTmp;
		if (pvChecking == 0)
		{
			vChecking.assign(1, nStartVertex);
			pvChecking = &vChecking;
		}
		else
			pvChecking->push_back(nStartVertex);

		std::vector<std::vector<int>> vCycleList, vCycleListTmp;
		std::vector<int>::iterator iter;
		int i,j, nVertex, nStatus;
		
		for (i=0; i<vAdjacencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjacencyList[nStartVertex][i];
		
			// check if the vertex is already visited
			nStatus = (*pvVertexStatus)[nVertex];
			if (nStatus == 1)  // found a cycle
			{
				for (iter=pvChecking->begin(); iter!=pvChecking->end(); iter++)
				{
					if (*iter == nVertex)
					{
						vTmp.assign(iter, pvChecking->end());
						vCycleList.push_back(vTmp);
						break;
					}
				}
			}
			else if (nStatus == 2)
				continue;
			else
			{
				vCycleListTmp = recur_getCyclesByDFS(vAdjacencyList, nVertex, pvVertexStatus, pvChecking);
				vCycleList.insert(vCycleList.end(), vCycleListTmp.begin(), vCycleListTmp.end());
			}
		}
		(*pvVertexStatus)[nStartVertex] = 2;
		return vCycleList;
	}

public:
	DepthFirstSearch(){}
	~DepthFirstSearch(){}
	
	// return true if the graph is a connected graph
	static bool IsConnectedGraph(std::vector<std::vector<int>> vAdjacencyList)
	{
		std::vector<int> vConnectedVertex = recur_connectedverticesByDFS(vAdjacencyList, 0);
		
		if ( vAdjacencyList.size() > vConnectedVertex.size() )
			return false;
		else if ( vAdjacencyList.size() == vConnectedVertex.size() )
			return true;
		else
			return false;  // actually should throw error. (invalid vAdjacencyList)
	}

	// return true if the entire graph includes at least one cycle
	static bool HasCycle(std::vector<std::vector<int>> vAdjacencyList)
	{
		//status: 0=not visited, 1=under checking (namely, ancestor of current vertex), 2=all checked (namely, dead end).
		std::vector<int> vVertexStatus(vAdjacencyList.size(), 0);
		
		int i, index = 0;
		bool bFound = true;
		while(bFound)
		{
			if (recur_hasCycleByDFS(vAdjacencyList, index, &vVertexStatus) == true)
				return true;
				
			// if there are non-visited vertices, need to check them too.
			bFound = false;
			for (i=index; i<vAdjacencyList.size(); i++)
			{
				if (vVertexStatus[i] == 0)
				{
					index = i;
					bFound = true;
					break;
				}
			}
		}
		return false;
	}
	
	// return a list of cycles contained in the entire graph
	static std::vector<std::vector<int>> getCycles(std::vector<std::vector<int>> vAdjacencyList)
	{
		//status: 0=not visited, 1=under checking (namely, ancestor of current vertex), 2=all checked (namely, dead end).
		std::vector<int> vVertexStatus(vAdjacencyList.size(), 0);
		
		std::vector<std::vector<int>> vCycleList, vCycleListTmp;
		int i, index = 0;
		bool bFound = true;
		while(bFound)
		{
			vCycleListTmp = recur_getCyclesByDFS(vAdjacencyList, index, &vVertexStatus);
			vCycleList.insert(vCycleList.end(), vCycleListTmp.begin(), vCycleListTmp.end());
				
			// if there are non-visited vertices, need to check them too.
			bFound = false;
			for (i=index; i<vAdjacencyList.size(); i++)
			{
				if (vVertexStatus[i] == 0)
				{
					index = i;
					bFound = true;
					break;
				}
			}
		}
		return vCycleList;
	}
	
};


/*******************************************************************/

int main()   // sample program
{
	std::string strN;
	
	std::cout << "Enter the number of vertices : ";
	std::cin >> strN;
	int nVertexNum = std::stoi(strN);
	std::cout << "Enter the number of edges : ";
	std::cin >> strN;
	int nEdgeNum = std::stoi(strN);
	
	std::vector<std::vector<int>> vAdjacencyList(nVertexNum), vCycleList;
	int i, j, vertex_from, vertex_to;
	// generate random adjascency list (multiple edges could be generated with same source/target) 
	for (i=0; i<nEdgeNum; i++)
	{
		vertex_from = rand() % nVertexNum;
		vertex_to = rand() % nVertexNum;
		vAdjacencyList[vertex_from].push_back(vertex_to);
	}
	
	std::cout << "A graph is randomly generated. The AdjasencyList is :\n";
	for (i=0; i<nVertexNum; i++)
	{
		for (j=0; j<vAdjacencyList[i].size(); j++)
			std::cout << std::to_string(j) << " -> " << std::to_string(vAdjacencyList[i][j]) << "\n";
	}
	
	std::cout << "\nThis graph:\n";
	if (DepthFirstSearch::IsConnectedGraph(vAdjacencyList))
		std::cout << "is connected\n";
	else
		std::cout << "is NOT connected\n";
	
	if (DepthFirstSearch::HasCycle(vAdjacencyList))
	{
		std::cout << "has cycles. And the cycles are:\n";
		vCycleList = DepthFirstSearch::getCycles(vAdjacencyList);
		for (i=0; i<vCycleList.size(); i++)
		{
			std::cout << std::to_string(vCycleList[i][0]);
			for (j=1; j<vCycleList[i].size(); j++)
				std::cout << " -> " << std::to_string(vCycleList[i][j]);
			std::cout << "\n";
		}
	}
	else
		std::cout << "has NO cycles\n";
	
	return 0;
}