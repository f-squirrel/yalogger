//
//  writer.cpp
//  yalogger
//
//  Created by Dmitry Danilov on 14.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#include "writer.h"
#include "logger_exception.h"
//#include <iostream>

namespace ya {

writer::writer(const file_options& options, message_queue_ptr_t queue, std::shared_ptr<flag_t> finish) :
    m_queue(queue), m_finish(finish) {
    m_ofstream.open(options.filename().c_str(), options.mode());
    if (!m_ofstream.is_open()) {
        throw logger_exception("Failed to open file");
    }
    std::cout << "current queue is lock-free?: " << std::boolalpha << m_queue->is_lock_free() << std::endl;
}

void writer::operator()() {
    while(!(*m_finish)) {
        char* value = nullptr;
        while(m_queue->pop(value)) {
            //std::cout << value << std::endl;
            m_ofstream << value << std::endl;
            m_ofstream.flush();
            delete[] value;
            value = nullptr;
        }
    }
    if (!m_options.is_stop_immediately()) {
        char*  value = nullptr;
        while(m_queue->pop(value)) {
            //std::cout << value << std::endl;
            m_ofstream << value << std::endl;
            m_ofstream.flush();
            delete [] value;
            value = nullptr;
        }
    }
    close();
    delete this;
}

void writer::close() {
    std::cout << "close writer\n";
    m_ofstream.close();
}

writer::~writer() {
    if(m_ofstream.is_open()) {
        close();
    }
}
}