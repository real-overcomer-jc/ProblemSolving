import sys
sys.setrecursionlimit(10**6)
input = sys.stdin.readline

n = int(input())
adj = [[] for _ in range(n+1)]
while True:
    try:
        u,v = map(int,input().split())
        adj[u].append(v)
        adj[v].append(u)
    except:
        break

def dfs(u,visited,parent):
    visited[u] = True
    for v in adj[u]:
        if not visited[v]:
            parent[v] = u
            dfs(v,visited,parent)

visited = [False]*(n+1)
parent = [-1]*(n+1)

dfs(1,visited,parent)
print(*parent[2:],sep='\n')






