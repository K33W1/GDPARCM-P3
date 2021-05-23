#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(const std::string& name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	for (int i = 0; i < this->numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::onFinished(int threadID)
{
	if (this->activeThreads[threadID] != nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);
		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}

void ThreadPool::run()
{
	while (this->running)
	{
		if (!this->pendingActions.empty())
		{
			if (!this->inactiveThreads.empty())
			{
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				this->pendingActions.pop();
				workerThread->start();
			}
			// else std::cout << "[ThreadPool " << this->name << "] No more available worker threads!\n";
		}
		// else std::cout << "[ThreadPool " << this->name << "] No pending actions!\n";
	}
}