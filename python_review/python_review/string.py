"""
string cannot be modified
"""

my_str = "fucking python"
print(my_str[0],my_str[-1])

# array cut name_str[start_index:end_index:step], the name_str[end_index] is excluding
print(my_str[1:-1])

# find the index of the started character
print(my_str.index('py'))

# my_str.replace(str1,str2) can replace the str1 in my_str with str2,
# then return the string as a new string, the old my_str does not change
my_str_new = my_str.replace('py','py2sdsds')
print(my_str)
print(my_str_new)

# my_str.split(split character) will split my_str into several elements,
# then stores as a list, but the old one does not change
my_str = "fucking python, fucking ROS"
my_str_list = my_str.split(' ')
print(my_str)
print(my_str_list)
my_str = "123_Jack_Cooper_321"
strip_my_str = my_str.strip("123") # remove '1,' '2' and '3,' not "123"
print(my_str)
print(strip_my_str)

