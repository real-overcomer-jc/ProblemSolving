from collections import deque

n,k = map(int,input().split())

def bfs(start,target):
    INF = int(1e5)+1
    q = deque([start])
    visited = [False]*INF
    visited[start] = True
    time = 0
    while True:
        count = len(q)
        for _ in range(count):
            x = q.popleft()
            if x == target:
                return time   
            for next_pos in x-1,x+1,2*x:
                if 0 <= next_pos < INF and not visited[next_pos]:
                    visited[next_pos] = True
                    q.append(next_pos)
        time += 1
    return -1

result = bfs(n,k)
print(result)



