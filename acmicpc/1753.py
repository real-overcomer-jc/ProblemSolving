import heapq
import sys

input = sys.stdin.readline
n,m = map(int,input().split())
start = int(input())

adj = [[] for _ in range(n+1)]
for _ in range(m):
    u,v,cost = map(int,input().split())
    adj[u].append([v,cost])

INF = int(1e9)
distance = [INF]*(n+1)

q = []
heapq.heappush(q,(0,start))
distance[start] = 0
while q:
    dist,u = heapq.heappop(q)
    if dist > distance[u]:
        continue

    for v,cost in adj[u]:
        cost += dist
        if distance[v] > cost:
            distance[v] = cost
            heapq.heappush(q,(cost,v))

for i in range(1,n+1):
    print(distance[i] if distance[i] != INF else 'INF')



