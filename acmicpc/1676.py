N = int(input())

def exp_range(s,e,m):
    while s < e:
        yield s
        s *= m

count = 0
for n in exp_range(5,N+1,5):
    count += N//n

print(count)

