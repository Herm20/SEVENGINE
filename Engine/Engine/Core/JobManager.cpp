#include "JobManager.h"

JobManager::JobManager() :
	jobs(),
	threads(new boost::thread[boost::thread::hardware_concurrency()]),
	count(boost::thread::hardware_concurrency())
{
	InitThreads();
}

JobManager::JobManager(u64 threadPoolSize) :
	jobs(),
	threads(new boost::thread[threadPoolSize]),
	count(threadPoolSize)
{
	InitThreads();
}

JobManager::~JobManager()
{
	delete[] threads;

	// Destroy the threads and whatnot
}
