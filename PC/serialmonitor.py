import argparse
import uart_api
from time import sleep

if __name__ == "__main__":

    print("Welcome to Serial Monitor")
    
    ap = argparse.ArgumentParser()
    ap.add_argument("-p", "--port", default="/dev/ttyUSB0", help="Enter Port Name")
    ap.add_argument("-b", "--baudrate", default=9600, help="Enter Baud rate")
    args = ap.parse_args()

    uart = uart_api.UART_API(args.port, args.baudrate)

    while True:
        try:
            print(uart.read())
            sleep(1)
        except KeyboardInterrupt:
            user_input = input("Enter data to send or enter nothing to read further: ")
            if user_input == "":
                pass
            else:
                uart.write(user_input)
                sleep(0.1)
