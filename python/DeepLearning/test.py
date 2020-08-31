import git

#repo = Repo(self.rorepo.working_tree_dir)
repo = git.Repo(r'../private_file')
print(repo.bare)

if repo.bare:
  new_repo = git.Repo.clone_from(url='http://git.code.oa.com/v_wacwang/private_file.git', to_path='../private_file')
else:
  new_repo = git.Repo(r'../private_file')

repo_branch = new_repo.git.branch('-r')
remote_branches = []
for index in repo_branch.split('\n'):
  print(index)
  remote_branches.append(index)

head = new_repo.head
print(head)



print(remote_branches)