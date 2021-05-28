#pragma once
#include "Lightswitch.h"
#include <vector>

template <typename T>
class ThreadSafeVector
{
public:
	ThreadSafeVector<T>() = default;
	~ThreadSafeVector() = default;

	void manualPriorityLock();
	void manualPriorityUnlock();
	void manualSharedLock();
	void manualSharedUnlock();
	
	void push_back(T t);
	void remove(T t);
	void clear();
	void clearNoLock();

	size_t size();

	T& operator[](unsigned int index);

	std::vector<T>::iterator begin();
	std::vector<T>::iterator end();

private:
	Lightswitch lightswitch;
	std::vector<T> vector;
};

template <typename T>
void ThreadSafeVector<T>::manualPriorityLock()
{
	lightswitch.priorityLock();
}

template <typename T>
void ThreadSafeVector<T>::manualPriorityUnlock()
{
	lightswitch.priorityUnlock();
}

template <typename T>
void ThreadSafeVector<T>::manualSharedLock()
{
	lightswitch.sharedLock();
}

template <typename T>
void ThreadSafeVector<T>::manualSharedUnlock()
{
	lightswitch.sharedUnlock();
}

template <typename T>
void ThreadSafeVector<T>::push_back(T t)
{
	lightswitch.priorityLock();
	vector.push_back(t);
	lightswitch.priorityUnlock();
}

template <typename T>
void ThreadSafeVector<T>::remove(T t)
{
	lightswitch.priorityLock();
	vector.erase(std::find(vector.begin(), vector.end(), t));
	lightswitch.priorityUnlock();
}

template <typename T>
void ThreadSafeVector<T>::clear()
{
	lightswitch.priorityLock();
	vector.clear();
	lightswitch.priorityUnlock();
}

template <typename T>
void ThreadSafeVector<T>::clearNoLock()
{
	vector.clear();
}

template <typename T>
size_t ThreadSafeVector<T>::size()
{
	lightswitch.sharedLock();
	size_t count = vector.size();
	lightswitch.sharedUnlock();
	
	return count;
}

template <typename T>
T& ThreadSafeVector<T>::operator[](unsigned index)
{
	lightswitch.sharedLock();
	T& t = vector.at(index);
	lightswitch.sharedUnlock();
	
	return t;
}

template <typename T>
typename std::vector<T>::iterator ThreadSafeVector<T>::begin()
{
	return vector.begin();
}

template <typename T>
typename std::vector<T>::iterator ThreadSafeVector<T>::end()
{
	return vector.end();
}
