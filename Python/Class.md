# def \_\_init\_\_(self):

`__init__()` is a special method in Python known as the **initializer** or **constructor**. It is automatically called when a new instance (object) of a class is created. This method is used to initialize the object's attributes or perform any setup that is needed when the object is instantiated.
### Example with Default Arguments:
```python
class Person:
    def __init__(self, name="Unknown", age=0):
        self.name = name
        self.age = age

# Create an instance with default values
person1 = Person()

# Create an instance with custom values
person2 = Person("Alice", 30)

print(f"{person1.name} is {person1.age} years old.")
print(f"{person2.name} is {person2.age} years old.")
```
### Output:
```pgsql
Unknown is 0 years old.
Alice is 30 years old.
```

# def \_\_del\_\_(self):

In Python, `__del__` is a special method known as the **destructor**. It is called when an object is about to be destroyed (i.e., when it is no longer referenced, and its memory is being reclaimed). The `__del__` method is used to define cleanup actions or resource management tasks that need to be performed before the object is removed from memory.

```python
class MyClass:
    def __init__(self):
        print("Object created")

    def __del__(self):
        print("Object destroyed and cleanup done")

# Create an instance of MyClass
obj = MyClass()

# Delete the object manually (not necessary, just for demonstration)
del obj
```
### When is `__del__` called?

- **Garbage Collection**: Python uses a garbage collector to automatically manage memory. When an object is no longer referenced (i.e., there are no variables or references pointing to it), it becomes eligible for garbage collection. If an object has a `__del__` method, it will be called as part of the cleanup process.
    
- **Program Shutdown**: When the program ends, Python tries to clean up all remaining objects. If there are objects still alive (referenced), their `__del__` methods will be called as part of this process. However, the order in which objects are destroyed can affect whether `__del__` is called during shutdown.
