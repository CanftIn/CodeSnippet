bool isPalindromeNumber(int num)
{
    int oldNum = num;
    int newNum = 0;
    while(oldNum > 0)
    {
        newNum = newNum * 10 + oldNum % 10;
        oldNum = oldNum / 10;
    }
    if(num == newNum)
        return true;
    else
        return false;
}