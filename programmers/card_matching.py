from itertools import permutations
from collections import deque
import copy

def bfs(board,y,x):
    dy = [-1,1,0,0]
    dx = [0,0,-1,1]

    n = len(board)
    INF = int(1e9)
    distance = [[INF]*n for _ in range(n)]

    q = deque([(y,x)])
    distance[y][x] = 0
    while q:
        y,x = q.popleft()
        for i in range(4):
            found = False
            ny,nx = y+dy[i],x+dx[i]
            while 0 <= ny < n and 0 <= nx < n:
                if 1 <= board[ny][nx] <= 6:
                    if distance[ny][nx] > distance[y][x]+1:
                        distance[ny][nx] = distance[y][x]+1
                        q.append((ny,nx))
                    found = True
                    break
                ny,nx = ny+dy[i],nx+dx[i]

            if not found:
                ny,nx = ny-dy[i],nx-dx[i]
                if distance[ny][nx] > distance[y][x]+1:
                    distance[ny][nx] = distance[y][x]+1
                    q.append((ny,nx))

            ny,nx = y+dy[i],x+dx[i]
            if 0 <= ny < n and 0 <= nx < n:
                if distance[ny][nx] > distance[y][x]+1:
                    distance[ny][nx] = distance[y][x]+1
                    q.append((ny,nx))

    return distance

def find_all_card_no(board):
    n = len(board)
    result = set()
    for y in range(n):
        for x in range(n):
            if 1 <= board[y][x] <= 6:
                result.add(board[y][x])
    return list(result)

def find_card_loc(board,card_no):
    n = len(board)
    result = []
    for y in range(n):
        for x in range(n):
            if board[y][x] == card_no:
                result.append((y,x))
    return result

result = int(1e9)
def remove_cards(board,card_no,prev_distance,total):
    global result
    card_loc = find_card_loc(board,card_no)
    for i in 0,1:
        start_y,start_x = card_loc[i]
        target_y,target_x = card_loc[(i+1)%2]

        new_total = total + 1 + prev_distance[start_y][start_x]

        #new_board = copy.deepcopy(board)
        distance = bfs(board,start_y,start_x)
        new_total += 1 + distance[target_y][target_x]

        board[start_y][start_x] = 0
        board[target_y][target_x] = 0

        next_distance = bfs(board,target_y,target_x)
        card_no_list = find_all_card_no(board)
        
        for next_card_no in card_no_list:
            remove_cards(board,next_card_no,next_distance,new_total)
            
        board[start_y][start_x] = card_no
        board[target_y][target_x] = card_no
        
        if len(card_no_list) == 0:
            result = min(result,new_total)

def solution(board, r, c):
    distance = bfs(board,r,c)
    card_no_list = find_all_card_no(board)
    for card_no in card_no_list:
        remove_cards(board,card_no,distance,0)
    return result
