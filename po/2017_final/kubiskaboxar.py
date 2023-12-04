n = int(input())
R = []
B = []
G = []
for i in range(n):
    le, co = input().split()
    le = int(le)
    if co == "B":
        B.append(le)
    elif co == "R":
        R.append(le)
    else:
        G.append(le)
R.sort()
B.sort()
G.sort()
letter = ["R", "B", "G"]
let = [R, B, G]

comb = []

for c1 in let:
    for c2 in let:
        if c1 == c2:
            continue
        a = 0
        b = 0
        ok = 0
        while a < len(c1) and b < len(c2):
            if c1[a] < c2[b]:
                a += 1
                b += 1
                ok += 1
            else:
                b += 1
        comb.append([len(c1)-ok, let.index(c1), let.index(c2)])

ans = []
for i in range(6):
    for j in range(6):
        if comb[i][2] != comb[j][1] or comb[i][1] == comb[j][2]:
            continue
        ans.append([comb[i][0] + comb[j][0] + len(let[comb[j][2]]), comb[i][1], comb[i][2], comb[j][2]])

ans.sort()

print(letter[ans[0][3]] + letter[ans[0][2]] + letter[ans[0][1]])
print(ans[0][0])