from itertools import combinations

n,m = map(int,input().split())

home = []
chicken = []
for i in range(n):
    row = list(map(int,input().split()))
    for j in range(n):
        if row[j] == 1:
            home.append((i,j))
        elif row[j] == 2:
            chicken.append((i,j))

INF = int(1e9)
min_city_distance = INF
for picked in combinations(chicken,m):
    city_distance = 0
    for y1,x1 in home:
        distance = INF
        for y2,x2 in picked:
            distance = min(distance,abs(y1-y2)+abs(x1-x2))
        city_distance += distance
    min_city_distance = min(min_city_distance,city_distance)

print(min_city_distance)




