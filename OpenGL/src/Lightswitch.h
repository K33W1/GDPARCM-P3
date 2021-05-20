#pragma once
#include <semaphore>

class Lightswitch
{
public:
	Lightswitch();
	~Lightswitch();

	void sharedLock();
	void sharedUnlock();
	void priorityLock();
	void priorityUnlock();

private:
	std::binary_semaphore sharedSemaphore;
	std::binary_semaphore counterSemaphore;
	std::binary_semaphore prioritySemaphore;
	unsigned int counter;
};
