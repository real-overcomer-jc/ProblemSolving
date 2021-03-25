import sys
sys.setrecursionlimit(10**6)

n = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(n-1):
    u,v,cost = map(int,input().split())
    adj[u].append((v,cost))

longest = 0
def dfs(u):
    global longest
    first,second = 0,-1
    for v,cost in adj[u]:
        cost += dfs(v)
        if cost > first:
            second = first
            first = cost
        elif cost > second:
            second = cost

    if second != -1:
        longest = max(longest,first+second)
    return first

h = dfs(1)
print(max(h,longest))
