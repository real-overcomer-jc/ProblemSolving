n = int(input())

board = []
for _ in range(n):
    board.append(list(map(int,input().split())))

INF = int(1e9)
dp = [[INF]*n for _ in range(n)]
for i in range(3):
    dp[0][i] = board[0][i]

for k in range(1,n):
    for i in range(3):
        for j in range(3):
            if i != j:
                dp[k][i] = min(dp[k][i],board[k][i]+dp[k-1][j])

print(min(dp[n-1]))


    
