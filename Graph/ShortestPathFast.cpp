/* ShortestPathFast.cpp
**
** Faster version of ShortestPath.cpp. (May not necessary true for densed graph as this is taking AdacencyList as input)
**
** contains functions that returns a list of distances between the corresponding vertex and the source vertex.
** You can easily find the vertex which has shortest distance form the source vertex looking up this distance table.
** 
** getDistancesDFS: build the distance table by Depth-First-Search. works fine when maximam possible weight is small, 
**                  otherwise too slow or costly in memory. Perhaps somewhat works with negative weighted edge but not sure...
**
** DijkstraBinaryHeap: build the distance table by Dijkstra algorithm, using Binary-Heap. Even faster than normal Dijkstra one.
**
** Both functions take AdacencyList as input. Edges are weighted.
** 
** Note that all vertices number starts from 0 (inclusive), to match with the index numbers of arrays.
**
** All worked find in original projects but not tested after extracted to here. (I must check...)
**
** All compiled and tested with g++ 6.2.0 MinGW-W64
**
** MIT License 
** Copyright (c) 2017 636F57@GitHub 
** See more detail at https://github.com/636F57/Algos/blob/master/LICENSE 
*/

#include <cstdlib> 
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <iostream>


/***************************** Depth-First-Search **************************************************/

struct edge
{
	int dest;
	int weight;
};

const long long MAX_DISTANCE = 1000000000000001;  // use this as initial value in the getDistances function. (change as needed)

// build a distance table by Depth-First-Search algorithm.
// nMaxWeight is the maximum possible weight for a edge
std::vector<long long> getDistancesDFS(std::vector<std::vector<edge>> &vAdjacencyList, int nMaxWeight, int nOriginVertex)
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

/******************************** Dijkstra with BinaryHeap ***********************************************/

#define MAX_DISTANCE2 10000*400000U  // initial value for distance table

struct edgeU  // non-natavie weighted edge
{
	int dest;
	unsigned int weight;
};

struct vertex  // actually struct edgeU will do but make this for more readable source...
{
	int dest;
	unsigned int distance;
};	

class comp
{
public:
	bool operator() (const vertex &a, const vertex &b) const
	{
		if (a.distance > b.distance)
			return true;
		else
			return false;
	}
};

// build distance table by Dijkstra algorithm from AdjacencyList.
// use binary heap (std::priority_queue) for queuing vertices.
std::vector<unsigned int> DijkstraBinaryHeap(std::vector<std::vector<edgeU>>& vAdjacencyList, int nStartVertex)
{
	int nVertexNum = vAdjacencyList.size();
	std::vector<unsigned int> vDistance(nVertexNum, MAX_DISTANCE2+1);  // distance from nStartVertex
	vDistance[nStartVertex] = 0;
	std::vector<char> vVertexStatus(nVertexNum, 0);  // 0:unchecked, 1:in queue, 2:done
	vVertexStatus[nStartVertex] = 1;
	std::priority_queue<vertex, std::vector<vertex>, comp> Queue((comp()));
	Queue.push({nStartVertex,0});
	int i, j, nCurrentVertex, nDestVertex;
	
	while (Queue.size() > 0)
	{
		// find the vertex in queue, which has the shortest distance from nStartVertex
		nCurrentVertex = Queue.top().dest;
		vVertexStatus[nCurrentVertex] = 2;
		Queue.pop();
		
		for (j=0; j<vAdjacencyList[nCurrentVertex].size(); j++)
		{
			nDestVertex = vAdjacencyList[nCurrentVertex][j].dest;
				
			if (vDistance[nDestVertex] > vDistance[nCurrentVertex] + vAdjacencyList[nCurrentVertex][j].weight)
			{
				vDistance[nDestVertex] = vDistance[nCurrentVertex] + vAdjacencyList[nCurrentVertex][j].weight;
			
				if (vVertexStatus[nDestVertex] != 2)
				{
					vVertexStatus[nDestVertex] = 1;
					Queue.push({nDestVertex,vDistance[nDestVertex]});
				}
			}
		}
		// prepare for next iteration. discard if vertex is already checked before
		while ( (Queue.size()>0) && (vVertexStatus[Queue.top().dest]==2) )
		{
			Queue.pop();
		}
	} 
	
	return vDistance;
}

int main()  // have not write a test program...
{
	return 0;
}
