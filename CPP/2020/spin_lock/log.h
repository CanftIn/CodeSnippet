#ifndef __LOG_H__
#define __LOG_H__

#include <time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int shift_files(const char* log_base_name,
                long max_long_size,
                int max_log_num);

int tools_get_curr_data_time_str(char* time_str);

#ifndef __cpluscplus
int log_write_log(const char* log_base_name,
                  long max_long_size,
                  int max_log_num,
                  const char* format,
                  va_list ap,
                  bool need_time = true,
                  bool to_log_d = true);



#endif