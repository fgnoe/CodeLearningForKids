#ifndef __MAPR_SCENE_H__
#define __MAPR_SCENE_H__
#include "cocos2d.h"
#include "TileR.h"

using namespace cocos2d;

class MapR
{
public:
	static const int width = 8;
	static const int height = 10;
	Node* rootNode;
	MapR() {}
	MapR(Node* rn, int grid[10][8]);
private:
	int gridMap[height][width];
	void fillCells();
	void assignCells(int grid[height][width])
	{
		for (int i = 0;i < height;i++)
			for (int j = 0;j < width;j++)
			{
				gridMap[i][j] = grid[i][j];
			}
	}
};
#endif
