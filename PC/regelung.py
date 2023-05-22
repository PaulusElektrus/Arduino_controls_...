from time import sleep
from uart_api import UART_API

if __name__ == "__main__":

    api = UART_API("/dev/ttyUSB0", 9115200)
    
    sleep(1)

    api.write("<Laden,30>")
    sleep(0.1)

    while True:
        print(api.read())
        sleep(1)