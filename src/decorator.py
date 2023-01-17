def load(local = False):
    
    def decorated_my_lambda(func):
        if local == False:
            func()
        else:
            print("will pass")
            pass
    return decorated_my_lambda


@load(local = False)
def my_lambda():
    print(f"This is the silvester")


def main():
    my_lambda()

if __name__ == '__main__':
    main()



