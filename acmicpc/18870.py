n = int(input())
x_points = list(map(int,input().split()))

x_mapping_table = dict()
for i,xpos in enumerate(sorted(set(x_points))):
    x_mapping_table[xpos] = i

x_points = [x_mapping_table[xpos] for xpos in x_points]
print(*x_points,sep=' ')




