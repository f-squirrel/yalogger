//
//  scoped_thread_guard.h
//  logger
//
//  Created by Dmitry Danilov on 09.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef logger_scoped_thread_guard_h
#define logger_scoped_thread_guard_h

#include "logger_exception.h"
#include <thread>

namespace ya {

class scoped_thread_guard {
    std::thread m_thread;
public:
    void set_thread(std::thread t) {
        m_thread = std::move(t);
        if( !m_thread.joinable() ) {
            throw logger_exception("Thread is not joinable");
        }
    }
    ~scoped_thread_guard() {
        m_thread.join();
    }
};
    
}
#endif
