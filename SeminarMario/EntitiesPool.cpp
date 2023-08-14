#include "EntitiesPool.h"
EntitiesPool::EntitiesPool()
{
	_pool = std::vector<EntityPtr>();
	_isInUse = std::vector<bool>();
}

void EntitiesPool::insert(EntityPtr whom)
{
	_pool.push_back(whom);
	_isInUse.push_back(false);
}

EntityPtr EntitiesPool::getNext()
{
	auto it = std::find(_isInUse.begin(), _isInUse.end(), false);
	if (it != _isInUse.end()) {
		size_t index = std::distance(_isInUse.begin(), it);
		_isInUse[index] = true;
		return _pool[index];
	}
	throw std::runtime_error("all the entities are in use"); 
}

void EntitiesPool::returnEntity(EntityPtr toFree)
{
	auto it = std::find(_isInUse.begin(), _isInUse.end(), true);
	if (it != _isInUse.end()) {
		size_t index = std::distance(_isInUse.begin(), it);
		_isInUse[index] = false;
	}
	else {
		throw std::runtime_error("error");
	}
}

void EntitiesPool::draw(cv::Mat canvas)
{
	for (int i = 0; i < _pool.size(); i++)
	{
		if (_isInUse[i])
			_pool[i]->draw(canvas);
	}
}

vector<EntityPtr> EntitiesPool::getPool()
{
	vector<EntityPtr> inUse;
	for (int i = 0; i < _pool.size(); i++)
	{
		if (_isInUse[i])
			inUse.push_back(_pool[i]);
	}
	return inUse;
}




