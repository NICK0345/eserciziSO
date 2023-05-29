import subprocess
import os
import sys
# Esercizio 3: Python o bash: 10 punti
# Scrivere un programma python o uno script bash che esaminando i dati in /proc/*/status fornisca in
# output una tabella che indichi per ogni processo di proprietà dell'utente, il nome dell'eseguibile e
# l'attuale occupazione di memoria (campo vmSize).
# iterare tutti i file di una directory, eseguire il comando shell per avere l'output di file -i, mettere in un dizionario dove la chiave e' il tipo di file e il valore e' il nome del file, stampare il dizionario
dict = {"name": [], "mem": []}
id = os.getuid()
for thread in os.listdir("/proc/"):
    print(thread)
    out = subprocess.run(['cat', "/proc/"+thread+"/status"], stdout=subprocess.PIPE).stdout.decode('utf-8')
    info = out.split('\n')
    for line in info:
        n = ""
        size = ""
        if line.startswith('Name'):
            n = line.split('\t')[1]
            print(line)
        if line.startswith('VmSize'):
            size = line.split('\t')[1]
            print(line)
        if line.startswith('Uid'):
            uid = line.split('\t')[1]
            print(line)
            if uid == str(id):
                dict["name"] = dict["name"].append(n)
                dict["mem"] = dict["mem"].append(size)

# import os, subprocess

# uid = os.getuid()
# res = {}
# maxnamelenght = 0
# print("uid: "+str(uid))
# for pid in os.listdir("/proc"):
#     status = str(subprocess.run(["cat", "/proc/"+pid+"/status"], stderr=subprocess.DEVNULL, stdout=subprocess.PIPE).stdout).split("\\n")
#     print(status)
#     if len(status)>1 and int(status[8].split("\\t")[1]) == uid:
#         name = status[0].split("\\t")[1]
#         res[name] = status[17].split("\\t")[1].strip()
#         maxnamelenght = maxnamelenght if len(name)<maxnamelenght else len(name)
# print("Nome processo".ljust(maxnamelenght, " ")+"\t\tOccupazione in memoria")

# for name, size in res.items():
#     print(name.ljust(maxnamelenght, " ")+"\t\t"+size)
