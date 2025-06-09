import json
from math import sqrt,acos,degrees,atan
import numpy as np

def normalize(data):
    min_value = min(data)
    max_value = max(data)
    normalized_data = []
    for x in data:
        normalized_data.append((x - min_value) / (max_value - min_value))
    return normalized_data

def data_sample(data, x_or_y):
    sample_res = []
    if x_or_y == 0 or x_or_y == 1:
        for i in range(x_or_y, len(data), 3):
            sample_res.append(data[i])
        return sample_res
    else:
        print("wrong input")
        return

f = open('json_data/stand_keypoints.json', 'r')
content = f.read()
a = json.loads(content)
f.close()
b = a['people']
data = b[0]['pose_keypoints_2d']
# print(f"the size of the list pose_keypoints_2d {len(data)}")

""" normalize the positions """
x_position = data_sample(data,0)
y_position = data_sample(data,1)

# print(x_position)
# print(y_position)

x_norm = normalize(x_position)
y_norm = normalize(y_position)


# the position of the ass
x_ass = x_norm[8]
y_ass = y_norm[8]

# position of the left knee
x_left_knee = x_norm[10]
y_left_knee = y_norm[10]

# position of the right knee
x_right_knee = x_norm[13]
y_right_knee = y_norm[13]

#distance between ass and knees
dis_ass_left_knee = abs(y_ass-y_left_knee)
dis_ass_right_knee = abs(y_ass-y_right_knee)
print(f"the absolute distance between ass and knees are:\n {dis_ass_left_knee} and {dis_ass_right_knee}")


""" sit or not ?"""

if dis_ass_right_knee < 0.052 and dis_ass_left_knee < 0.052:
    print("you are sitting")
elif dis_ass_right_knee >0.23 and dis_ass_left_knee > 0.23:
    print("you are standing")
else:
    print("you are not sitting or standing")

