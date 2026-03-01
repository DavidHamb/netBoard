# Execute with root privileges in order to access /dev/ttyACM0

import serial
import time
import subprocess

if subprocess.run('whoami', capture_output=True, text=True).stdout == "root\n":
    # configure port
    ser = serial.Serial('/dev/ttyACM0', 9600)

    while True:
        # throw ping command towards Google
        output = subprocess.run(['ping', '-c 1', '8.8.8.8'], capture_output=True, text=True).stdout
    
        # extract response time
        if "time" not in output:
            ser.write("9999\n".encode())
            print("Network unavailable")

        else:
            if "time=" in output:
                time_ms = output.split("time=")[1].split("ms")[0]
                print(f"Ping: {time_ms}ms")
                ser.write(f"{time_ms}\n".encode()) # send to Arduino
        
            time.sleep(1)

else:
    print("Please run the program as root")