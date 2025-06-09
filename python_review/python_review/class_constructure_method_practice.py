class student:
    def __init__(self, name, age, score):
        self.name = name
        self.age = age
        self.score = score

stu_list = []
for i in range(5):
    print(f"the information of the {i} student")
    name = input("input student name")
    age = input("input student age")
    score = input("input student score")
    stu_list.append(student(name, age, score))
    print(f"the {i} student: name {stu_list[i].name}, age {stu_list[i].age}, score {stu_list[i].score}")

print(stu_list)