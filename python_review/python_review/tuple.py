"""
In comparison with list, tuple cannot be modified

name_tuple = (element 1, element 2, element 3)
empty_tuple = () or tuple()

"""

my_tuple = (1, "two", 3, 6.666)
print(my_tuple)

# single-element tuple
single_tuple = ("yyds",)
print(single_tuple)

# nest_tuple
nest_tuple = (1, (1,"yyds"),[1,2,"fuck"])
print(nest_tuple)
print(nest_tuple[1][1])

# index(), count(), len()
print(nest_tuple[1].index(1))
print(nest_tuple[2].count("fuck"))
print(len(nest_tuple))
print(len(nest_tuple[1]))

# tuple cannot be modified, but the list in the tuple can be modified
nest_tuple[2][2] = 3
print(nest_tuple)