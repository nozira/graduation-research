import re
arr = []
brr = []
crr = []
row = []
#初期化データ読込
with open('HN_conect.csv','r',encoding='utf8') as input:
    for k in range(1599):
        d = input.readline()
        brr.append(d.split(','))
    #print(brr[0][0])
#地域ＩＤ読込
with open('HN_ID.txt','r',encoding='utf8') as input_id:
    for k in range(1599):
        d = input_id.readline()
        e = d.rstrip()
        row.append(e)
#隣接情報読込　and　配列に格納　after　処理
with open('HN_conect00.txt','r',encoding='utf8') as input_conect:
    c = input_conect.read()
    arr.append(c.split('\n\n'))
    for i in range(8791):
        crr.append(arr[0][i].split('\n'))
        L = len(crr[i])
        for j in range(L):
            for n in range(1599):
                for m in range(1599):
                    if(brr[n][m]!='#' and crr[i][0]==row[n] and crr[i][j]==row[m]):
                        brr[n][m]='xxx'
        if(i%800==0):
            print('#')
#.csvで出力
with open('HK_conect00.csv','a',encoding='utf8') as out:
    for t in range(1599):
        for m in range(1599):
            out.write(str(brr[t][m])+',')
        out.write('\n')