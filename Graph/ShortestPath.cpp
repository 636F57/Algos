/* ShortestPath.cpp
**
** contains functions that returns a list of distances between the corresponding vertex and the source vertex.
** You can easily find the vertex which has shortest distance form the source vertex looking up this distance table.
** 
** Native: build the distance table by trival method. works fine in any case but slow.
** Dijkstra: build the distance table by Dijkstra algorithm. Faster. 
**
** Both functions take AdacencyMatrix as input. Edges are not weighted. Good for densed graph.
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
#include <iostream>

#define MAX_DISTANCE 1000000000*2000LL  // initial value for distance table


// build distance table by native way
std::vector<long long> Native(std::vector<std::vector<int>>& vAdjacencyMatrix, int nStartVertex)
{	
	int nVertexNum = vAdjacencyMatrix.size();
	std::vector<long long> vDistance(nVertexNum, MAX_DISTANCE+1);  // distance from nStartVertex
	vDistance[nStartVertex] = 0;
	int i,j, cnt;
	bool bChanged = true;
	
	while (bChanged)
	{
		bChanged = false;
		for (i=nStartVertex, cnt=0; cnt<nVertexNum; cnt++, i=(i+1)%nVertexNum)
		{
			for (j=0; j<nVertexNum; j++)
			{
				if (vAdjacencyMatrix[i][j] >= 0)
				{		
					if (vDistance[j] > vDistance[i] + vAdjacencyMatrix[i][j])
					{
						vDistance[j] = vDistance[i] + vAdjacencyMatrix[i][j];
						bChanged = true;
					}
				}
			}
		}
	}
	
	return vDistance;
}

// build distance table by Dijkstra algorithm
std::vector<long long> Dijkstra(std::vector<std::vector<int>>& vAdjacencyMatrix, int nStartVertex)
{		
	int nVertexNum = vAdjacencyMatrix.size();
	std::vector<long long> vDistance(nVertexNum, MAX_DISTANCE+1);  // distance from nStartVertex
	vDistance[nStartVertex] = 0;
	
	std::vector<char> vVertexStatus(nVertexNum, 0);  // 0:unchecked, 1:in queue, 2:done
	vVertexStatus[nStartVertex] = 1;
	int i, j, cnt = 1, nCurrentVertex;
	long long lShortest;
	
	while (cnt > 0)
	{
		// find the vertex in queue, which has the shortest distance from nStartVertex
		lShortest = MAX_DISTANCE + 1;
		for (i=0; i<nVertexNum; i++)
		{
			if ((vVertexStatus[i]==1) && (vDistance[i] < lShortest))
			{
				lShortest = vDistance[i];
				nCurrentVertex = i;
			}
		}
		
		for (j=0; j<nVertexNum; j++)
		{
			if (j == nCurrentVertex)
				continue;
				
			if (vAdjacencyMatrix[nCurrentVertex][j] >= 0)
			{	
				if (vDistance[j] > vDistance[nCurrentVertex] + vAdjacencyMatrix[nCurrentVertex][j])
				{
					vDistance[j] = vDistance[nCurrentVertex] + vAdjacencyMatrix[nCurrentVertex][j];
				
					if (vVertexStatus[j] == 0)
					{
						vVertexStatus[j] = 1;
						cnt++;
					}
				}
			}
		}
		
		vVertexStatus[nCurrentVertex] = 2;
		cnt--;
	} 
	
	return vDistance;
}

int main()  // have not write a test program...
{
	return 0;
}
