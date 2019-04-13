#ifndef JOB_CALLABLE_H_
#define JOB_CALLABLE_H_

#include <cstdio>
#include <boost/lockfree/queue.hpp>

// Temporary
#include <boost/chrono.hpp>
#include <random>

#include "JobObject.h"

struct JobCallable
{
	// Temporary test functionality
	void operator()(char identity, boost::lockfree::queue<JobObject, boost::lockfree::capacity<256>>& jobs)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(250 + std::rand() % 250));
		std::srand(identity);

		for (u64 i = 0; i < 4; ++i) // Make this a permanent loop with break condition for actual event handling
		{
			JobObject job;
			bool gotJob = jobs.pop(job);
			while (!gotJob) { gotJob = jobs.pop(job); }

			jobs.push(JobObject(identity));

			printf("%c - %c\n", identity, job.value);

			boost::this_thread::sleep_for(boost::chrono::milliseconds(std::rand() % 250));
		}
	}
};

#endif
