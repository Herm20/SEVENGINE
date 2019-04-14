#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include "Types.h"
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>

#include "JobObject.h"
#include "JobCallable.h"

class JobManager
{
private:
	boost::lockfree::queue<JobObject, boost::lockfree::capacity<256>> jobs;
	boost::thread* threads;
	u64 count;

	inline void InitThreads()
	{
		for (u64 i = 0; i < boost::thread::hardware_concurrency(); ++i)
		{
			jobs.push(JobObject('X'));
		}

		JobCallable proto;

		for (u64 i = 0; i < count; ++i)
		{
			threads[i] = boost::thread(proto, char(i + 65), boost::ref(jobs));
		}
	}

public:
	JobManager();
	JobManager(u64 threadPoolSize);
	~JobManager();
};

#endif
