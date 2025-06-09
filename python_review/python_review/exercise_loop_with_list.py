def while_with_list(my_list):
    index = 0
    odd_list = []
    while index < len(my_list):
        if my_list[index]%2 == 0:
            odd_list.append(my_list[index])
        index += 1
    return odd_list

def for_with_list(my_list):
    odd_list = []
    for element in my_list:
        if element %2 == 0:
            odd_list.append(element)

    return odd_list

my_list = [1,2,3,4,5,6,7,8,9,10]
print(while_with_list(my_list))
print(".......")
print(for_with_list(my_list))