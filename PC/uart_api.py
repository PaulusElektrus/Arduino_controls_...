import serial


class UART_API:
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.serial_port = serial.Serial(self.port, self.baudrate)
        print(f"The Port name is {self.serial_port.name}")

    def read(self):
        line = self.serial_port.read(self.serial_port.inWaiting())
        line = line.decode()
        return line

    def write(self, data):
        self.serial_port.write(data.encode(encoding = 'ascii', errors = 'strict'))

    def close(self):
        self.serial_port.close()

