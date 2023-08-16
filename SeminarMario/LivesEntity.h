#pragma once
#include "Entities.h"
//class LivesEntityState :public EntityState {
//public:
//	void reset(cv::Point const& TL);
//	LivesEntityState(std::string const& image);
//};
EntityPtr CreateLives(std::string const& framePath,cv::Point tl);
