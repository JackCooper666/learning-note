my_list = [1, 2, 3, 4, 5, 6, 7, 8,"string1"]
my_tuple = (1,2,3,4,5,6,2,4,"string1")
my_str = "fasdfsdaf"
my_set = {1,2,4,5,"string"}

# list() transfer to list
print(f"tuple to list: {list(my_tuple)}")
print(f"str to list: {list(my_str)}")
print(f"set to list: {list(my_set)}")
# str() to str
print(f"list to str: {str(my_list)}")
print(f"tuple to str: {str(my_tuple)}")
print(f"set to str: {str(my_set)}")
# tuple() to tuple
print(f"list to tuple: {tuple(my_list)}")
print(f"str to tuple: {tuple(my_str)}")
print(f"set to tuple: {tuple(my_set)}")
# set() to set
print(f"list to set: {set(my_list)}")
print(f"str to set: {set(my_str)}")
print(f"tuple to set: {set(my_tuple)}")
# set cannot nest with list