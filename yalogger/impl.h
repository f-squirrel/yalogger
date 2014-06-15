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
#include "lock_free_mq.h"

namespace ya {
class file_options;
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
    message_queue_ptr_t m_message_queue;
    flag_ptr_t m_finish;
    scoped_thread_guard m_thread_g;
    LEVEL m_min_level;
};
}

#endif /* defined(__yalogger__impl__) */
