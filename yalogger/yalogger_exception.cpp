//
//  yalogger_exception.cpp
//  yalogger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#include "yalogger_exception.h"

#include <exception>

class yalogger_exception : public std::runtime_error {
    
public:
    yalogger_exception(const char* msg) : std::runtime_error(msg){}
};