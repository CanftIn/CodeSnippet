import json
import os
import re
import requests

class Github(object):
  def __init__(self, username):
    self.__username = username
    self.headers = {
      'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.86 Safari/537.36',
    }
    self.__path = "./github_fold"
  
  # user info
  def get_user_info(self):
    url = 'https://api.github.com/users/' + self.__username
    resp = requests.get(url, headers=self.headers)
    #print(resp.text)
    file_path = self.__path + '/user_infomation.json'
    with open(file_path, 'w') as f:
      f.write(resp.text.encode('gbk', 'ignore').decode('gbk', 'ignore'))
    return file_path

  def get_user_repos_detail(self):
    url = 'https://api.github.com/users/' + self.__username + '/repos'
    resp = requests.get(url, headers=self.headers, verify=False, timeout=2)
    repo_detail = []
    for name in resp.json():
      repo_url = 'https://api.github.com/repos/' + self.__username + '/' + name['name']
      detail = requests.get(repo_url, headers=self.headers, verify=False, timeout=2)
      repo_detail.append(detail.text.encode("gbk", 'ignore').decode("gbk", "ignore"))
      print('正在下载仓库信息 >>> ', name['name'])
    print(repo_detail)
    file_path = self.__path + '/user_all_repos_detail.json'
    with open(file_path, 'w') as f:
      f.write(str(repo_detail))
    return file_path

if __name__ == "__main__":
  github = Github('canftin')
  github.get_user_info()
  github.get_user_repos_detail()
