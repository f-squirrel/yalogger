//
//  impl.h
//  yalogger
//
//  Created by Dmitry Danilov on 15.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#ifndef __yalogger__impl__
#define __yalogger__impl__

#include "scoped_thread_guard.h"
#include "file_options.h"
#include "lock_free_mq.h"
#include "writer.h"
#include <fstream>
#include <string>
#include <iostream>
#include <atomic>
#include <thread>
#include <memory>

namespace ya {
class logger_impl {
public:
    logger_impl(const file_options& fo, const LEVEL& log_level);
    ~logger_impl();
    void log(LEVEL level, const char_t* message);
    void close();
    
    logger_impl(const logger_impl& ) = delete;
    logger_impl& operator = (const logger_impl&) = delete;
private:
    void send_msg_to_writer(char_t* message);
private:
    message_queue_t m_message_queue;
    std::shared_ptr<flag_t> m_finish;
    scoped_thread_guard m_thread_g;
    LEVEL m_min_level;
};
}

#endif /* defined(__yalogger__impl__) */
