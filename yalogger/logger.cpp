//
//  logger.cpp
//  logger
//
//  Created by Dmitry Danilov on 08.08.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#include "logger.h"
#include "logger_exception.h"
#include "file_options.h"
#include <thread>
#include <sstream>
#include <fstream>
#include <boost/date_time.hpp>

namespace ya {

logger::logger(const file_options& fo, const LEVEL& log_level) : m_pimpl(new logger_impl(fo, log_level)) {
}

void logger::log(LEVEL level, const char_t* message) {
    m_pimpl->log(level, message);
}

void logger::close() {
    m_pimpl->close();
}

}
