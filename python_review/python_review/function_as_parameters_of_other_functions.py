def test_func(compute):
    result = compute(5,4)
    print(f"the type of the compute: {type(compute)}")
    print(result)

def compute(x,y):
    return x+y

test_func(compute)