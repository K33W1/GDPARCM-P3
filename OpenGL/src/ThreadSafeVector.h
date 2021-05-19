#pragma once
#include <vector>
#include <mutex>

template <typename T>
class ThreadSafeVector
{
public:
	ThreadSafeVector<T>();
	~ThreadSafeVector();

	void push_back(T t);
	void remove(T t);
	void clear();

	unsigned int size();

	T operator[](unsigned int index);

private:
	std::vector<T> vector;
	std::mutex mutex;
};
