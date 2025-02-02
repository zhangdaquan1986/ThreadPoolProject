#include "ThreadPool.h"
#include <iostream>

/**
 * @brief �R���X�g���N�^
 * @param numThreads �X���b�h��
 */
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(&ThreadPool::workerThread, this);
    }
}

/**
 * @brief �f�X�g���N�^
 */
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();

    for (std::thread &worker : workers) {
        worker.join();
    }
}

/**
 * @brief �^�X�N��ǉ�����
 * @param task ���s����֐��i�����_����֐��|�C���^�j
 */
void ThreadPool::enqueueTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

/**
 * @brief ���[�J�[�X���b�h�̎��s�֐�
 */
void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) return;

            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
