class student:
    # class property
    name = None
    gender = None
    nationality = None
    age = None
    # class behavior
    # function in class
    # "self" must be in behavior compulsorily, but it is not compulsory to be used
    def say_hello(self):
        print(f"Hello World {self.name}")
    def say_goodbye(self,msg):
        print(f"Goodbye {msg}")

stu_1 = student()
stu_1.name = 'Zewen Sun'
stu_1.gender = 'Male'
stu_1.age = 18
stu_1.nationality = 'China'
stu_2 = student()
stu_2.nationality = 'China'
stu_2.name = 'Jack Cooper'
stu_2.gender = 'Male'
stu_2.age = 20

print(stu_1.name)
print(stu_1.gender)
print(stu_1.age)
print(stu_1.nationality)
print(stu_2.name)
print(stu_2.gender)
print(stu_2.age)
print(stu_2.nationality)
stu_1.say_hello()
stu_1.say_goodbye('fuck')
stu_2.say_hello()
stu_2.say_goodbye('Wula!!!!!!!//////')