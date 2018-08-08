import re
arr = []
brr = []
Conect_ = []
CC_conection = []
with open ('./HK_conect01.txt', 'a', encoding='utf8') as out:
    with open ('./HK_ID.txt', 'r', encoding='utf8') as input00:
        for k in range(194):
            c = input00.readline()
            brr.append(c)
    with open ('./hokkaido000.txt', 'r', encoding='utf8') as input:
        for k in range(188):
            d = input.readline()
            arr.append(d.split(","))
            l = len(arr[k])
            for i in range(l):
                #print(arr[k][i])
                for j in range (194):
                    if (arr[k][i] in brr[j] ):
                        arr[k][i]=brr[j]
                        #print('###')
                        e = arr[k][i].replace('\n','')
                        arr[k][i] = e
                #print(arr[k][i])
                out.write(arr[k][i])
                out.write('\n')
            #print('\n')
            out.write('\n')