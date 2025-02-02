#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

/**
 * @class ThreadPool
 * @brief �X���b�h�v�[�����Ǘ�����N���X
 */
class ThreadPool {
public:
    /**
     * @brief �R���X�g���N�^�i�X���b�h�v�[�����������j
     * @param numThreads �X���b�h��
     */
    explicit ThreadPool(size_t numThreads);

    /**
     * @brief �f�X�g���N�^�i�X���b�h�����S�ɏI���j
     */
    ~ThreadPool();

    /**
     * @brief �^�X�N���X���b�h�v�[���ɒǉ�
     * @param task ���s����֐��i�����_����֐��|�C���^�j
     */
    void enqueueTask(std::function<void()> task);

private:
    /**
     * @brief ���[�J�[�X���b�h�����s����֐�
     */
    void workerThread();

    std::vector<std::thread> workers; ///< ���[�J�[�X���b�h�̃��X�g
    std::queue<std::function<void()>> tasks; ///< �^�X�N�L���[
    std::mutex queueMutex; ///< �^�X�N�L���[�̕ی�p�~���[�e�b�N�X
    std::condition_variable condition; ///< �^�X�N�ҋ@�p�̏����ϐ�
    bool stop; ///< �X���b�h�v�[����~�t���O
};

#endif // THREADPOOL_H
