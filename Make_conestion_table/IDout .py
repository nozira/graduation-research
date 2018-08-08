import re
out = []
#参照地域指定
with open('HN_sample_ID.txt','r',encoding='utf8') as input_id:
    for k in range(194):
        d = input_id.readline()
        e = d.rstrip()
        init.append(e)
#初期化データ出力
with open('HK_conect.csv','a',encoding='utf8') as out:
    for n in range(194):
        for k in range(194):
            if(n==k):
                out.write('#,')
            else:
                out.write('0,')
        out.write('\n')