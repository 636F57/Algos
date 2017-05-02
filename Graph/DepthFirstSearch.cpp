/* Depth-First-Search library
**
** contains IsConnectedGraph, HasCycle, getCycles, and getDistances as utility method functions.
**
** IsConnectedGraph: returns whether the graph is a connected graph or not
** HasCycle: returns whether the entire graph includes at least one cycle or not
** getCycles: returns a list of cycles contained in the entire graph
** getDistances: returns a list of distances between the corresponding vertex and the source vertex
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
	static std::vector<int> recur_connectedVertexesByDFS(std::vector<std::vector<int>> vAdjascencyList, int nStartVertex,
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
		
		for (i=0; i<vAdjascencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjascencyList[nStartVertex][i];
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
				vTmp = recur_connectedVertexesByDFS(vAdjascencyList, nVertex, pvConnectedVertex);
				pvConnectedVertex->insert(vConnectedVertex.end(), vTmp.begin(), vTmp.end());
			}
		}
		return vConnectedVertex;
	}

	// return if the connected part (which includes nStartVertex) of the graph contains at least one cycle
	static bool recur_hasCycleByDFS(std::vector<std::vector<int>> vAdjascencyList, int nStartVertex, std::vector<int> *pvVertexStatus)
	{
		(*pvVertexStatus)[nStartVertex] = 1;

		int i,j, nVertex, nStatus; 
		
		for (i=0; i<vAdjascencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjascencyList[nStartVertex][i];
			
			// check if the vertex is already visited
			nStatus = (*pvVertexStatus)[nVertex];
			if (nStatus == 1)
				return true;
			else if (nStatus == 2)
				continue;
			else
			{
				if ( recur_hasCycleByDFS(vAdjascencyList, nVertex, pvVertexStatus) )
					return true;
			}
		}
		(*pvVertexStatus)[nStartVertex] = 2;
		return false;
	}

	// return a list of cycles contained in the connected part (which includes nStartVertex) of the graph
	static std::vector<std::vector<int>> recur_getCyclesByDFS(std::vector<std::vector<int>> vAdjascencyList, int nStartVertex, 
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
		
		for (i=0; i<vAdjascencyList[nStartVertex].size(); i++)
		{
			nVertex = vAdjascencyList[nStartVertex][i];
		
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
				vCycleListTmp = recur_getCyclesByDFS(vAdjascencyList, nVertex, pvVertexStatus, pvChecking);
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
	static bool IsConnectedGraph(std::vector<std::vector<int>> vAdjascencyList)
	{
		std::vector<int> vConnectedVertex = recur_connectedVertexesByDFS(vAdjascencyList, 0);
		
		if ( vAdjascencyList.size() > vConnectedVertex.size() )
			return false;
		else if ( vAdjascencyList.size() == vConnectedVertex.size() )
			return true;
		else
			return false;  // actually should throw error. (invalid vAdjascencyList)
	}

	// return true if the entire graph includes at least one cycle
	static bool HasCycle(std::vector<std::vector<int>> vAdjascencyList)
	{
		//status: 0=not visited, 1=under checking (namely, ancestor of current vertex), 2=all checked (namely, dead end).
		std::vector<int> vVertexStatus(vAdjascencyList.size(), 0);
		
		int i, index = 0;
		bool bFound = true;
		while(bFound)
		{
			if (recur_hasCycleByDFS(vAdjascencyList, index, &vVertexStatus) == true)
				return true;
				
			// if there are non-visited vertexes, need to check them too.
			bFound = false;
			for (i=index; i<vAdjascencyList.size(); i++)
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
	static std::vector<std::vector<int>> getCycles(std::vector<std::vector<int>> vAdjascencyList)
	{
		//status: 0=not visited, 1=under checking (namely, ancestor of current vertex), 2=all checked (namely, dead end).
		std::vector<int> vVertexStatus(vAdjascencyList.size(), 0);
		
		std::vector<std::vector<int>> vCycleList, vCycleListTmp;
		int i, index = 0;
		bool bFound = true;
		while(bFound)
		{
			vCycleListTmp = recur_getCyclesByDFS(vAdjascencyList, index, &vVertexStatus);
			vCycleList.insert(vCycleList.end(), vCycleListTmp.begin(), vCycleListTmp.end());
				
			// if there are non-visited vertexes, need to check them too.
			bFound = false;
			for (i=index; i<vAdjascencyList.size(); i++)
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
	
	/** for weighted graph **/
	struct edge
	{
		int dest;
		int weight;
	};
	
	const long long MAX_DISTANCE = 1000000000000001;  // use this as initial value in the getDistances function. (change as needed)

	// return a list of distances between the corresponding vertex and the source vertex
	// vertex number is 0-based (starts from 0).
	// nMaxWeight is the maximum possible weight for a edge
	// good only when nMaxWeight is small otherwise it takes too long time and too much memory
	std::vector<long long> getDistances(std::vector<std::vector<edge>> &vAdjacencyList, int nMaxWeight, int nOriginVertex)
	{
		std::vector<std::list<int>> vCheckList(nMaxWeight+1);
		std::vector<long long> vDistance(vAdjacencyList.size(), MAX_DISTANCE);
		std::list<int>::iterator iter;
		long long lDistance = 0;
		
		vDistance[nOriginVertex] = 0;
		vCheckList[0].push_back(nOriginVertex);
		int nCheckCnt = 1, nVertexSrc, nVertexDest, i,j;
		int nWeightTmp;
		
		while (nCheckCnt > 0)
		{
			while ( vCheckList[lDistance % (nMaxWeight+1)].size() == 0)
			{
				lDistance++;
			}
			nWeightTmp = lDistance % (nMaxWeight + 1);
			nVertexSrc = vCheckList[nWeightTmp].front();
			vCheckList[nWeightTmp].pop_front();
			nCheckCnt--;
			
			for (i=0; i<vAdjacencyList[nVertexSrc].size(); i++)
			{
				nVertexDest = vAdjacencyList[nVertexSrc][i].dest;
				
				// if current path is shorter, move the vertex from the old distance queue to new distance queue
				if (vDistance[nVertexDest] > lDistance + vAdjacencyList[nVertexSrc][i].weight)
				{
					if (vDistance[nVertexDest] < MAX_DISTANCE)
					{
						nWeightTmp = vDistance[nVertexDest] % (nMaxWeight+1);
						iter = std::find(vCheckList[nWeightTmp].begin(), vCheckList[nWeightTmp].end(), nVertexDest);
						vCheckList[nWeightTmp].erase(iter);
						nCheckCnt--;
					}
					
					vDistance[nVertexDest] = lDistance + vAdjacencyList[nVertexSrc][i].weight;
					vCheckList[vDistance[nVertexDest] % (nMaxWeight+1)].push_back(nVertexDest);
					nCheckCnt++;
				}
			}
		}
		return vDistance;
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
	
	std::vector<std::vector<int>> vAdjascencyList(nVertexNum), vCycleList;
	int i, j, vertex_from, vertex_to;
	// generate random adjascency list (multiple edges could be generated with same source/target) 
	for (i=0; i<nEdgeNum; i++)
	{
		vertex_from = rand() % nVertexNum;
		vertex_to = rand() % nVertexNum;
		vAdjascencyList[vertex_from].push_back(vertex_to);
	}
	
	std::cout << "A graph is randomly generated. The AdjasencyList is :\n";
	for (i=0; i<nVertexNum; i++)
	{
		for (j=0; j<vAdjascencyList[i].size(); j++)
			std::cout << std::to_string(j) << " -> " << std::to_string(vAdjascencyList[i][j]) << "\n";
	}
	
	std::cout << "\nThis graph:\n";
	if (DepthFirstSearch::IsConnectedGraph(vAdjascencyList))
		std::cout << "is connected\n";
	else
		std::cout << "is NOT connected\n";
	
	if (DepthFirstSearch::HasCycle(vAdjascencyList))
	{
		std::cout << "has cycles. And the cycles are:\n";
		vCycleList = DepthFirstSearch::getCycles(vAdjascencyList);
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