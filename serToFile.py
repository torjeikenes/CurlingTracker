###############
### Script listens to serial port and writes contents into a file
###############
### requires pySerial to be installed 
#import serial  # sudo pip install pyserial should work
#
#serial_port = '/dev/ttyACM0';
#baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
#write_to_file_path = "output.txt";
#
#output_file = open(write_to_file_path, "w+");
#ser = serial.Serial(serial_port, baud_rate)
#while True:
#    line = ser.readline();
#    line = line.decode("utf-8") #ser.readline returns a binary, convert to string
#    print(line);
#    output_file.write(line);



import serial
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1)

write_to_file_path = "output.txt";

while True:
    data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
    if len(data) > 0:
        print data
        line = data.decode("utf-8") #ser.readline returns a binary, convert to string
        with open(write_to_file_path, 'a') as the_file:
            the_file.write(line)
            the_file.write("\n")
