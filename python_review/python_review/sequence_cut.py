my_str = "fall in love"
# sequence cut name_str[start_index:end_index:step], the name_str[end_index] is excluding
# a new string will be created
new_str = my_str[0:7:2]
print(new_str)

# list is the same as string
my_list = [[1,2,3,4,5],[1,6,7,4,"dskladkasjdl"]]
new_list = my_list[1][0:5:2]
print(new_list)

# stuple as well
my_tuple = (1,2,3,4,5,"dadsa")
new_tuple = my_tuple[0:5:2]
print(new_tuple)