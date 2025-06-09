class student:
    name = None
    age = None
    tel = None

    def __init__(self,name,age,tel):
        """"
        __init__() will executed automatically, after running student()
        student() will send its parameter into __init__() directly

        """
        self.name = name
        self.age = age
        self.tel = tel
        print(self.name, self.age, self.tel)

student1 = student("John","25","55")
print(student1.name)
print(student1.age)
print(student1.tel)