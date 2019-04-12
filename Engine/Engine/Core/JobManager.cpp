#include "JobManager.h"

JobManager::JobManager() :
	jobs(),
	threads(new boost::thread[1]),
	count(1)
{
	// Setup the thread(s)
}

JobManager::JobManager(u64 threadPoolSize) :
	jobs(),
	threads(new boost::thread[threadPoolSize]),
	count(threadPoolSize)
{
	// Setup the thread(s)
}

JobManager::~JobManager()
{
	delete[] threads;

	// Destroy the threads and whatnot
}
