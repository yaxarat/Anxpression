import firebase_admin   
from firebase_admin import credentials
from firebase_admin import firestore
import time

cred = credentials.Certificate('.\silent-oasis-220015-feb6eb71fb17.json')
default_app =  firebase_admin.initialize_app(cred)

db = firestore.client()

while (1==1):
    doc_ref1 = db.collection(u'Readings').document(u'Heart Rate')
    doc1 = doc_ref1.get()
    BPM = u'Heart Rate: {}'.format(doc1.to_dict())
    BPM = BPM[34:36]
    print(BPM)

    doc_ref2 = db.collection(u'Readings').document(u'Humidity')
    doc2 = doc_ref2.get()
    humid = u'Humidity: {}'.format(doc2.to_dict())
    humid = humid[26:28]
    print(humid)

    doc_ref3 = db.collection(u'Readings').document(u'Temperature')
    doc3 = doc_ref3.get()
    temp = u'Temperature: {}'.format(doc3.to_dict())
    temp = temp[26:28]
    print(temp)

    doc_ref4 = db.collection(u'Readings').document(u'Noise')
    doc4 = doc_ref4.get()
    loud = u'Noise: {}'.format(doc4.to_dict())
    loud = loud[17]
    print(loud)

    time.sleep(2)


    

    
    
