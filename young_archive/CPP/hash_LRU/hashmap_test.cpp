#include <iostream>
#include <string>
#include "hashmap.h"

int main() {
  std::list<std::pair<int, std::string>> mylist = { {1, "fuck"},
                                                    {2, "shit"},
                                                    {3, "cao"},
                                                    {4, "ni"},
                                                    {5, "ma"} };
  
  std::list<std::pair<int, std::string>> mylist_V = { {1, "wo"},
                                                      {2, "shi"},
                                                      {3, "shuai"},
                                                      {4, "bi"},
                                                      {5, "ya"} };
  HashMap<int, std::string> hashmap = { {1, "fuck"},
                                        {2, "shit"},
                                        {3, "cao"},
                                        {4, "ni"},
                                        {5, "ma"} };

  std::cout << hashmap.at(1) << std::endl;
  std::cout << hashmap.at(2) << std::endl;
  std::cout << hashmap.at(3) << std::endl;
}