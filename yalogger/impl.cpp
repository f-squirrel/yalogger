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
#include <fstream>
#include <boost/date_time.hpp>

namespace ya {

const char_t* get_level_string(LEVEL level) {
    switch (level) {
        case Debug:
            return TEXT("DEBUG");
        case Info:
            return TEXT("INFO");
        case Warning:
            return TEXT("WARNING");
        case Error:
            return TEXT("ERROR");
        default:
            return TEXT("UNKNOWN");
    }
}

char_t* format_message(LEVEL level, const char_t* message) {
    using namespace boost::posix_time;
    const char_t* level_str = get_level_string(level);
    const string_t& time_str = to_iso_extended_string_type<char_t>(microsec_clock::local_time());
    size_t len = __strlen(level_str) + __strlen(message) + time_str.length() +  50;
    char_t* out_message = new char_t[ len ];
    __snprintf(out_message, len - 1, "%s %s  %s", time_str.c_str(), level_str, message);
    return  out_message;
}

char_t* format_message(LEVEL level, const string_t& message) {
    using namespace boost::posix_time;
    const char_t* level_str = get_level_string(level);
    const string_t& time_str = to_iso_extended_string_type<char_t>(microsec_clock::local_time());
    size_t len = __strlen(level_str) + message.length() + time_str.length() +  50;
    char_t* out_message = new char_t[ len ];
    __snprintf(out_message, len - 1,  TEXT("%s %s  %s"), time_str.c_str(), level_str, message.c_str());
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

void logger_impl::log(LEVEL level, const string_t& message) {
    if (level < m_min_level) {
        return;
    }
    char_t* formatted_msg = format_message(level, message);
    send_msg_to_writer(formatted_msg);
}

void logger_impl::send_msg_to_writer(char* message) {
    if (!message) {
        return;
    }
    m_message_queue->push(message);
}

void logger_impl::close() {
    log(Info, TEXT("finishing"));
    *m_finish = true;
}
    
}
