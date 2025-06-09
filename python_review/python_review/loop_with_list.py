def while_with_list(my_list):
    index = 0
    while index < len(my_list):
        print(my_list[index])
        index += 1

def for_with_list(my_list):
    for element in my_list:
        print(element)

my_list = [1,2,3,4,5]
while_with_list(my_list)
print(".......")
for_with_list(my_list)