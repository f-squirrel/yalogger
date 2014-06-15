//
//  impl.cpp
//  yalogger
//
//  Created by Dmitry Danilov on 15.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#include "impl.h"
#include "logger_exception.h"
#include "file_options.h"
#include "writer.h"
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

logger_impl::logger_impl(const file_options& fo, const LEVEL& log_level) :
    m_min_level(log_level),
    m_finish(std::make_shared<flag_t>(false)),
    m_message_queue(std::make_shared<message_queue_t>(1024))
{
    if (fo.filename().empty()) {
        throw logger_exception("Failed to init logger_impl: empty filename");
    }
    ya::writer* writer = new ya::writer(fo, m_message_queue, m_finish);
    m_thread_g.set_thread(std::thread(std::ref(*writer)));
}

logger_impl::~logger_impl() {
    std::cout << "dtor logger_impl\n";
    if (!(*m_finish)) {
        close();
    }
}

void logger_impl::log(LEVEL level, const char_t* message) {
    if (level < m_min_level) {
        return;
    }
    char* formatted_msg = format_message(level, message);
    send_msg_to_writer(formatted_msg);
}

void logger_impl::send_msg_to_writer(char* message) {
    if (!message) {
        return;
    }
    m_message_queue->push(message);
}

void logger_impl::close() {
    log(Info, "finishing");
    *m_finish = true;
}
    
}
