#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <string>
#include <vector>
#include <stdio.h>
#include <boost/filesystem.hpp>

class FileIO {
public:
  // Create one directory if not exist.
  static bool CreateDir(const std::string &path);
  // Create one directory forcibly, if exist, delete origin directory and create one empty folder.
  static bool ReCreateDir(const std::string &path);
  // Delete one folder and files within
  static bool DeleteDir(const std::string &path);
  // Check if one directory (not file) is exist.
  static bool CheckDir(const std::string &path);
  // Check if one file exist or not.
  static bool CheckFile(const std::string &file_path);
  // Get all files of current folder path, ignore sub-folder
  static void GetFileList(const std::string &path, std::vector<std::string> *file_list);
  // Get all files of current folder recursively, including files in sub-folder.
  static void GetFileListRecur(const std::string &path, std::vector<std::string> *file_list);
};

#endif