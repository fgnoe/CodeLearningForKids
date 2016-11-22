#include "MapR.h"



MapR::MapR(Node* rn, int grid[10][8])
{
	rootNode = rn;
	assignCells(grid);
	fillCells();
}
void MapR::fillCells()
{
	for(int i = 0; i<height;i++)
		for (int j = 0;j < width;j++)
		{
			if ((TileType)gridMap[i][j] == TileType::Robot)
			{
				Sprite* sprtRobot = Sprite::create("sprites/robot1.png");
				rootNode->addChild(sprtRobot);
				sprtRobot->setName("robot");
				//sprtRobot->setPosition(Vec2(j * 80 + 72, (height - i - 1) * 80 + 500));
				
				//Positioning
				sprtRobot->setPosition(Vec2(RandomHelper::random_int(0, 700), RandomHelper::random_int(0, 1280)));
				MoveTo* move = MoveTo::create(1.f, Vec2(j * 80 + 72, (height - i - 1) * 80 + 500));
				EaseSineInOut* sine = EaseSineInOut::create(move);
				sprtRobot->runAction(sine);
			}
			else
				TileR(rootNode, (TileType)gridMap[i][j], j * 80 + 72, (height-i-1) * 80 + 500);
		}
}

