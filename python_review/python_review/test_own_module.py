import build_own_module

build_own_module.test(1,2)

from build_own_module import *
# import * can only import the functions which are allowed in the "__all__".
# Thus the testB() cannot be imported
testA()