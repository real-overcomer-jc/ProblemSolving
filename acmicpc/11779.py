from collections import deque
import sys
input = sys.stdin.readline

n = int(input())
m = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(m):
    u,v,cost = map(int,input().split())
    adj[u].append((v,cost))

start,end = map(int,input().split())

INF = float('inf')
distance = [INF]*(n+1)
parent = [-1]*(n+1)

q = deque([(0,start)])
distance[start] = 0
while q:
    dist,u = q.popleft()
    if dist > distance[u]:
        continue

    for v,cost in adj[u]:
        cost += dist
        if distance[v] > cost:
            parent[v] = u
            distance[v] = cost
            q.append((cost,v))

path = []
v = end
while v != -1:
    path.append(v)
    v = parent[v]
path.reverse()

print(distance[end])
print(len(path))
print(*path)


    



