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
 * @brief スレッドプールを管理するクラス
 */
class ThreadPool {
public:
    /**
     * @brief コンストラクタ（スレッドプールを初期化）
     * @param numThreads スレッド数
     */
    explicit ThreadPool(size_t numThreads);

    /**
     * @brief デストラクタ（スレッドを安全に終了）
     */
    ~ThreadPool();

    /**
     * @brief タスクをスレッドプールに追加
     * @param task 実行する関数（ラムダ式や関数ポインタ）
     */
    void enqueueTask(std::function<void()> task);

private:
    /**
     * @brief ワーカースレッドが実行する関数
     */
    void workerThread();

    std::vector<std::thread> workers; ///< ワーカースレッドのリスト
    std::queue<std::function<void()>> tasks; ///< タスクキュー
    std::mutex queueMutex; ///< タスクキューの保護用ミューテックス
    std::condition_variable condition; ///< タスク待機用の条件変数
    bool stop; ///< スレッドプール停止フラグ
};

#endif // THREADPOOL_H
