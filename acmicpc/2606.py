n = int(input())
m = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(m):
    u,v = map(int,input().split())
    adj[u].append(v)
    adj[v].append(u)

visited = [False]*(n+1)
count = 0

def dfs(u):
    global count
    visited[u] = True
    for v in adj[u]:
        if not visited[v]:
            dfs(v)
    count += 1

dfs(1)
print(count-1)


