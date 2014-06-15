//
//  concurrent_queue.h
//  logger
//
//  Created by Dmitry Danilov on 03.09.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef logger_concurrent_queue_h
#define logger_concurrent_queue_h

#include <queue>
#include <thread>
#include <mutex>

namespace ya {
namespace utils {

template<typename Data>
class concurrent_queue {
private:
    std::queue<Data> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition_variable;
public:
    void push(Data const& data) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_mutex.unlock();
        m_condition_variable.notify_one();
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
    
    bool try_pop(Data& popped_value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_queue.empty())
        {
            return false;
        }
        
        popped_value=m_queue.front();
        m_queue.pop();
        return true;
    }
    
    void wait_and_pop(Data& popped_value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        while(m_queue.empty()) {
            m_condition_variable.wait(lock);
        }
        
        popped_value=m_queue.front();
        m_queue.pop();
    }
};

} //utils
} // ya

#endif
