#ifndef _TILER_	
#define _TILER_

#include "cocos2d.h"
#include "MapR.h"

using namespace cocos2d;

enum TileType
{
	Null,
	Ground,
	Robot,
	Star
};
class TileR
{
public:
	TileR() {}
	TileR(Node* rootNode, TileType typ, float x, float y);
	~TileR();
	Sprite* sprite;
	TileType type;
private:

};

#endif

