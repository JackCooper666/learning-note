"""
1. list can store different types of element even another data temp such as list, string, tuple, set, dictionary
list_name = [element 1, element 2, element 3]
empty_list= list() or []
"""
mixed_list = ["adasdsd", "s", 1,2,3]
print(mixed_list)
print(mixed_list[0])
print(mixed_list[1])
print(mixed_list[4])
print(mixed_list[-1])
print(mixed_list[-2])
print(mixed_list[-5])

nest_list = [[1,2,3,4],[5,4,3]]
print(nest_list)
print(nest_list[0])
print(nest_list[0][0])
print(nest_list[0][1])
print(nest_list[0][2])
print(nest_list[1])
print(nest_list[1][0])
print(nest_list[1][1])

print(nest_list[1].index(5))
# name_list.index(element content) will show the index of the relative element
nest_list[1][nest_list[1].index(5)] = 66
# modify the content of the corresponding element
print(nest_list)

nest_list[0].insert(1,"fuck")
# insert an element in the list
print(nest_list)

nest_list[1].append("you")
# add an element at the end of the list
print(nest_list)

new_list = [1,2,"dsfasdf"]
nest_list[1].extend(new_list)
# add a list of elements at the end of the list
print(nest_list)

del nest_list[0]
# delete an element in the list
print(nest_list)
del nest_list[0][1]
print(nest_list)

new_list = [[1,2,"dsfasdf"]]
nest_list.extend(new_list)
print(nest_list)
# cut an element of a list
cut_list = nest_list.pop(0)
print(cut_list)
print(nest_list)

my_list = ["fuck","fuck","fuck","you","her"]
# remove an element according to the content of the element
# .remove can only remove the first aimed  element
my_list.remove("fuck")
print(my_list)
# count the "fuck", count the length of the list
count = my_list.count("fuck")
print(f"there are {count} \"fuck\"s in the list")
print(f"the length of the list is {len(my_list)}")
# clear the list
print(my_list.clear())
