funding = 5000000

def manu(username):
    print(f"Hello, {username}, welcome to black bank, your requirement?")
    print("funding check:\t [Pess 1]")
    print("deposit:\t [Pess 2]")
    print("withdraw:\t [Pess 3]")
    print("leave:\t [Pess 4]")
    option = int(input("Your choice Press enter to continue"))
    return option

def funding_check():
    print("funding check")
    print(f"your funding is {funding} CNY")

def deposit():
    print("deposit")
    #print(f"your funding is {funding} CNY, now")
    money = float(input("how much you want to deposit?"))
    global funding
    funding += money
    funding_check()

def withdraw():
    print("withdraw")
    #print(f"your funding is {funding} CNY, now")
    money = float(input("how much you want to withdraw?"))
    global funding
    funding -= money
    funding_check()


username = input("What is your name?")
while True:
    option = manu(username)
    if option == 1:
        funding_check()
    elif option == 2:
        deposit()
    elif option == 3:
        withdraw()
    else:
        break