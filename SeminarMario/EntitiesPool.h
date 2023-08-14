#pragma once

#include "Entities.h"
#include <vector>

// Object Pool Design Pattern
using namespace std;
class EntitiesPool
{
private:
	vector<EntityPtr> _pool;
	vector<bool> _isInUse;

public:
	EntitiesPool();

	void insert(EntityPtr whom);

	// throws exception if all entities are in use.
	EntityPtr getNext();
	void returnEntity(EntityPtr toFree);
	void draw(cv::Mat canvas);
	vector<EntityPtr> getPool();
};


