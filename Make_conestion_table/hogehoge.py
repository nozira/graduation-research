import re
arr = []
with open ('./自治体ＩＤ.txt', 'r', encoding='utf8') as input00:
    for k in range(2277):
        c = input00.readline()
        arr.append(c.split(","))
        print(arr[k][1])
with open ('./ID.txt', 'a', encoding='utf8') as out:
    for i in range(2277):
        out.write(arr[i][1])