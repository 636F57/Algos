/* HamiltonianPath.cpp
**
** finds Hamiltonian Path if exists. returns as a list of vertices, which indicates the path from source to the final destination.
** takes AdjacencyMatrix as input.
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
#include <deque>
#include <iostream>

class HamiltonianPath
{
private:
	struct pathstatus
	{
		int end_vertex;          // current vertex
		std::vector<int> vUsed;  // array to store the previous vertex of when visited, otherwise -1.
		int usedcnt;             // number of used vertecies
	};

public:
	HamiltonianPath(){}
	~HamiltonianPath(){}
	
	static std::vector<std::vector<int>> getHamiltonianPath(std::vector<std::vector<bool>>& vAdjacencyMatrix, int nStartVertex)
	{
		int nVertexNum = vAdjacencyMatrix.size();
		
		std::vector<std::vector<int>> vHamiltonianPathList;
		std::vector<int> vTmpHamiltonianPath(nVertexNum);
		std::vector<int> vUsed(nVertexNum, -1);	
		
		vUsed[nStartVertex] = -2;       // previous vertex not available as starting vertex
		pathstatus tmpstatus, currentstatus;
		tmpstatus.end_vertex = nStartVertex;
		tmpstatus.usedcnt = 1;
		tmpstatus.vUsed.assign(vUsed.begin(),vUsed.end());
		std::deque<pathstatus> dqTmpPath({tmpstatus});
		
		int i, j, nCurrentVertex;
		
		while (dqTmpPath.size() > 0)
		{
			currentstatus = dqTmpPath.front();
			dqTmpPath.pop_front();
			nCurrentVertex = currentstatus.end_vertex;
			
			if (currentstatus.usedcnt == nVertexNum)  // Hamiltonian path found.
			{
				vTmpHamiltonianPath[nVertexNum-1] = nCurrentVertex;
				for (i=nVertexNum-2; i>=0; i--)
				{
					vTmpHamiltonianPath[i] = currentstatus.vUsed[vTmpHamiltonianPath[i+1]];
				}
				vHamiltonianPathList.push_back(vTmpHamiltonianPath);
				continue;
			}
			
			// go to the next vertex which is not used yet
			for (i=0; i<nVertexNum; i++)
			{
				if (vAdjacencyMatrix[nCurrentVertex][i] == false)
					continue;
					
				if (currentstatus.vUsed[i] != -1)
					continue;
					
				tmpstatus.end_vertex = i;
				tmpstatus.usedcnt = currentstatus.usedcnt + 1;
				tmpstatus.vUsed.assign(currentstatus.vUsed.begin(), currentstatus.vUsed.end());
				tmpstatus.vUsed[i] = nCurrentVertex;
				dqTmpPath.push_back(tmpstatus);
			}
		}
		
		return vHamiltonianPathList;
	}
};

int main()   // sample vAdjacencyMatrix is not yet implemented...
{	
	std::vector<std::vector<bool>> vAdjacencyMatrix;  
	
	std::vector<std::vector<int>> vHamiltonianPathList  = HamiltonianPath::getHamiltonianPath(vAdjacencyMatrix, 0);
	
		
	for (int k=0; k<vHamiltonianPathList.size(); k++)
	{
		for (int j=0; j<vHamiltonianPathList[k].size() - 1; j++)
			std::cout << std::to_string(vHamiltonianPathList[k][j]) + " -> ";

		std::cout << std::to_string(vHamiltonianPathList[k].back()) + "\n";
	}
	
	return 0;
}