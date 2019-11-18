import serial
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1)

write_to_file_path = "output.txt";

while True:
    data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
    if len(data) > 0:
        print data
        line = data.decode("utf-8") #ser.readline returns a binary, convert to string
        with open(write_to_file_path, 'w') as the_file:
            the_file.write(line)
            #the_file.write("\n")
