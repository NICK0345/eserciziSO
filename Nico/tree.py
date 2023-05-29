# Esercizio 3: Python o bash: 10 punti
# Scrivere uno script bash o un programma python che preso come parametro un pattern (stringa
# ASCII) fornisca in output l'elenco dei file del sottoalbero che ha come radice la directory corrente che
# nel loro contenuto includano il pattern. La lista di output deve essere ordinata dal file più
# recentemente modificato al file con ultima modifica più remota.
from os import listdir, walk
from os.path import isfile, join, getmtime
import sys, re

if len(sys.argv) < 2:
    exit()
root = "."
match = []
for path, subdirs, files in walk(root):
    for file in files:
        with open(join(path,file)) as f:
            try:
                if re.search(sys.argv[1], f.read()):
                    match.append(join(path,file))
            except UnicodeDecodeError:
                continue
match.sort(key=lambda x:-getmtime(x))
print(match)