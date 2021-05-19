#include "ThreadSafeVector.h"
#include <algorithm>

template <typename T>
ThreadSafeVector<T>::ThreadSafeVector()
{
	
}

template <typename T>
ThreadSafeVector<T>::~ThreadSafeVector()
{
	
}

template <typename T>
void ThreadSafeVector<T>::push_back(T t)
{
	mutex.lock();
	vector.push_back(t);
	mutex.unlock();
}

template <typename T>
void ThreadSafeVector<T>::remove(T t)
{
	mutex.lock();
	vector.erase(std::find(vector.begin(), vector.end(), t));
	mutex.unlock();
}

template <typename T>
void ThreadSafeVector<T>::clear()
{
	mutex.lock();
	vector.clear();
	mutex.unlock();
}

template <typename T>
unsigned ThreadSafeVector<T>::size()
{
	mutex.lock();
	int count = vector.size();
	mutex.unlock();
	return count;
}

template <typename T>
T ThreadSafeVector<T>::operator[](unsigned index)
{
	mutex.lock();
	T t = vector.at(index);
	mutex.unlock();
	return t;
}

class Scene;

template ThreadSafeVector<const Scene*>;
