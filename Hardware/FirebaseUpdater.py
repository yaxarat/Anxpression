import serial
import firebase_admin
import random
from firebase_admin import credentials
from firebase_admin import firestore

cred = credentials.Certificate('.\silent-oasis-220015-feb6eb71fb17.json')
firebase_admin.initialize_app(cred)

db = firestore.client()
i = 0
s = serial.Serial('COM11', baudrate = 9600)

while(1==1):
    arduinoData = s.readline().decode('ascii')
    heartRate = arduinoData[0:3]
    humid = arduinoData[3:5]
    temp = arduinoData[5:7]
    loud = arduinoData[7]
    Result = [heartRate, humid, temp, loud] 
    print(Result)
    doc_ref = db.collection(u'Readings')
    doc_ref.document(u'Heart Rate').set({
        u'Beats per Minute': heartRate
    })
    doc_ref.document(u'Humidity').set ({
        u'Percentage': humid
    })
    doc_ref.document(u'Temperature').set({
        u'Celcius': temp
    })
    doc_ref.document(u'Noise').set({
        u'Loud': loud
    })