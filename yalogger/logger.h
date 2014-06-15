//
//  logger.h
//  logger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef __logger__logger__
#define __logger__logger__

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

//TODO:
// 1. implement loading file partially instaed of loading all file: to avoid loading over GB logs in memory
// 2. test with multiple user threads
// 3. add timestamp
// 4. add template

namespace ya {

class logger {
public:
    logger(const file_options& fo, const LEVEL& log_level);
    ~logger();
    void log(LEVEL level, const char_t* message);
    void close();
    
    logger(const logger& ) = delete;
    logger& operator = (const logger&) = delete;
private:
    void send_msg_to_writer(char_t* message);
private:
    message_queue_t m_message_queue;
    std::shared_ptr<flag_t> m_finish;
    scoped_thread_guard m_thread_g;
    LEVEL m_min_level;
};

}


#endif /* defined(__logger__logger__) */
