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
    
char* format_message(LEVEL level, const char* message) {
    using namespace boost::posix_time;
    char* level_str = nullptr;
    switch (level) {
        case Debug:
            level_str = const_cast<char*>("DEBUG");
            break;
        case Info:
            level_str = const_cast<char*>("INFO");
            break;
        case Warning:
            level_str = const_cast<char*>("WARNING");
            break;
        case Error:
            level_str = const_cast<char*>("ERROR");
            break;
        default:
            level_str = const_cast<char*>("UNKNOWN");
            break;
    }
    ptime timesatmp =  microsec_clock::local_time();
    std::string time_str = to_iso_extended_string(timesatmp);
    
    char* out_message = new char[ strlen(level_str) + strlen(message) + time_str.length() +  50 ];
    sprintf(out_message, "%s %s  %s", time_str.c_str(), level_str, message);
    return  out_message;
}

logger::logger(const file_options& fo, const LEVEL& log_level) :
    m_min_level(log_level),
    m_message_queue(1024) {

    if (fo.filename().empty()) {
        throw logger_exception("Failed to init logger: empty filename");
    }
    m_finish = std::make_shared<flag_t>(false);
    ya::writer* writer = new ya::writer(fo, m_message_queue, m_finish);
    m_thread_g.set_thread(std::thread(std::ref(*writer)));
}

logger::~logger() {
    std::cout << "dtor logger\n";
    if (!(*m_finish)) {
        close();
    }
}

void logger::close() {
    log(Info, "finishing");
    *m_finish = true;
}

void logger::log(LEVEL level, const char_t* message) {
    if (level < m_min_level) {
        return;
    }
    char* formatted_msg = format_message(level, message);
    send_msg_to_writer(formatted_msg);
}

void logger::send_msg_to_writer(char* message) {
    if (!message) {
        return;
    }
    m_message_queue.push(message);
}
}
