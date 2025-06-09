"""
name_dictionary = {
key_name1: value1,
key_name2: value2,
key_name3: value3,
key_name4: value4
}

in one dictionary, key_name cannot be the same

empty_dictionary = {} or dict()
"""
dictionary = {
    "Jack Cooper": 10000,
    "Ash": 10000000,
    "python": "stupid"
}
print(dictionary)
print(dictionary["Jack Cooper"])

"""
value can be a list, set,tuple, string,dictionary
nest_dictionary = {
    key_name1: {
        sub_key1_name1: value1,
        sub_key1_name2: value2,
        sub_key1_name3: value3
    },
    key_name2: {
        sub_key2_name1: value1,
        sub_key2_name2: value2,
        sub_key2_name3: value3
    }
}
"""

nested_dictionary = {
    "Jack Cooper": {"Chinese": 150,
                    "Mathmetics": 150,
                    "English": 150
                    },
    "Ash":{
        "Chinese":90,
        "mathmetics":90,
        "English":90
    },
    "python":{
        "Chinese": 0,
        "Mathmetics": 0,
        "English": 0
    }
}

print(nested_dictionary["Jack Cooper"]["Mathmetics"])
# modify value
nested_dictionary["Jack Cooper"]["Mathmetics"] = 10000
print(nested_dictionary["Jack Cooper"])
# add new key
nested_dictionary["Ash"]["shape"] = 10000
print(nested_dictionary["Ash"])
# cut a key or a sub-dictionary
score = nested_dictionary["Ash"].pop("shape")
print(score)
print(nested_dictionary["Ash"])
sub_dict = nested_dictionary.pop("python")
print(sub_dict)
print(nested_dictionary)
# clear a sub-dictionary or the whole dictionary
nested_dictionary["Ash"].clear()
print(nested_dictionary)
nested_dictionary.clear()
print(nested_dictionary)

nested_dictionary = {
    "Jack Cooper": {"Chinese": 150,
                    "Mathmetics": 150,
                    "English": 150
                    },
    "Ash":{
        "Chinese":90,
        "mathmetics":90,
        "English":90
    },
    "python":{
        "Chinese": 0,
        "Mathmetics": 0,
        "English": 0
    }
}
# .keys can get all keys
keys_name = nested_dictionary.keys()
print(keys_name)
for key in keys_name:
    print(f"name of the examiner: {key}")
    print(f"his or her score: {nested_dictionary[key]}")

sub_keys = nested_dictionary["Jack Cooper"].keys()
print(sub_keys)
for key in sub_keys:
    print(f"Jack's subjects: {key}")
    print(f"his score: {nested_dictionary["Jack Cooper"][key]}")

for key in nested_dictionary:
    print(f"examiner name: {key}")
    print(f"his or her score: {nested_dictionary[key]}")

for key in nested_dictionary["Jack Cooper"]:
    print(f"Jack's subjects: {key}")
    print(f"the score: {nested_dictionary["Jack Cooper"][key]}")