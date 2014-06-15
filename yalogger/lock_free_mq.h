//
//  lock_free_mq.h
//  yalogger
//
//  Created by Dmitry Danilov on 14.06.14.
//  Copyright (c) 2014 Dmitry Danilov. All rights reserved.
//

#ifndef yalogger_lock_free_mq_h
#define yalogger_lock_free_mq_h

#include "defs.h"
#include <atomic>
#include <memory>
#include <boost/lockfree/queue.hpp>

namespace ya {
typedef boost::lockfree::queue<char_t*> message_queue_t;
typedef std::atomic<bool> flag_t;
typedef std::shared_ptr<flag_t> flag_ptr_t;
}

#endif
