import serial
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=.1) # velger port og overføringshastighet

write_to_file_path = "output.txt"; # velger filnavn 

while True:
    data = arduino.readline()[:-2] #leser serial dataen og fjerner \n på slutten
    if len(data) > 0: # kjører bare om det er noe data
        print data
        line = data.decode("utf-8")+ ";" # konverterer til streng og legger til semikolon

        # skriver posisjonen til fil
        with open(write_to_file_path, 'w') as the_file:
            the_file.write(line)
