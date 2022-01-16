"""
Generator of random binary pictures saved as .txt file
"""
x=int(input("Wight: "))
y=int(input("Height: "))
name=input("Name: ")

import random;
am=int(x*y*0.3)
temp=[]
for i in range(x):
    temp.append([])
    for j in range(y):
        temp[i].append(0)
        
while am>0:
    i=random.randrange(x)
    j=random.randrange(y)
    if temp[i][j] == 0:
        temp[i][j] = 1
        am -= 1
with open("./pictures/"+name+".txt",mode='w',newline='') as f: 
    f.write(str(x)+"\t"+str(y)+"\n")
    for ny in range(y):
        for nx in range(x):
            f.write(str(temp[nx][ny])+"\t")
        f.write("\n")
f.close()
