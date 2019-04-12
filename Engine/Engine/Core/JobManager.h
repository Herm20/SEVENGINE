#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include "Types.h"
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>

#include "JobObject.h"

class JobManager
{
private:
	boost::lockfree::queue<JobObject> jobs;
	boost::thread* threads;
	u64 count;

public:
	JobManager();
	JobManager(u64 threadPoolSize);
	~JobManager();
};

#endif
