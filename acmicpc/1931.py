n = int(input())

schedules = []
for _ in range(n):
    i,j = map(int,input().split())
    schedules.append((i,j))

schedules.sort(key = lambda x: (x[1],x[0]))

count = 0
last = 0
for start,end in schedules:
    if last <= start:
        count += 1
        last = end

print(count)



