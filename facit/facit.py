#knapsack
ans = []
for count in range(30):
    ans.append([])
    s, n = map(int, input().split())
    items = []
    dp = [[-1 for i in range(s+1)] for j in range(n)]
    for _ in range(n):
        size, val = map(int, input().split())
        items.append([val, size])
        dp[_][0] = 0



    def rec(row, col):
        val, size = items[row][0], items[row][1]

        if dp[row][col] != -1:
            return dp[row][col] 
        elif row == 0:
            if size <= col:
                dp[row][col] = val
            else:
                dp[row][col] = 0 
            return dp[row][col]
        if size <= col:
            dp[row][col] = max(val+rec(row-1, col-size), rec(row-1, col))

        else:
            dp[row][col] = rec(row-1, col)
        return dp[row][col]
    rec(n-1, s)

    ct = 0
    ro = n-1
    co = s
    while True:
        if ro == 0 and co != 0:
            ans[count].append(ro)
            ct += 1
            break
        if dp[ro][co] == dp[ro-1][co]:
            ro -= 1
            continue
        else:
            ans[count].append(ro)
            ro -= 1
            co = co - items[ro][1] 
            ct += 1
for thing in ans:
    print(len(thing))
    print(" ".join(thing))

#dfs
import sys
sys.setrecurisonlimit(10**9)
n = int(input())
adj = []
visited = [False for i in range(n)]
def dfs(at):
    if visited[at]:
        return
    visited[at] = True
    for v in adj[at]:
        dfs(v)



#bfs        
from collections import deque
n = int(input())
q = deque()
dist = [-1] * n
adj = []
q.append(0)
dist[0] = 0
while len(q) > 0:
    u = q.popleft()
    for v in adj[u]:
        if dist[v] == -1:
            dist[v] == dist[u]+1
            q.append(v)
            

import sys
sys.setrecusionlimit(10**6)

m = int(input())

# 1, 3, 4
coins = [1, 5, 10]
change = [-1 for i in range(m+1)]
change[0] = 0
for i in range(1, m+1):
    mini = 10**18
    for j in range(len(coins)):
        if i - coins[j] >= 0:
            if change[i-coins[j]]+1 < mini:
                mini = change[i-coins[j]]+1
    change[i] = mini
print(change[-1])
                

#dijkstra
import heapq
import sys
sys.setrecursionlimit(10**9)

t = int(input())

for i in range(t):
    n, m = map(int, input().split())
    adj = [[] for i in range(n)]
    for j in range(m):
        a, b, c = map(int, input().split())
        adj[a-1].append((b-1, c))
        adj[b-1].append((a-1, c))

        
    s = int(input())
    q = []
    heapq.heappush(q, (0, s-1))
    dist = [10**18]*n
    dist[s-1] = 0
    visited = set()
    while len(q) > 0:
        d, u = heapq.heappop(q)
        if u in visited: 
            continue
        visited.add(u)
        
        for v, w in adj[u]:

            newdist = dist[u] + w
            if newdist < dist[v]:
                dist[v] = newdist
                heapq.heappush(q, (newdist, v))

    for j in range(len(dist)):
        if dist[j] == 10**18:
            dist[j] = -1
        if dist[j] != 0:
            if j == len(dist)-1:
                print(dist[j])
                continue
            print(dist[j], end=' ')
            
            
            
#union find
n, q = map(int, input().split())
parent = [i for i in range(n)]
rank = [0 for i in range(n)]

def find_set(v):
    if v == parent[v]:
        return v
    parent[v] = find_set(parent[v])
    return parent[v]

def union_sets(a, b):
    a = find_set(a)
    b = find_set(b)
    if a!=b:
        if rank[a] < rank[b]:
            a, b = b, a
        parent[b] = a
        rank[a] += 1
        

for i in range(q):
    inp = [i for i in input().split()]
    inp[1] = int(inp[1])
    inp[2] = int(inp[2])
    if inp[0] == "?":
        a = find_set(inp[1])
        b = find_set(inp[2])

        if a != b:
            print("no")
        else:
            print("yes")
    else:
        union_sets(inp[1], inp[2])

          
