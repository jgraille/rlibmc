def load(local):
    if local:
        params = {"key":"this is local"}
    else:
        params = {"key":"this is not local"}
        
    def decorated_my_lambda(func):
        def wrapper(*args,**kwargs):
            if local is False:
                print(params)
                func(*args,**kwargs)
            else:
                print("passing")
                pass
        return wrapper
    return decorated_my_lambda

@load(local = True)
def my_lambda(event,context):
    print(f"This is the {event}")
    print(f"The context is {context}")


my_lambda(event = "Silverster", context = "cold")



