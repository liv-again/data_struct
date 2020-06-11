import os
import sys
import chardet

a = os.listdir(os.getcwd())
for file in a:
    if ".cpp" in file:
        print(file)
        content = ''
<<<<<<< HEAD
        with open(file,mode= 'rb') as e:
            content = e.read()
        enc = chardet.detect(content).get('encoding')
        with open(file,mode= 'r+',encoding=enc) as e:
=======
        with open(file,mode= 'r+',encoding='gb2312') as e:
>>>>>>> f57c84a00ddb7c1690ff73befa01771038786a85
            content = e.read()
        with open(file,mode= 'wb') as e:
            e.write(content.encode('utf8'))
        
            #print(e.read())