//
//  writer.h
//  yalogger
//
//  Created by Dmitry Danilov on 14.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#ifndef __yalogger__writer__
#define __yalogger__writer__

#include "defs.h"
#include "lock_free_mq.h"
#include "file_options.h"
namespace ya {
class file_options;
class writer {
public:
    writer(const file_options& options, message_queue_ptr_t queue, flag_ptr_t finish);
    ~writer();
    void operator()();
    writer(const writer&) = delete;
    writer& operator = (const writer&) = delete;
private:
    void close();
private:
    flag_ptr_t m_finish;
    message_queue_ptr_t m_queue;
    ofstream_t m_ofstream;
    file_options m_options;
};
}
#endif /* defined(__yalogger__writer__) */
