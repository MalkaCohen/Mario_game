#include "ScoreEntity.h"
using namespace cv;
using namespace std;

EntityStatePtr CreateScoreState(float fontScale, int fontFace)
{

	IGraphicsComponentPtr graphicsPtr(
		new ScoresGraphics(fontScale, fontFace));

	IPhysicsComponentPtr physicsPtr = make_shared<FixedWidgetPhysics>();
	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}

EntityPtr CreateScore(float fontScale, int fontFace)
{
	auto scoreState = CreateScoreState(fontScale, fontFace);
	EntityPtr score(new Entity(scoreState));
	return score;
	
}