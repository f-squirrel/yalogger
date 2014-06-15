//
//  logger_exception.h
//  logger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef __logger__logger_exception__
#define __logger__logger_exception__


#include <stdexcept>

namespace ya {
class logger_exception : public std::runtime_error {
public:
    explicit logger_exception(const char* msg) : std::runtime_error(msg) {}
};

}
#endif /* defined(__logger__logger_exception__) */
