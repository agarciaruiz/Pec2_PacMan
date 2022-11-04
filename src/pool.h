#ifndef POOL_H
#define POOL_H
#include <list>

template<typename T>
class Pool
{
private:
	std::list<T*> pooledObjects{};
public:
	T* Pool::GetItem()
	{
		if (pooledObjects.empty())
		{
			T* obj = new T();
			return obj;
		}
		else
		{
			T* obj = pooledObjects.front();
			pooledObjects.pop_front();
			return obj;
		}
	}

	void Pool::ReturnItem(T* obj)
	{
		pooledObjects.push_back(obj);
	}
};

#endif