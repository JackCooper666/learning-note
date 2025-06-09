"""
    this file is for the fucking review for the python variable
"""

print(666)
print("black horse")
"""
that is interpretation
"""
# single line interpretation

money = 50.555
print("there ",money,"dollar in my wallet")

ice_cream = 10
money = money-ice_cream
print("now, there is ",money,"dollar rest",type(money))

# variable type transfer
num2str = str(11)
print(type(num2str),num2str)
str2float = float("11.2323")
print(type(str2float),str2float)
print("11//2 = ", 11/2)
print("11%2 = ", 11%2)
print("2**3 is 2^3 = ", 2**3)
print("I try to use citation \"black horse\"")
print("I try" + "to fuck python") # this is joker, trash, bich
print("fuck you",str("sb13"),num2str,str2float,2**6)

company_name = "Media boarder"
stock_price = 19.99
stock_code = "003032"
stock_price_daily_growth_factor = 1.2
growth_days = 7

print("company:",company_name,"stock code:",stock_code,"stock price:",stock_price,"stock price daily growth factor:",stock_price_daily_growth_factor,"after",growth_days,"days growth","the price reached %.2f"% (stock_price*(stock_price_daily_growth_factor**7)))

print("What is your name")
name = input() # the result of input() is string always
print("your fucking name is",name)