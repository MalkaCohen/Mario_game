#pragma once
#include "Graphics.h"
#include "Physics.h"
#include "Observer.h"
class EntityState:public Subject
{
protected:
	IGraphicsComponentPtr _graphicsPtr;
	IPhysicsComponentPtr _physicsPtr;
	std::map<Event, std::shared_ptr<EntityState>> _adjecentStates;

public:
	EntityState(IGraphicsComponentPtr graphics=nullptr, IPhysicsComponentPtr physics=nullptr);

	virtual void update();

	IPhysicsComponentPtr const& getPhysics() const;
	IGraphicsComponentPtr const& getGraphics() const;

	void addState(Event const& e, std::shared_ptr<EntityState> toWhere);
	virtual std::shared_ptr<EntityState> tryModifyState(Event const& e) const;

	virtual void reset(cv::Point const& TL);

	void draw(cv::Mat & canvas);
};
typedef std::shared_ptr<EntityState> EntityStatePtr;


class Entity : public IObserver
{
protected:
	EntityStatePtr _state;

public:
	Entity(EntityStatePtr state);

	// Inherited via IObserver
	virtual void onNotify(Event const& e) override;
	virtual void reset(cv::Point const& TL);
	void draw(cv::Mat& canvas);

	//???
	EntityStatePtr getState();

	bool checkCollision(Entity entity);
	cv::Point getTL();
	cv::Point getSize();
};
typedef std::shared_ptr<Entity> EntityPtr;