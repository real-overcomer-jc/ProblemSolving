from collections import deque
import sys

input = sys.stdin.readline
n,m,k = map(int,input().split())
board = [list(input()) for _ in range(n)]
dydx = ((0,1),(1,0),(0,-1),(-1,0))

INF = float('inf')
distance = [[[INF]*(k+1) for _ in range(m)] for _ in range(n)]
distance[0][0][0] = 1
q = deque([(0,0,0)])
min_dist = -1
while q:
    count,y,x = q.popleft()
    if y == n-1 and x == m-1:
        min_dist = distance[y][x][count]
        break

    for dy,dx in dydx:
        ny,nx = y+dy,x+dx
        if 0 <= ny < n and 0 <= nx < m and distance[ny][nx][count] == INF:
            if board[ny][nx] == '0':
                distance[ny][nx][count] = distance[y][x][count]+1
                q.append((count,ny,nx))
            elif count < k:
                distance[ny][nx][count+1] = distance[y][x][count]+1
                q.append((count+1,ny,nx))

print(min_dist)
