#include "SlimeEntity.h"

using namespace cv;
using namespace std;

EntityStatePtr CreateSlimeEnemyState(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr physicsPtr = make_shared<FixedWidgetPhysics>();
	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}

EntityPtr CreateSlimeEnemy(std::string const& rootAnimationsFolder)
{
	auto slimeState = CreateSlimeEnemyState(rootAnimationsFolder);
	EntityPtr slime(new Entity(slimeState));
	return slime;
}
