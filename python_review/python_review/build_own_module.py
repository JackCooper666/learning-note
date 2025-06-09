__all__ = ['testA','test']
# __all__ can only restrict "from module_name import *"
def test(a,b):
    print(a+b)
def testA():
    print("testA")
def testB():
    print("testB")


"""
the comments in the main, only be executed when the module is running.
Thus, the comments will not be executed, when the module is imported.
"""
if __name__ == '__main__':
    test(1,2)