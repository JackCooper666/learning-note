"""

import module_name
from module_name import class, variable, function, method
from module_name import *
import module_name as alias
from module_name import function_name as alias

"""


"""
import module_name1, module_name2
module_name1.function_name()
"""
import time
time.sleep(1)

"""
from module_name1 import function_name,class_name,variable,function,method
function_name()
"""
from time import sleep
sleep(1)

"""
from module_name1 import * # import all the content of the module
function_name()
"""
from time import *
sleep(1)