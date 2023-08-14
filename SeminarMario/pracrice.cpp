#include "Animation.h"
#include <opencv2/opencv.hpp>
#include <ctime>

// @2: include the slime enemy:
#include "SlimeEntity.h"
#include "LivesEntity.h"
#include "ScoreEntity.h"
#include "Timer.h"
#include "HeroEntity.h"
#include "EntitiesPool.h"

using namespace cv;

/////////////////////////////////δρετι!
	
int main()
{
	Mat background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
	resize(background, background, Size(1370, 745));

	auto slime = CreateSlimeEnemy(R"(../Animations/SlimeOrange)");
	slime->reset(Point(background.size().width / 35, background.size().height *2.35 / 3));
	
	EntitiesPool slimeEntities;
	slimeEntities.insert(slime);
	auto slime1=slimeEntities.getNext();


	EntityPtr hero = createHero(R"(../Animations/Hero)");
	hero->reset(Point(background.size().width / 35, background.size().height * 2 / 3));
	
	auto lives = CreateLives(R"(../Animations/heart.png)", Point(background.size().width * 95 / 100, background.size().height * 1 / 17));

	auto score = CreateScore(1.2, FONT_HERSHEY_SIMPLEX);
	score->reset(Point(background.size().width * 1 / 15, background.size().height * 1 / 10));

	Timer timer(/*freq. ms=*/100);
	timer.Register(slime);
	timer.Register(hero);

	std::srand(std::time(0));



	bool isToExit = false;
	while (false == isToExit)
	{
		Mat canvas = background.clone();
		auto inUse = slimeEntities.getPool();
		for (int i = 0; i < inUse.size(); i++)
		{
			bool is_collision = hero->checkCollision(*inUse[i]);
			if (is_collision) {
				hero->reset(Point{ hero->getTL().x - 50,hero->getTL().y });
				int randomPlace = std::rand() % (canvas.size().width - inUse[i]->getSize().x);
				inUse[i]->reset(Point{ randomPlace,inUse[i]->getTL().y });
			}
		}
		timer.tick();
		slimeEntities.draw(canvas);
		hero->draw(canvas);
		lives->draw(canvas);
		score->draw(canvas);
		imshow("test", canvas);
	}

	return 0;
}
