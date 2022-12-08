from __future__ import annotations
import time
from typing import Optional
import serial
from pathlib import Path

from threading import Thread

from collections import deque

from rich import get_console

from random import randint

console = get_console()

DUMMY = 128



def guess_arduino_port() -> str|None:
    candidates = list(Path('/dev/').glob('ttyACM*'))

    if len(candidates) == 0:
        return None

    if len(candidates) == 1:
        return str(candidates[0])

    return sorted([str(p) for p in candidates])[0]


class NoArduinoError(Exception):
    ...



class ArduinoCarrito:
    def __init__(
        self, 
        port: str|None=None, *,
        read_interval: float = 0.5,
        max_buffer_size: int = 256
    ):
        self.serial = serial.Serial()
        
        self.connect(port)
        
        """clear the serial buffer"""
        self.serial.read_all()

        self.read_interval = read_interval
        self.serial_buffer = deque([], maxlen=max_buffer_size)

        self._listen_thread = Thread(target=self._listen, daemon=True)
        self._listen_thread.start()

    def connect(
        self, 
        port: Optional[str]=None, *, 
        open: bool=True, guess: bool=True
    ):
        """
        Connect to arduino serial port
        """

        if port is None:
            if guess:
                self.serial.setPort(guess_arduino_port())
        else:
            self.serial.setPort(port)

        if self.serial.port is None:
            raise NoArduinoError()

        if open:
            self.serial.open()

    def _listen(self):
        while True:
            try:
                time.sleep(self.read_interval)
                while self.serial.in_waiting > 0:
                    bs = self.serial.readline()
                    self.serial_buffer.append(bs)

            except IOError as e:
                self.serial.close()
                self.connect()

            except Exception as e:
                console.log(f'Error ocurred in listening thread: {repr(e)}')

    def peek_serial(self):
        if len(self.serial_buffer) > 0:
            return self.serial_buffer[-1]
        else:
            return ''

    def forward(self, speed: int):
        self.write(bytes([0,1,speed,DUMMY,DUMMY]))

    def backward(self, speed: int):
        self.write(bytes([0,2,speed,DUMMY,DUMMY]))

    def left(self, speed: int):
        self.write(bytes([0,3,speed,DUMMY,DUMMY]))

    def right(self, speed: int):
        self.write(bytes([0,4,speed,DUMMY,DUMMY]))

    def stop(self):
        self.write(bytes([0,5,DUMMY,DUMMY,DUMMY]))

    def move_servo(self, angle: int):
        self.write(bytes([0,6,angle,DUMMY,DUMMY]))

    def write(self, s: str|bytes):
        if type(s) is str:
            self.serial.write(s.encode())

        if type(s) is bytes:
            self.serial.write(s)

    def fill(self, c: int, n: int):
        """
        write c n times
        """
        self.write(bytes([c for _ in range(n)]))


