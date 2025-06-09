my_list = [21,25,21,23,22,20]
my_list.append(31)
print(my_list)
my_list.extend([29,33,30])
print(my_list)
first_element = my_list.pop(0)
last_element = my_list.pop(-1)
print(f"cut the first element {first_element} and the last element {last_element}")
print(my_list)
my_list[my_list.index(21)] = 31
print(my_list)
print(f"elements 31 are at {my_list.index(31)}")