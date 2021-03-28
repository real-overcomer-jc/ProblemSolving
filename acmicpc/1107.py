import sys

input = sys.stdin.readline
n = int(input())
m = int(input())
buttons = [False]*10
for button in map(int,input().split()):
    buttons[button] = True

current = 100
best = abs(n-current)
for channel in range(0,999901):
    count = 0
    temp = channel
    while True:
        if buttons[temp%10]:
            count = -1
            break

        count += 1
        temp //= 10
        if temp == 0:
            break

    if count == -1:
        continue
    best = min(best,abs(n-channel) + count)

print(best)



        


    



