class phone:
    name = None
    manufacturing_ID = None
    __current_voltage = 5      # private member variable, can only be applied by internal variables and behavior
    def __manager_right(self): # private member behavior, can only be applied by internal variables and behavior
        print("welcome, manager")

    def arrow_io(self):
        if self.__current_voltage >= 5:
            print("game start")
        else:
            print("game end")
            self.__manager_right()

iphone = phone()
iphone.arrow_io()

