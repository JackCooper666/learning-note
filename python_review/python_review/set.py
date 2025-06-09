"""

the element in a set must be different
, and the arrangement of element in a set is not in order
, but set can be modified unlike the string and tuple
my_set = {element. element, element, element}
empty_set = set()

"""

my_set = {"fuck","you","fall","in","love"}
print(my_set)

# add new element
my_set.add("python")
my_set.add("fuck")
print(my_set)

# remove element
my_set.remove("python")
print(my_set)

# sample an element randomly
element = my_set.pop()
print(element)
print(my_set)

# get a difference set of two sets
set1 = {1,2,3,7}
set2 = {1,5,6,2}
set3 = set1.difference(set2) # the elements that set1 has but set2 does not have, and creat a new set
print(set1)
print(set2)
print(set3)

set1 = {1, 2, 3, 7}
set2 = {1, 5, 6, 2}
set4 = set2.difference(set1)
print(set1)
print(set2)
print(set4)

# delete the elements of set1 that both sets have
set1 = {1, 2, 3, 7}
set2 = {1, 5, 6, 2}
set1.difference_update(set2)
print(set1)
print(set2)

# unitify two sets
set1 = {1,2,3,7}
set2 = {1,5,6,2}
set5 = set1.union(set2)
print(set1)
print(set2)
print(set5)

# read all the elements of set, only for_loop can be used
for element in set5:
    print(element)