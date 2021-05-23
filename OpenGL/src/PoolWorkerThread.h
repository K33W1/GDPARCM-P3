#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	int getThreadID();

	void assignTask(IWorkerAction* action);

private:
	void run() override;

	IWorkerAction* workerAction;
	IFinishedTask* finishedTask;

	int id = 0;
};