n = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(n-1):
    u,v,cost = map(int,input().split())
    adj[u].append((v,cost))

dp = [-1]*(n+1)
longest = 0
def dfs(u):
    global dp,longest
    dp[u] = 0
    first,second = 0,-1
    for v,cost in adj[u]:
        if dp[v] == -1:
            dfs(v)
        cost += dp[v]
        if cost > first:
            second = first
            first = cost
        elif cost > second:
            second = cost

    dp[u] = first
    if second != -1:
        longest = max(longest,first+second)

dfs(1)
print(max(dp[1],longest))

