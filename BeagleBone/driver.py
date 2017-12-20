import serial
import requests

ser = serial.Serial('/dev/ttyO2', 9600)

while True:
   dataValue = ser.readline()
   requests.post('http://192.168.7.1/data', data = dataValue)
   
ser.close() 