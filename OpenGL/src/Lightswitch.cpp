#include "Lightswitch.h"

Lightswitch::Lightswitch()
	: sharedSemaphore(1), counterSemaphore(1), prioritySemaphore(1)
{
	counter = 0;
}

Lightswitch::~Lightswitch()
{
	
}

void Lightswitch::sharedLock()
{
	sharedSemaphore.acquire();
	counterSemaphore.acquire();
	if (++counter == 1)
	{
		prioritySemaphore.acquire();
	}
	counterSemaphore.release();
	sharedSemaphore.release();
}

void Lightswitch::sharedUnlock()
{
	counterSemaphore.acquire();
	if (--counter == 0)
	{
		prioritySemaphore.release();
	}
	counterSemaphore.release();
}

void Lightswitch::priorityLock()
{
	sharedSemaphore.acquire();
	prioritySemaphore.acquire();
}

void Lightswitch::priorityUnlock()
{
	prioritySemaphore.release();
	sharedSemaphore.release();
}
