#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <functional>
#include <atomic>
#include <iostream>

class LogInterface {
public:
  virtual ~LogInterface() {}

  virtual void Warn(const std::string& data) = 0;
  virtual void Error(const std::string& data) = 0;
  virtual void Info(const std::string& data) = 0;
  virtual void Debug(const std::string& data) = 0;
};

class Log {
public:
  using OutMessageType = std::function<void(const std::string&)>;
  enum Level {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
  };
  static Log* Instance() {
    static Log single;
    return &single;
  }

  static Log& Out(Level level) {
    Instance()->current_level_ = level;
    return *Instance();
  }

  static void ToHex(std::string& message, const char* data, unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
      char buf[8];
      std::sprintf(buf, " 0x%x ", (unsigned char)data[i]);
      message += buf;
    }
  }

  void RegisterInterface(LogInterface* handle) {
    handle_ = handle;
    funcs_[DEBUG] = std::bind(&LogInterface::Debug, handle_, std::placeholders::_1);
    funcs_[INFO] = std::bind(&LogInterface::Info, handle_, std::placeholders::_1);
    funcs_[WARN] = std::bind(&LogInterface::Warn, handle_, std::placeholders::_1);
    funcs_[ERROR] = std::bind(&LogInterface::Error, handle_, std::placeholders::_1);
  }

  void Warn(const std::string& data) {
    if (handle_)
      handle_->Warn(data);
    else
      std::cout << data << std::endl;
  }

  void Warn(const std::string&& data) {
    if (handle_)
      handle_->Warn(data);
    else
      std::cout << data << std::endl;
  }

  void Debug(const std::string& data) {
    if (handle_)
      handle_->Debug(data);
    else
      std::cout << data << std::endl;
  }

  void Debug(const std::string&& data) {
    if (handle_)
      handle_->Debug(data);
    else
      std::cout << data << std::endl; 
  }

  void Info(const std::string& data) {
    if (handle_)
      handle_->Info(data);
    else
      std::cout << data << std::endl;
  }

  void Info(const std::string&& data) {
    if (handle_)
      handle_->Info(data);
    else
      std::cout << data << std::endl;
  }

  void Error(const std::string& data) {
    if (handle_)
      handle_->Error(data);
    else
      std::cout << data << std::endl;
  }

  void Error(const std::string&& data) {
    if (handle_)
      handle_->Error(data);
    else
      std::cout << data << std::endl;
  }

  void write(Level level, std::string& data) {
    if ((handle_) && (level <= ERROR) && (level >= DEBUG)) {
      funcs_[level](data);
    } else {
      std::cout << data;
    }
  }

  void write(Level level, std::string&& data) {
    if ((handle_) && (level <= ERROR) && (level >= DEBUG)) {
      funcs_[level](data);
    } else {
      std::cout << data;
    }
  }

  Log& operator << (std::string& str) {
    write(current_level_, str);
    return *Instance();
  }

  Log& operator << (std::string&& str) {
    write(current_level_, str);
    return *Instance();
  }

private:
  Log() : handle_(nullptr) {}

  LogInterface* handle_;
  OutMessageType funcs_[ERROR + 1];

  std::atomic<Level> current_level_;
};

#endif
