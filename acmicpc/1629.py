a,b,c = map(int,input().split())

def power(a,b):
    global c
    if b == 1:
        return a

    if b % 2 == 0:
        value = power(a,b//2) % c 
        return (value * value) % c
    else:
        return (a * power(a,b-1)) % c

print(power(a,b))
