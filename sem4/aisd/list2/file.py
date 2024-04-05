def func(x, y, z):
    print(x, y, z)
    
def func_test(*args):
    func(*args)
    
func_test(2, 3 ,4)