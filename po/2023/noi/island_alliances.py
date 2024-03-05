n, m, q = map(int, input().split())

hate = {}
parent = [i for i in range(n)]
rank = [0 for i in range(n)]
def find_par(u):
    if u == parent[u]:
        return u
    parent[u] = find_par(parent[u])
    return parent[u]

def union(a, b):
    a = find_par(a)
    b = find_par(b)
    if a!=b:
        if rank[a] < rank[b]:
            a, b = b, a
        parent[b] = a
        rank[a] +=1

for i in range(m):
    a, b = map(int, input().split())
    a-=1
    b-=1
    if a not in hate:
        hate[a] = [b]
    else:
        hate[a].append(b)

    if b not in hate:
        hate[b] = [a]
    else:
        hate[b].append(a)

for i in range(q):
    u, v = map(int, input().split())
    u-=1
    v-=1
    u1 = find_par(u)
    v1 = find_par(v)
    say = ""
    if u1 in hate:
        for group in hate[u1]:
            gr_lead = find_par(group)
            # print("u1 v1 gr", u1, v1, gr_lead)
            if v1 == gr_lead:
                say = "REFUSE"
                break
    if say == "REFUSE":
        print(say)
    else:
        print("APPROVE")
        union(u1, v1)
        new_lead = find_par(u1)
        if u1 != new_lead:
            u1, v1, = new_lead, u1
        if u1 not in hate:
            if v1 in hate:
                hate[u1] = hate[v1] #vet inte om det blir copy eller egen
        else:
            if v1 in hate:
                hate[u1] += hate[v1]
