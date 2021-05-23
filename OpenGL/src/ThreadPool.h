#pragma once
#include "IETThread.h"
#include "IFinishedTask.h"
#include <string>
#include <queue>
#include <unordered_map>

class PoolWorkerThread;
class IWorkerAction;

class ThreadPool : public IFinishedTask, public IETThread
{
private:
	typedef std::queue<PoolWorkerThread*> ThreadList;
	typedef std::unordered_map<int, PoolWorkerThread*> ThreadMap;
	typedef std::queue<IWorkerAction*> ActionList;

public:
	ThreadPool(const std::string& name, int numWorkers);
	~ThreadPool();

	void startScheduler();
	void scheduleTask(IWorkerAction* action);
	void stopScheduler();

private:
	// Inherited via IFinishedTask
	virtual void onFinished(int threadID) override;

	// Inherited via IETThread
	virtual void run() override;

	ThreadMap activeThreads;
	ThreadList inactiveThreads;
	ActionList pendingActions;

	std::string name;
	int numWorkers = 0;
	bool running = false;
};