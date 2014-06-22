//
//  writer.cpp
//  yalogger
//
//  Created by Dmitry Danilov on 14.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#include "writer.h"
#include "logger_exception.h"

namespace ya {

writer::writer(const file_options& options, message_queue_ptr_t queue, flag_ptr_t finish) :
    m_queue(queue), m_finish(finish) {
    m_ofstream.open(options.filename().c_str(), options.mode());
    if (!m_ofstream.is_open())
        throw logger_exception("Failed to open file");
}

void writer::operator()() {
    while(!(*m_finish)) {
        char_t* value = nullptr;
        while(m_queue->pop(value)) {
            m_ofstream << value << std::endl;
            m_ofstream.flush();
            delete[] value;
            value = nullptr;
        }
    }
    char_t* value = nullptr;
    while(m_queue->pop(value)) {
        if (!m_options.is_stop_immediately()) {
            m_ofstream << value << std::endl;
            m_ofstream.flush();
        }
        delete [] value;
        value = nullptr;
    }
    close();
    delete this;
}

void writer::close() {
    m_ofstream.close();
}

writer::~writer() {
    if(m_ofstream.is_open())
        close();
}
}