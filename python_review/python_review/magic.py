""""
magic methods:
1.  __str__
2.  __lt__ : do comparison "<," between two objects
3.  __le__ : do comparison "<=" and ">=," between two objects
4.  __eq__ : do comparison "=," between two objects
"""
class student:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def __str__(self):
        return f"{self.name} is {self.age} years old"
    def __lt__(self, other):
        return self.age < other.age
    def __le__(self, other):
        return self.age <= other.age
    def __eq__(self, other):
        return self.age == other.age

student1 = student('Jack', 25)
student2 = student('Cooper', 30)
print(student1)
print(student2)
print(str(student1))
print(student1 < student2)
print(student1 > student2)
print(student1 <= student2)
print(student1 >= student2)
print(student1 == student2)
print(student1 != student2)