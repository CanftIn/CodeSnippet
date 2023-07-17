def online():
    '''
    通过获取好友信息，判断用户是否还在线
    :return: True ，还在线，False 不在线了
    '''
    try:
        if itchat.search_friends():
            return True
    except:
        return False
    return True
