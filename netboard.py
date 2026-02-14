import serial
import time
import subprocess

# configure port
ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    # throw ping command towards Google
    output = subprocess.run(['ping', '-c 1', '8.8.8.8'], capture_output=True, text=True).stdout
  
    # extract response time
    if "time=" in output:
        time_ms = output.split("time=")[1].split("ms")[0]
        print(f"Ping: {time_ms}ms")
        ser.write(f"{time_ms}\n".encode()) # send to Arduino
    
    time.sleep(1)