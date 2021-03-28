//
// Created by Mengwen Li (ml4643) on 3/14/2021.
//

#ifndef MAIN_MEMTABLE_QUEUE_H
#define MAIN_MEMTABLE_QUEUE_H

#include <deque>
#include <future>
#include <memory>
#include <optional>
#include <string_view>

#include "memtable.h"

using namespace std;

namespace projectdb {

class SSTableIndex;

/**
* The MemTableQueue holds a queue for objects of class MemTable.
* It maintains the order the MemTables are flushed to disk
* when executing concurrent threads.
*/
class MemTableQueue {
   public:
    MemTableQueue();
    // https://abseil.io/tips/1
    [[nodiscard]] optional<string> get(string_view key) const;
    // TODO: @mli: set and remove will return an optional of future<>.
    // https://stackoverflow.com/questions/14222899/exception-propagation-and-stdfuture
    [[nodiscard]] optional<future<SSTableIndex>> set(string_view key,
                                                     string_view value);
    [[nodiscard]] optional<future<SSTableIndex>> remove(string_view key);

    /**
     * NOTE: @mli:
     * It is possible that we have multiple futures in queue (although this is
     * highly unlikely), when we call future.wait(0) for the first future, if it
     * indicates that it's not ready, we should NOT do the check for the other
     * futures, even if it's possible that the other futures have finished. This
     * is because the MemTable and SSTableIndex queue has a strict order. We
     * have to ALWAYS remove from the begining and add in the end.
     */
    void pop();

   private:
    deque<MemTable> m_queue;

    [[nodiscard]] optional<future<SSTableIndex>> tryLaunchFlushToDisk(
        const MemTable& memTable);
};

}  // namespace projectdb

#endif  // MAIN_MEMTABLE_QUEUE_H
