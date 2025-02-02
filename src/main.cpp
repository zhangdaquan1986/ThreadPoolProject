#include "ThreadPool.h"
#include <iostream>
#include <chrono>

/**
 * @brief メイン関数
 * @return プログラムの終了コード
 */
int main() {
    ThreadPool pool(4);  // 4スレッドのスレッドプールを作成

    // タスクを追加
    for (int i = 0; i < 10; ++i) {
        pool.enqueueTask([i] {
            std::cout << "Task " << i << " is running on thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "All tasks completed." << std::endl;

    return 0;
}
