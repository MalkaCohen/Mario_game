#include"LivesEntity.h"
using namespace cv;
using namespace std;

LivesEntityState::LivesEntityState(std::string const& imagepath)
	{
		Frame frame(imagepath);
		resize(frame.image, frame.image, Size(frame.image.cols / 8, frame.image.rows / 8));
		resize(frame.mask, frame.mask, Size(frame.mask.cols / 8, frame.mask.rows / 8));
		IGraphicsComponentPtr graphicsPtr(new LivesGraphics(frame));
		IPhysicsComponentPtr physicsPtr = make_shared<FixedWidgetPhysics>();
		_graphicsPtr = graphicsPtr;
		_physicsPtr = physicsPtr;
	}
	void LivesEntityState::reset(cv::Point const& TL)
	{
		_graphicsPtr->reset(3);
		_physicsPtr->reset(TL);

	}


EntityPtr CreateLives(std::string const& framePath,cv::Point tl)
{
	auto state = new LivesEntityState(framePath);
	state->reset(tl);
	EntityPtr lives(new Entity(make_shared<EntityState>(state->getGraphics(), state->getPhysics())));
	return lives;
}

