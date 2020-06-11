import os
import sys
import chardet

a = os.listdir(os.getcwd())
for file in a:
    if ".cpp" in file:
        print(file)
        content = ''
        with open(file,mode= 'rb') as e:
            content = e.read()
        enc = chardet.detect(content).get('encoding')
        with open(file,mode= 'r+',encoding=enc) as e:
            content = e.read()
        with open(file,mode= 'wb') as e:
            e.write(content.encode('utf8'))
        
            #print(e.read())