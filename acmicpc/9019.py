from collections import deque

N = 10000
for _ in range(int(input())):
    a,b = map(int,input().split())

    visited = [False]*N
    q = deque([(a,'')])
    visited[a] = True
    while q:
        n,cmd_list = q.popleft()
        next_state = []
        # D
        next_state.append(((2*n)%N,'D'))
        # S
        next_state.append(((n-1+N)%N,'S'))
        # L,R
        left_rotated = (n%1000)*10+n//1000
        right_rotated = (n//10)+(n%10)*1000
        next_state.append((left_rotated,'L'))
        next_state.append((right_rotated,'R'))

        found = False
        for state,cmd in next_state:
            if not visited[state]:
                if b == state:
                    found = True
                    print(cmd_list+cmd)
                    break
                visited[state] = True
                q.append((state,cmd_list+cmd))

        if found:
            break


