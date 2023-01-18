import functools

def do_twice(func):
    @functools.wraps(func)    
    def wrapper_do_twice(*args, **kwargs):
        func(*args, **kwargs)
        return func(*args, **kwargs)
    return wrapper_do_twice

@do_twice
def say_whee():
    print("Whee!")

@do_twice
def return_greeting(name):
    print("Creating greeting")
    return f"Hi {name}"

say_whee()
hi_angel = return_greeting("Angel")
print(hi_angel)

print(say_whee.__name__)
