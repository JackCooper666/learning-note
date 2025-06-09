class phone:
    __is_5g_enable = False
    def __check_59(self):
        if self.__is_5g_enable:
            print("5g enabled")
        else:
            print("5g disabled")
    def call_by_5g(self):
        self.__check_59()
        print("calling")

myphone = phone()
myphone.call_by_5g()
