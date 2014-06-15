//
//  logger.h
//  logger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef __logger__logger__
#define __logger__logger__

#include "impl.h"
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
    ~logger() = default;
    void log(LEVEL level, const char_t* message);
    void close();
    
    logger(const logger& ) = delete;
    logger& operator = (const logger&) = delete;
private:
    std::unique_ptr<logger_impl> m_pimpl;
};

}


#endif /* defined(__logger__logger__) */
