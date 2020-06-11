import os
import sys


a = os.listdir(os.getcwd())
for file in a:
    if ".cpp" in file:
        print(file)
        content = ''
        with open(file,mode= 'r+',encoding='utf8') as e:
            content = e.read()
        with open(file,mode= 'wb') as e:
            e.write(content.encode('gb2312'))
        
            #print(e.read())