n = int(input())

times = list(map(int,input().split()))
times.sort()

total = 0
sum_value = 0
for time in times:
    sum_value += time
    total += sum_value

print(total)
