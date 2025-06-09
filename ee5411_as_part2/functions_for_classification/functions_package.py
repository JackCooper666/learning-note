import json
from math import sqrt,acos,degrees,atan
import numpy as np

def json_load_and_pre_processing(filename):
    f = open(filename,'r')
    content = f.read()
    a = json.loads(content)
    f.close
    people = a['people']
    number_of_people = len(people)
    data_people = []

    for i in range(number_of_people):
        data_person = people[i]['pose_keypoints_2d']
        data_people.append(data_person)

    return data_people

def normalize(data):
    min_value = min([min(sublist) for sublist in data])
    max_value = max([max(sublist) for sublist in data])
    normalized_data = []
    for sublist in data:
        normalized_data_sublist = []

        for x in sublist:
            normalized_data_sublist.append((x - min_value)/(max_value - min_value))

        normalized_data.append(normalized_data_sublist)

    return normalized_data

def data_sample(normalized_data, x_or_y):
    sample_res = []

    if x_or_y == 0 or x_or_y == 1:
        for normalized_sublist in normalized_data:
            normalized_sublist_temp = []

            for x in range(x_or_y,len(normalized_sublist),3):
                normalized_sublist_temp.append(normalized_sublist[x])

            sample_res.append(normalized_sublist_temp)
    else:
        print("wrong input")
        return
    return sample_res


def check_sitting_standing(i, tailbone, left_knee, right_knee, left_ankle, right_ankle):
    i = i
    vector_tailbone2left_knee = [0,0]
    vector_tailbone2right_knee = [0,0]
    vector_left_ankle2knee = [0,0]
    vector_right_ankle2knee = [0,0]

    # vector tailbone to knees
    vector_tailbone2left_knee[0] = left_knee[0] - tailbone[0]
    vector_tailbone2left_knee[1] = left_knee[1] - tailbone[1]
    vector_tailbone2right_knee[0] = right_knee[0] - tailbone[0]
    vector_tailbone2right_knee[1] = right_knee[1] - tailbone[1]
    print(f"the vector tailbone to knees is:\n to left knee {vector_tailbone2left_knee} and to right knee {vector_tailbone2right_knee}")

    # vector knees to ankles
    vector_left_ankle2knee[0] = left_ankle[0] - left_knee[0]
    vector_left_ankle2knee[1] = left_ankle[1] - left_knee[1]
    vector_right_ankle2knee[0] = right_ankle[0] - right_knee[0]
    vector_right_ankle2knee[1] = right_ankle[1] - right_knee[1]
    print(f"the vectors knees to ankles are:\n to left knee {vector_left_ankle2knee} and to right knee {vector_right_ankle2knee}")

    """ sit or not ?"""

    if vector_tailbone2right_knee[1] < 0.12 and vector_tailbone2left_knee[1] < 0.12:
        if  vector_left_ankle2knee[1] > - 0.06 and vector_right_ankle2knee[1] > - 0.06:
            print(f"{i + 1}th person is sitting")
        else:
            print(f"{i + 1}th person is not sitting or standing")

    elif vector_tailbone2right_knee[1] > 0.14 and vector_tailbone2left_knee[1] > 0.14:
        if vector_left_ankle2knee[1] > 0.13 and abs(vector_left_ankle2knee[1]-vector_right_ankle2knee[1]) < 0.05:
            print(f"{i + 1}th person is standing")
        else:
            print(f"{i + 1}th person is not sitting or standing")

    else:
        print(f"{i + 1}th person is not sitting or standing")

    print("one check finish")

if __name__ == '__main__':

    """ 
    data_1 = json_load_and_pre_processing('multi_people_2_keypoints.json')
    print(data_1)
    normalized_data_1 = normalize(data_1)
    print(normalized_data_1)
    print(data_sample(normalized_data_1, 0))

    data_2 = json_load_and_pre_processing('stand_keypoints.json')
    print(data_2)
    print(len(data_2))
    normalized_data_2 = normalize(data_2)
    print(normalized_data_2)
    print(len(normalized_data_2))
    print(data_sample(normalized_data_2, 0))
    print(len(data_sample(normalized_data_2, 0)))
    """


