import subprocess
import os
import sys
# iterare tutti i file di una directory, eseguire il comando shell per avere l'output di file -i, mettere in un dizionario dove la chiave e' il tipo di file e il valore e' il nome del file, stampare il dizionario

directory = sys.argv[1] if len(sys.argv[1])> 0 else '.' 
files = {}
for file in os.listdir(directory):
    res = subprocess.run(['file', directory+file], stdout=subprocess.PIPE).stdout.decode('utf-8')
    name, type = res.split(':')
    type = type.split(',')[0]
    if type in files.keys():
        files[type].append(name)
        break
    else:
        files[type] = [name]

for type, name in files.items():
    print(type.replace('\n', '')+": "+" ".join(name).replace(directory, ''))

