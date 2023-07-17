#include "file_io.h"

// Create one directory if not exist.
bool FileIO::CreateDir(const std::string &path) {
  if (CheckDir(path) == false) {
    printf("[INFO] will create folder [%s]\n", path.c_str());
    return boost::filesystem::create_directories(boost::filesystem::path(path));
  } else {
    printf("[INFO] folder already exist: [%s]\n", path.c_str());
    return true;
  }
}

// Create one directory forcibly, if exist, delete origin directory and create one empty folder.
bool FileIO::ReCreateDir(const std::string &path) {
  bool ret = true;
  if (ret) {
    if (CheckDir(path)) {
      printf("[INFO] folder[%s] already exist, delete first.\n", path.c_str());
      ret = boost::filesystem::remove_all(boost::filesystem::path(path));
    }
  }
  if (ret) {
    ret = boost::filesystem::create_directories(boost::filesystem::path(path));
  }
  return ret;
}

// Delete one folder and files within
bool FileIO::DeleteDir(const std::string &path) {
  if (CheckDir(path) == false) {
    printf("[INFO] path not exist: [%s]\n", path.c_str());
    return true;
  } else {
    return boost::filesystem::remove_all(boost::filesystem::path(path));
  }
}

// Check if one directory (not file) is exist.
bool FileIO::CheckDir(const std::string &path) {
  boost::filesystem::path bf_path(path);
  if (!boost::filesystem::exists(bf_path)) return false;
  if (!boost::filesystem::is_directory(bf_path)) return false;
  return true;
}

// Check if one file exist or not.
bool FileIO::CheckFile(const std::string &file_path) {
  boost::filesystem::path bf_path(file_path);
  if (!boost::filesystem::exists(bf_path)) return false;
  if (!boost::filesystem::is_regular_file(bf_path)) return false;
  return true;
}

// Get all files of current folder path, ignore sub-folder
void FileIO::GetFileList(const std::string &path, std::vector<std::string> *file_list) {
  if (CheckDir(path) == false) return;

  boost::filesystem::directory_iterator iter(path);
  boost::filesystem::directory_iterator end_iter;
  while (iter != end_iter) {
    if (boost::filesystem::is_regular_file(*iter)) {
      file_list->push_back(iter->path().string());
    }
    ++iter;
  }
}

// Get all files of current folder recursively, including files in sub-folder.
void FileIO::GetFileListRecur(const std::string &path, std::vector<std::string> *file_list) {
  if (CheckDir(path) == false) return;

  boost::filesystem::directory_iterator iter(path);
  boost::filesystem::directory_iterator end_iter;
  while (iter != end_iter) {
    if (boost::filesystem::is_directory(*iter)) {
      GetFileListRecur(iter->path().string(), file_list);
    } else {
      file_list->push_back(iter->path().string());
      ++iter;
    }
  }
}