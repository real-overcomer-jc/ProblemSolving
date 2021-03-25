n,m = map(int,input().split())

counter_dict = dict()
for _ in range(n+m):
    name = input()
    counter_dict.setdefault(name,0)
    counter_dict[name] += 1

count = 0
result = []
for key in counter_dict:
    if counter_dict[key] == 2:
        count += 1
        result.append(key)
result.sort()

print(count)
print(*result,sep='\n')

