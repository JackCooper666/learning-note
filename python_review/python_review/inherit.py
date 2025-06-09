# Father class
class iphone_13:
    IMEI = None
    producer = "Chinese Fushikang"
    def call_by_4g(self):
        print("4g call")

class xiaomi:
    def NFC(self):
        print("NFC_reader")
    def IR_remoter(self):
        print("IR_remoter")

# Son class
# Single inherit
"""

class son_class(Father_class_name):
    members.....
"""
class iphone_14(iphone_13):
    face_id = True
    def call_by_5g(self):
        print("5g call")

# multiple inherit
"""

the inheriting priority of Father_1 > Father_2 > Father_3 > Father_4

class son_class(Father_class_1_name, Father_class_2_name, Father_class_3_name, Father_class_4_name):
    members.....

"""
class oppo(iphone_14,xiaomi):
    pass
my_phone = iphone_14()
my_phone.call_by_4g()
print(my_phone.producer)
my_oppo = oppo()
my_oppo.call_by_5g()
my_oppo.NFC()
my_oppo.call_by_4g()