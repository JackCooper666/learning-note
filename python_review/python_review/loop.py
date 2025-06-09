import random

i = 0
while i < 100:
    print("Oh, beauty, I love you")
    i += 1

i = 1
sum = 0
while i <= 100:
    sum += i
    i += 1

print("accumulation of 100",sum)

i = 1
while i < 10:
    j = 1
    while j<=i:
        print(f"{i}*{j}={i*j}\t",end='')
        j += 1
    print()
    i += 1


name = "itheima is a brand of itcast"
i = 0
for letter in name:
    if letter == "a":
        i += 1

print(f"There are {i} letters \"a\"")

"""
    range(num1)
    range(5) = [0 1 2 3 4]
    range(num1,num2)
    range(5,10) = [5,6,7,8,9]
    range(num1,num2,step)
    range(5,10,2) = [5,7,9]

"""
j = 0

for l in range(1,100):
    if l % 2 == 0:
        j += 1
print(f"There are {j} odd numbers")
print(l) # the value of "l" can be got !!!, but this is wrong and informal

i = 0
j = 0
for i in range(1,10):
    for j in range(1,i+1):
        print(f"{j}*{i}={i*j}\t",end='')
    print()

import random
money_store= 10000
salary = 1000
member = 20
i = 0
for i in range(member):
    grade = random.randint(1,10)
    if grade < 5:
        print(f"member {i+1} grade is {grade}, does not have salary")
        continue
    elif money_store <= 0:
        print("run out of the money store, not salary, see you next year")
        break
    else:
        print(f"member {i+1} grade is {grade}, salary is {salary}, next person")
        money_store -= salary
        print(f"money_store is {money_store}")






"""
num = random.randint(1,10)
i = 1
flag = False
while flag == False:
    answer = int(input(f"{i} times guess"))
    if answer == num:
        print("right")
        flag = True
    else:
        print("wrong")
        flag = False
        i += 1
        if answer > num:
            print("too high")
        else:
            print("too low")
"""

