"""

Chapter 3-
Judgment

"""

import random

verify_1 = True # True, 1
compare = 10>5
print("10>5 =",compare,"type of compare:",type(compare))

"""
>
<
<=
>=
==
!=
"""

print("Welcome to black horse park. Free ticket for people who is under 120cm")
high = int(input("What is your high?"))
vip_level = int(input("and your vip level?"))

if high < 120:
    print("You are so low,stupid little man, here is your free ticket")
elif vip_level > 3:
    print("Oh!!! my distinguished guest, here is your free ticket")
else:
    print("You are so tall, 10 CNY ticket")

print("happy in the park")

print("number guessing game")
answer = int(input("Your answer?"))
num = random.randint(1,10)

if answer == num:
    print("Congrats!")
else:
    if answer > num:
        print("Your answer is too high")
    else:
        print("Your answer is too low")

    answer = int(input("Your second chance?"))
    if answer == num:
        print("Congrats!")
    else:
        if answer > num:
            print("Your second chance is too high")
        else:
            print("Your second chance is too low")

        answer = int(input("Your third chance?"))
        if answer == num:
            print("Congrats!")
        else:
            print("you are so stupid")