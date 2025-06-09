class iphone13:
    IMEI = None
    producer = "USA, amazon"

    def call_by_5g(self):
        print("Fucking 5g calling")

class iphone14(iphone13):
    producer = "China, Taiwan" # modify father's member variables

    def call_by_5g(self):      # modify father's member behaviors
        print("CPU one core mode")
        print("5g calling")
        print(f"the previous producer {iphone13.producer}")
        print("CPU two cores mode")
        iphone13.call_by_5g(self)

my_phone = iphone14()
my_phone.call_by_5g()
print(my_phone.producer)