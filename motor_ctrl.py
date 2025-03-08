import serial
import keyboard

# Open serial connection
arduino = serial.Serial(arduino_port="COM3", baud_rate=9600, timeout=0.1)

def send_command(command):
    arduino.write(command.encode())

try:
    print("'W' to move forward, 'S' to move backward. Release to stop.")

    while True:
        if keyboard.is_pressed('w'):  # Move Forward
            send_command('f')
        elif keyboard.is_pressed('s'):  # Move Backward
            send_command('b')
        else:  # No key pressed -> Stop motor
            send_command('s')

except KeyboardInterrupt:
    print("Stopping program.")
    send_command('s')  # Stop motor before exiting
    arduino.close()
