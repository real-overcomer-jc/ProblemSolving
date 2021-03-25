for _ in range(int(input())):
    n = int(input())

    dp = [0]*(max(2,n+2))
    dp[n] = 1
    for i in range(n-1,0,-1):
        dp[i] = dp[i+1] + dp[i+2]

    if n > 1:
        dp[0] = dp[2]

    print(dp[0],dp[1])
