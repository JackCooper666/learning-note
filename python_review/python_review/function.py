"""
This section is used to practise "function"

Define a function
def function_name(input):
    comments
    return return value

Use the function
function_name(input)

e.g.
def strcount(data):
    count = 0
    for i in data:
        count += 1
    print(f"the length of the string \"{data}\" is {count}")

strcount("hello world")

"""

def start():
    print("Fuck you!!!, \nFucking Python!!!")

start()

def add(x, y):
    sum = x + y
    print(f"The sum of {x} and {y} is {sum}")
    return x + y

sum = add(2, 3)
print(f"the return value of the add function is {sum}")

def temperature_test(temperature):
    """
    This function is used to test the temperature
    :param temperature: tester's temperature
    :return: None
    """
    if temperature < 37.3:
        print("pass")
    else:
        print("fail")


temperature = float(input("enter your temperature"))
boom = temperature_test(temperature)
print(f"{boom}, the type of the return value of the temperature_test function {type(boom)}")

def return_none():
    return None

print(return_none())
print(str(return_none()))

# None == False
"""
def func_b():
    print("fuck")
    return b

def func_a():
    temp = func_b()
    print(f"Fuck Fuck {temp}")
    
func_a()
"""

"""
the variable at the outside of functions is the global value

num = 10
"""

num = 10

def func_a():
    print(f"func_a {num}")

def func_b():
    num = 300
    print(f"func_b {num}")

def func_c():
    global num # "global" can modify the value of global variable "num," or it can declare global variables in functions
    num = 400
    print(f"func_c {num}")
func_a()
func_b()
print(num)
func_c()
print(num)
