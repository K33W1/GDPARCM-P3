#pragma once
#include "Lightswitch.h"
#include <unordered_map>

template <typename Key, typename Value>
class ThreadSafeUnorderedMap
{
public:
	ThreadSafeUnorderedMap<Key, Value>() = default;
	~ThreadSafeUnorderedMap() = default;

	void manual_lock();
	void manual_unlock();
	
	void insert(const Key& key, const Value& value);
	void remove(const Key& key);
	void clear();

	Value at(const Key& key);
	Value& operator[](const Key& key);
	
	size_t size();
	bool doesExist(const Key& key);

	std::unordered_map<Key, Value>::iterator begin();
	std::unordered_map<Key, Value>::iterator end();

private:
	std::unordered_map<Key, Value> unorderedMap;
	Lightswitch lightswitch;
};

template <typename Key, typename Value>
void ThreadSafeUnorderedMap<Key, Value>::manual_lock()
{
	lightswitch.priorityLock();
}

template <typename Key, typename Value>
void ThreadSafeUnorderedMap<Key, Value>::manual_unlock()
{
	lightswitch.priorityUnlock();
}

template <typename Key, typename Value>
void ThreadSafeUnorderedMap<Key, Value>::insert(const Key& key, const Value& value)
{
	lightswitch.priorityLock();
	unorderedMap.insert({ key, value });
	lightswitch.priorityUnlock();
}

template <typename Key, typename Value>
void ThreadSafeUnorderedMap<Key, Value>::remove(const Key& key)
{
	lightswitch.priorityLock();
	unorderedMap.erase(key);
	lightswitch.priorityUnlock();
}

template <typename Key, typename Value>
void ThreadSafeUnorderedMap<Key, Value>::clear()
{
	lightswitch.priorityLock();
	unorderedMap.clear();
	lightswitch.priorityUnlock();
}

template <typename Key, typename Value>
Value ThreadSafeUnorderedMap<Key, Value>::at(const Key& key)
{
	lightswitch.sharedLock();
	Value value = unorderedMap.at(key);
	lightswitch.sharedUnlock();

	return value;
}

template <typename Key, typename Value>
Value& ThreadSafeUnorderedMap<Key, Value>::operator[](const Key& key)
{
	lightswitch.sharedLock();
	Value& value = unorderedMap[key];
	lightswitch.sharedUnlock();

	return value;
}

template <typename Key, typename Value>
size_t ThreadSafeUnorderedMap<Key, Value>::size()
{
	lightswitch.sharedLock();
	size_t count = unorderedMap.size();
	lightswitch.sharedUnlock();
	
	return count;
}

template <typename Key, typename Value>
bool ThreadSafeUnorderedMap<Key, Value>::doesExist(const Key& key)
{
	lightswitch.sharedLock();
	bool exist = unorderedMap.find(key) != unorderedMap.end();
	lightswitch.sharedUnlock();
	
	return exist;
}

template <typename Key, typename Value>
typename std::unordered_map<Key, Value>::iterator ThreadSafeUnorderedMap<Key, Value>::begin()
{
	return unorderedMap.begin();
}

template <typename Key, typename Value>
typename std::unordered_map<Key, Value>::iterator ThreadSafeUnorderedMap<Key, Value>::end()
{
	return unorderedMap.end();
}
