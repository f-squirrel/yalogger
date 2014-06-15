//
//  defs.h
//  yalogger
//
//  Created by Dmitry Danilov on 13.09.13.
//  Copyright (c) 2013 Dmitry Danilov. All rights reserved.
//

#ifndef yalogger_defs_h
#define yalogger_defs_h

#include <string>
#include <fstream>

namespace ya {

enum LEVEL {
    Debug   = 0x0,
    Info    = 0x1,
    Warning = 0x2,
    Error   = 0x4
};

#if defined (WIN32) && defined(UNICODE)
typedef wchar_t char_t;
#define TEXT(quote) L##quote
#define __snprintf swprintf
#define __strlen wcslen
#else
typedef char char_t;
#define TEXT(quote) quote
#define __snprintf snprintf
#define __strlen strlen
#endif

typedef std::basic_string<char_t> string_t;
typedef std::basic_ofstream<char_t> ofstream_t;
    
}

#endif
