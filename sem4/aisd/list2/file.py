def func(x, y, z):
    print(x, y, z)
    
def func_test(*args):
    func(*args)

def f1(arr):
    arr[1], arr[2] = arr[2], arr[1]

my_arr = [1, 3, 2]
f1(my_arr.copy())
print(my_arr)