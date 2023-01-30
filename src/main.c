#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <string.h>
#include <errno.h>

#include "logging/logging.h"
#include "util/util.h"

static atomic_bool shuttingDown = false;
static pthread_t loggerThread;

static void* logReader(void* v) {
  struct log_entry entry;
  while (!shuttingDown || logging_has_more_entry()) {
    logging_read_log(&entry);
    fprintf(stderr, "[%f] %s\n", entry.realtime, entry.message);
  }
  return NULL;
}

int main2(int argc, char** argv) {
  util_init();
  int res = 0;
  if ((res = util_thread_create(&loggerThread, NULL, logReader, NULL)) < 0) {
    fprintf(stderr, "Critical error: Cannot start log reader thread aborting: %s", strerror(-res));
    return -EFAULT;
  }
  
  util_set_thread_name(pthread_self(), "Main-Thread");
  
  pr_info("Hello World!\n");
  
  atomic_store(&shuttingDown, true);
  pr_info("Shutting down logger thread. Good bye UwU!");
  if (!logging_flush())
    pr_warn("Logging subsystem did not flush in time. Shutting down logging thread anyway");
  pthread_join(loggerThread, NULL);
  util_cleanup();
  return EXIT_SUCCESS;
}

