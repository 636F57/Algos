/* HamiltonianPath.cpp
**
** finds Hamiltonian Path if it exists. returns as a list of vertices, which indicates the path from source to the final destination.
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
		int end_vertex;				// current vertex
		std::vector<int> vVisited;	// array to store the previous vertex of the time when it is visited, otherwise -1.
		int visitedcnt;				// number of visited vertecies
	};

public:
	HamiltonianPath(){}
	~HamiltonianPath(){}
	
	static std::vector<std::vector<int>> getHamiltonianPath(std::vector<std::vector<bool>>& vAdjacencyMatrix, int nStartVertex)
	{
		int nVertexNum = vAdjacencyMatrix.size();
		
		std::vector<std::vector<int>> vHamiltonianPathList;
		std::vector<int> vTmpHamiltonianPath(nVertexNum);
		std::vector<int> vVisited(nVertexNum, -1);	
		
		vVisited[nStartVertex] = -2;       // previous vertex not available as starting vertex
		pathstatus tmpstatus, currentstatus;
		tmpstatus.end_vertex = nStartVertex;
		tmpstatus.visitedcnt = 1;
		tmpstatus.vVisited.assign(vVisited.begin(),vVisited.end());
		std::deque<pathstatus> dqTmpPath({tmpstatus});
		
		int i, j, nCurrentVertex;
		
		while (dqTmpPath.size() > 0)
		{
			currentstatus = dqTmpPath.front();
			dqTmpPath.pop_front();
			nCurrentVertex = currentstatus.end_vertex;
			
			if (currentstatus.visitedcnt == nVertexNum)  // Hamiltonian path found.
			{
				vTmpHamiltonianPath[nVertexNum-1] = nCurrentVertex;
				for (i=nVertexNum-2; i>=0; i--)
				{
					vTmpHamiltonianPath[i] = currentstatus.vVisited[vTmpHamiltonianPath[i+1]];
				}
				vHamiltonianPathList.push_back(vTmpHamiltonianPath);
				continue;
			}
			
			// go to the next vertex which is not visited yet
			for (i=0; i<nVertexNum; i++)
			{
				if (vAdjacencyMatrix[nCurrentVertex][i] == false)
					continue;
					
				if (currentstatus.vVisited[i] != -1)
					continue;
					
				tmpstatus.end_vertex = i;
				tmpstatus.visitedcnt = currentstatus.visitedcnt + 1;
				tmpstatus.vVisited.assign(currentstatus.vVisited.begin(), currentstatus.vVisited.end());
				tmpstatus.vVisited[i] = nCurrentVertex;
				dqTmpPath.push_back(tmpstatus);
			}
		}
		
		return vHamiltonianPathList;
	}
	
	static std::vector<std::vector<int>> getHamiltonianCycle(std::vector<std::vector<bool>>& vAdjacencyMatrix, int nStartVertex)
	{
		std::vector<std::vector<int>> vHamiltonianCycleList;
		std::vector<std::vector<int>> vHamiltonianPathList = getHamiltonianPath(vAdjacencyMatrix, 0);
		
		for (int i=0; i<vHamiltonianPathList.size(); i++)
		{
			if (vAdjacencyMatrix[nStartVertex][vHamiltonianPathList[i].back()] == true)
			{
				vHamiltonianPathList[i].push_back(nStartVertex);
				vHamiltonianCycleList.push_back(vHamiltonianPathList[i]);
			}
		}
		
		return vHamiltonianCycleList;
	}
};

int main()   
{	
	/* sample graph
	    /| \ 
	   / |  \  
	  / / \  \
	 / /    \  \
	/ /      \  \
	---       ---
	\ \      /  /
	 \ \    /  /
	  \  --   /
	   \/   \/ 
	    -----
	*/
	std::vector<std::vector<bool>> vAdjacencyMatrix(10);  
	vAdjacencyMatrix[0] = {0,1,0,0,1,1,0,0,0,0};        
	vAdjacencyMatrix[1] = {1,0,1,0,0,0,1,0,0,0};
	vAdjacencyMatrix[2] = {0,1,0,1,0,0,0,1,0,0};
	vAdjacencyMatrix[3] = {0,0,1,0,1,0,0,0,1,0};
	vAdjacencyMatrix[4] = {1,0,0,1,0,0,0,0,0,1};
	vAdjacencyMatrix[5] = {1,0,0,0,0,0,1,0,0,1};
	vAdjacencyMatrix[6] = {0,1,0,0,0,1,0,1,0,0};
	vAdjacencyMatrix[7] = {0,0,1,0,0,0,1,0,1,0};
	vAdjacencyMatrix[8] = {0,0,0,1,0,0,0,1,0,1};
	vAdjacencyMatrix[9] = {0,0,0,0,1,1,0,0,1,0};
	
	
	std::vector<std::vector<int>> vHamiltonianPathList = HamiltonianPath::getHamiltonianPath(vAdjacencyMatrix, 0);
	
	std::cout << "Number of Hamiltonian paths : " << std::to_string(vHamiltonianPathList.size()) << "\n";	
	for (int k=0; k<vHamiltonianPathList.size(); k++)
	{
		for (int j=0; j<vHamiltonianPathList[k].size() - 1; j++)
			std::cout << std::to_string(vHamiltonianPathList[k][j]) + " -> ";

		std::cout << std::to_string(vHamiltonianPathList[k].back()) + "\n";
	}
	
	std::vector<std::vector<int>> vHamiltonianCycleList = HamiltonianPath::getHamiltonianCycle(vAdjacencyMatrix, 0 );
	std::cout << "\nNumber of Hamiltonian cycles : " << std::to_string(vHamiltonianCycleList.size()) << "\n";
	for (int k=0; k<vHamiltonianCycleList.size(); k++)
	{
		for (int j=0; j<vHamiltonianCycleList[k].size() - 1; j++)
			std::cout << std::to_string(vHamiltonianCycleList[k][j]) + " -> ";

		std::cout << std::to_string(vHamiltonianCycleList[k].back()) + "\n";
	}
	
	return 0;
}