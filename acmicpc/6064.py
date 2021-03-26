from math import gcd

def lcm(a,b):
    return a*(b//gcd(a,b))

for _ in range(int(input())):
    N,M,x,y = map(int,input().split())

    x -= 1
    y -= 1
    found = False
    for k in range(x,x+lcm(N,M),N):
        if k % M == y:
            print(k+1)
            found = True
            break

    if not found:
        print(-1)
            

