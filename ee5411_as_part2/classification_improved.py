import json
from math import sqrt,acos,degrees,atan
import numpy as np

# self defined module
from functions_for_classification.functions_package import (
    json_load_and_pre_processing, normalize, data_sample, check_sitting_standing
)

# data load
data_people = json_load_and_pre_processing('json_data/my_standing_keypoints.json')
#print(data_people)

# normalized the data
normalized_people_data = normalize(data_people)
#print(normalized_people_data)

# get the x-axis position of each joint
normalized_people_data_x = data_sample(normalized_people_data, 0)
#print(normalized_people_data_x)
# get the y-axis position of each joint
normalized_people_data_y = data_sample(normalized_people_data, 1)
#print(normalized_people_data_y)

#print(len(data_people))
for i in range(len(data_people)):
    tailbone = []
    left_knee = []
    right_knee = []
    left_ankle = []
    right_ankle = []

    tailbone.append(normalized_people_data_x[i][8])
    tailbone.append(normalized_people_data_y[i][8])

    left_knee.append(normalized_people_data_x[i][10])
    left_knee.append(normalized_people_data_y[i][10])

    right_knee.append(normalized_people_data_x[i][13])
    right_knee.append(normalized_people_data_y[i][13])

    left_ankle.append(normalized_people_data_x[i][11])
    left_ankle.append(normalized_people_data_y[i][11])

    right_ankle.append(normalized_people_data_x[i][14])
    right_ankle.append(normalized_people_data_y[i][14])

    check_sitting_standing(i, tailbone, left_knee, right_knee, left_ankle, right_ankle)



