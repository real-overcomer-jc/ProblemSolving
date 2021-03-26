n = int(input())
m = int(input())
s = input()

io = 0
count = 0
for i in range(1,m):
    if s[i-1] == 'I' and s[i] == 'O': 
        io += 1
    elif s[i-1] == 'O' and s[i] == 'I':
        if io >= n: count += 1
    else:
        io = 0

print(count)


