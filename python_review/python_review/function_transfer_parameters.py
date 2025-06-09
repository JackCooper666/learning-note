def user_info(name,age,gender):
    print(f"your name is {name}, your age is {age}, your gender is {gender}")

def user_info_1(name,age,gender = "Male"): # gender is the default parameter, default parameter should be at the end
    print(f"your name is {name}, your age is {age}, your gender is {gender}")

def variable_length_position_transfer_parameters(*args):
    print(args) # the ype of args is tuple

def variable_length_key_words_transfer_parameters(**kargs):
    print(kargs) # kargs is dictionary, so the input parameters must use key words transfer




# position transfer parameters: transfer real parameters according to the order of the visual parameters
user_info("Jack Cooper",18,"Male")
# key words transfer parameters
user_info(age= 20,name="Jack Cooper",gender="Male")
# position transfer with key words transfer, position transfer must be placed at the start and in order of the visual parameters
user_info("Jack Cooper", gender= "Male", age=20)

user_info_1("Fuck",20,gender="Female")
user_info_1("Jack Cooper", 1)

variable_length_position_transfer_parameters("TOM",[1,2,3],123)
variable_length_key_words_transfer_parameters(name="Jack Cooper",age=20, gender="Male")

