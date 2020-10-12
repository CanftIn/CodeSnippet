#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "file_io.h"
//using namespace boost::filesystem;

int main() {
  /*
  std::string _file_path = "../";
  std::string file_name = "file.txt";
  boost::filesystem::path file_path(_file_path);
  std::string full_file_path = (file_path/file_name).string();

  std::cout << full_file_path.empty() << std::endl;
  std::cout << "system_complete: " << boost::filesystem::system_complete(full_file_path) << std::endl;
  std::cout << "generic_string: " << file_path.generic_string() << std::endl;
  */
  std::vector<std::string> file_vec;
  FileIO::GetFileList("./", &file_vec);

  for_each(file_vec.begin(), file_vec.end(), [](std::string it){ std::cout << it << std::endl; });
  return 0;
}