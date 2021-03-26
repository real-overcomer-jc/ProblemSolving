for _ in range(int(input())):
    n = int(input())
    dp = [-1]*(n+1)
    dp[0] = 1 
    if n > 0: dp[1] = 1
    if n > 1: dp[2] = 2
    for i in range(3,n+1):
        dp[i] = dp[i-1]+dp[i-2]+dp[i-3]
    print(dp[n])
