#include "PoolWorkerThread.h"
#include "IWorkerAction.h"
#include "IFinishedTask.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask)
{
	this->id = id;
	this->finishedTask = finishedTask;
}

PoolWorkerThread::~PoolWorkerThread()
{

}

int PoolWorkerThread::getThreadID()
{
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action)
{
	this->workerAction = action;
}

void PoolWorkerThread::run()
{
	this->workerAction->onStartTask();
	this->finishedTask->onFinished(this->id);
}