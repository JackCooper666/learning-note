class animal: # abstract class is the class who has abstract method, it is a kind of top design
    def voice(self): # abstract method
        pass

class dog(animal):
    def voice(self):
        print("wof, wof")

class cat(animal):
    def voice(self):
        print("miao, miao")

def make_noise(Animal:animal):
    Animal.voice()

my_dog = dog()
my_cat = cat()
make_noise(my_dog)
make_noise(my_cat)