#pragma once
#include <mutex>
#include <queue>

template <typename T>
class ConcurrentQueue final
{

private:
	std::mutex mut;
	std::queue<sp<T>> queue;

public:

	ConcurrentQueue() = default;
	~ConcurrentQueue() = default;

	void enqueueCopy(sp<T>& toCopy);
	sp<T> dequeueCopy();
};

template <typename T>
sp<T> ConcurrentQueue<T>::dequeueCopy()
{
	std::lock_guard<std::mutex> lock(mut);

	if (queue.empty())
	{
		return nullptr;
	}

	sp<T>& result = queue.front();
	queue.pop();
	return result;
}

template <typename T>
void ConcurrentQueue<T>::enqueueCopy(sp<T>& toCopy)
{
	std::lock_guard<std::mutex> lock(mut);
	queue.push(toCopy);
}


