import datetime
import subprocess
import math
import random
from time import sleep


for i in range(10):
    system = r'./'+str(i)+r'/Division/v010'
    source = r'./'+str(i)+r'/Division/v010.c'
    try:
        subprocess.check_call(['gcc','-o',system,source,'-lm'])
        print("Compiled")
    except:
        print("subprocess.check_call() failed")

filePOP = []
popYear = []
popData = []
for j in range(10):
    temp = []
    for k in range(10):
        filePOP.append(r'./'+str(k)+r'/Division/Population/'+str(j)+r'.txt')
        with open(filePOP[(10*j)+k]) as filePOP[(10*j)+k]:
            lines = filePOP[(10*j)+k].readlines()
            pop = []
            for line in lines:
                pop.append(int(line.rstrip()))
            popYear.append(pop)
        temp.append(sum(popYear[(10*j)+k]))
    popData.append(temp)

data = []
for i in range(10):
    arr = []
    for j in range(6):
        arr.append(popData[j][i] + popData[j+1][i] + popData[j+2][i] + popData[j+3][i] + popData[j+4][i])
    data.append(arr)

result = []
for j in range(6):
    temp =[]
    for i in range(10):
        temp.append(data[i][j])
    result.append(temp)

out = []
for j in range(6):
    temp = []
    for i in range(10):
        temp.append(math.floor(289*(result[j][i]/sum(result[j]))))
    out.append(temp)

for i in range(6):
    for j in range(289-sum(out[i])):
        num = random.randint(0,9)
        out[i][num] = out[i][num] + 1

seats = []
for j in range(10):
    temp = []
    for i in range(6):
        temp.append(out[i][j])
    seats.append(temp)
file = []
for j in range(9):
    for k in range(6):
        now = datetime.datetime.now()
        system = r'./'+str(j)+r'/Division/v010'
        connect = r'./'+str(j)+r'/Division/town/conect_id.txt'
        seatsRegion = str(seats[j][k])
        print(seatsRegion)
        for l in range(5):
            file.append(r'./'+str(j)+r'/Division/Population/'+str(k + l)+r'.txt')
            print(file[l])
        out = r'./'+str(j)+r'/out/'+str(now.year)+str(now.month)+str(now.day)+str(now.hour)+str(now.minute)+str(now.second)+r'.csv'
        try:
            subprocess.check_call([system,seatsRegion,connect,file[0],file[1],file[2],file[3],file[4],out])
        except:
            print("subprocess.check_call() failed")
        print(">",end="")
    print("\n",end="")
print("Fin")