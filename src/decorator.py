def decorated_my_lambda(func):
    def wrapper():
        local = False
        if local is False:
            print("Local is false")
            func()
        else:
            print("passing")
            pass
    return wrapper

@decorated_my_lambda
def my_lambda():
    print(f"This is the silvester")


my_lambda()



