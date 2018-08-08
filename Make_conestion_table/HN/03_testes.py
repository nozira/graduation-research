import re
arr = []
brr = []
with open ('./HN_conect00.txt', 'a', encoding='utf8') as out:
    with open ('./HN_conect01.txt', 'r', encoding='utf8') as input:
        for i in range(9700):#ID.txt行数指定
            c = input.readline()
            line = c.replace('\n','')
            arr.append(line)
            if ("県" not in arr[i] ):
                brr.append(arr[i])

        for k in range(9120):
            out.write(brr[k])
            out.write('\n')