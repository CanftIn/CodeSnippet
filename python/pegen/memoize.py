def memoize(func):
  def memoize_wrapper(self, *args):
    pos = self.mark()
    memo = self.memos.get(pos)
    if memo is None:
      memo = self.memos[pos] = {}
    key = (func, args)
    if key in memo:
      res, endpos = memo[key]
      self.reset(endpos)
    else:
      res = func(self, *args)
      endpos = self.mark()
      if res is None:
        assert endpos == pos
      else:
        assert endpos > pos
      memo[key] = res, endpos
    return res
  return memoize_wrapper