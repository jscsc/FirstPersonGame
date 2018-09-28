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

	void enqueue(sp<T>& toCopy);
	sp<T> dequeue();
};

template <typename T>
sp<T> ConcurrentQueue<T>::dequeue()
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
void ConcurrentQueue<T>::enqueue(sp<T>& toCopy)
{
	std::lock_guard<std::mutex> lock(mut);
	queue.push(toCopy);
}


