for _ in range(int(input())):
    m = int(input())
    data = [list(map(int,input().split())) for _ in range(2)]

    dp = [[-1]*m for _ in range(2)]
    dp[0][0] = data[0][0]
    dp[1][0] = data[1][0]
    best = 0
    for i in range(1,m):
        dp[0][i] = data[0][i] + max(dp[1][i-1],dp[1][i-2])
        dp[1][i] = data[1][i] + max(dp[0][i-1],dp[0][i-2])
        best = max(dp[0][i],dp[1][i])

    print(best)
