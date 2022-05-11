#include <mutex>
#include <queue>
#include <thread>

#include "Logging/Logger.h"

class ThreadPool {
public:
	void Start();
	void QueueJob(const std::function<void()>& job);
	void Stop();

private:
	void ThreadLoop();

	bool should_terminate = false;           // Tells threads to stop looking for jobs
	std::mutex queue_mutex;                  // Prevents data races to the job queue
	std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> jobs;
	//std::vector<std::function<void()>> jobs;
};

inline void ThreadPool::Start() {
	const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports
	threads.resize(num_threads);
	for (uint32_t i = 0; i < num_threads; i++) {
		//threads.at(i) = std::thread([=] {ThreadLoop(); });
		threads.at(i) = std::thread([=] {this->ThreadLoop(); });
	}
}

inline void ThreadPool::ThreadLoop() {
	while (true) {
		std::function<void()> job;
		{
			std::unique_lock lock(queue_mutex);
			mutex_condition.wait(lock, [this] {
				return !jobs.empty() || should_terminate;
				});
			if (should_terminate) {
				return;
			}
			job = jobs.front();
			jobs.pop();
		}
		//for(int i = 0;i<jobs.size();i++)
		//{
		//	std::function<void()> job = jobs[i];
		//	job();
		//}
	}
}

inline void ThreadPool::QueueJob(const std::function<void()>& job) {
	{
		std::unique_lock lock(queue_mutex);
		jobs.push(job);
		//jobs.push_back(job);
	}
	mutex_condition.notify_one();
}

inline void ThreadPool::Stop() {
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		should_terminate = true;
	}
	mutex_condition.notify_all();
	for (std::thread& active_thread : threads) {
		active_thread.join();
	}
	threads.clear();
}