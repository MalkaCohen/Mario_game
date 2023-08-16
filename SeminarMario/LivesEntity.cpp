#include"LivesEntity.h"
using namespace cv;
using namespace std;



EntityStatePtr CreateLiveState(std::string const& imagepath) {
		Frame frame(imagepath);
		resize(frame.image, frame.image, Size(frame.image.cols / 8, frame.image.rows / 8));
		resize(frame.mask, frame.mask, Size(frame.mask.cols / 8, frame.mask.rows / 8));
		IGraphicsComponentPtr graphicsPtr(new LivesGraphics(frame));
		IPhysicsComponentPtr physicsPtr = make_shared<FixedWidgetPhysics>();
		return make_shared<EntityState>(graphicsPtr, physicsPtr);

}


EntityPtr CreateLives(std::string const& framePath,cv::Point tl)
{
	auto liveState = CreateLiveState(framePath);
	EntityPtr lives(new Entity(liveState));
	lives->reset(tl);
	return lives;

}

