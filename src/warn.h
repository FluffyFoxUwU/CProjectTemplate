#ifndef _headers_1675087294_CProjectTemplate_warn
#define _headers_1675087294_CProjectTemplate_warn

#include <stdio.h>
#include <stdlib.h>

// Linux kernel style bug 

#include "logging/logging.h"

#define WARN() do { \
  pr_warn("WARN: at %s:%d/%s()!", __FILE__, __LINE__, __func__); \
} while(0)

#define WARN_ON(cond) do { \
  if (cond)  \
    WARN(); \
} while(0)

#endif

