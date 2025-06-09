my_str = "salary 10000, Horse black to welcome, python learn"
new_str_1 = my_str[my_str.index("Horse"):my_str.index(", python")].split(" ")[-1::-1]
print(new_str_1)
