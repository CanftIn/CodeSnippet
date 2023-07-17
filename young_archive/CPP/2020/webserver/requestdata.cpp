#include "requestdata.h"
#include "utils.h"
#include "epoll.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/time.h>
#include <unordered_map>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <queue>

int requestData::parse_URI() {
  std::string& str = content;
  int pos = str.find('\r', now_read_pos);
  if (pos < 0) {
    return PARSE_URI_AGAIN;
  }
  std::string request_line = str.substr(0, pos);
  if (str.size() > pos + 1)
    str = str.substr(pos + 1);
  else
    str.clear();
  
  pos = request_line.find("GET");
  if (pos < 0)
  {
    pos = request_line.find("POST");
    if (pos < 0)
    {
      return PARSE_URI_ERROR;
    }
    else
    {
      method = METHOD_POST;
    }
  }
  else
  {
    method = METHOD_GET;
  }
}