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
#include "Config.h"

using namespace cv;

/////////////////////////////////
	
int main()
{
	Mat background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
	resize(background, background, Size(SCREEN_WIDTH,SCREEÉ_HEIGHT));

	auto slime = CreateSlimeEnemy(R"(../Animations/SlimeOrange)");
	slime->reset(Point(SCREEN_WIDTH / 35, DEFAULT_SILME_Y));
	
	EntitiesPool slimeEntities;
	slimeEntities.insert(slime);
	auto slime1=slimeEntities.getNext();


	EntityPtr hero = createHero(R"(../Animations/Hero)");
	hero->reset(Point(DEFAULT_HERO_X, DEFAULT_HERO_Y));
	
	auto lives = CreateLives(R"(../Animations/heart.png)", Point(DEFAULT_LIVES_X, DEFAULT_LIVES_Y));

	auto score = CreateScore(/*fontScale*/1.2, FONT_HERSHEY_SIMPLEX);
	score->reset(Point(DEFAULT_SCORE_X, DEFAULT_SCORE_Y));

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
				hero->reset(Point{ hero->getTL().x - 50,DEFAULT_HERO_Y});
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
