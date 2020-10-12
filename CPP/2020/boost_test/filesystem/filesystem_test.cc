#include <iostream>
#include <boost/filesystem.hpp>

//using namespace boost::filesystem;

int main() {
  std::string _file_path = "../";
  std::string file_name = "file.txt";
  boost::filesystem::path file_path(_file_path);
  std::string full_file_path = (file_path/file_name).string();

  std::cout << full_file_path.empty() << std::endl;
  std::cout << "system_complete: " << boost::filesystem::system_complete(full_file_path) << std::endl;
  std::cout << "generic_string: " << file_path.generic_string() << std::endl;
  return 0;
}