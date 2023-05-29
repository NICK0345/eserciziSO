# Esercizio 3: Python o bash: 10 punti
# Scrivere uno script bash o un programma python che preso come parametro un pattern (stringa
# ASCII) fornisca in output l'elenco dei file che contengono il pattern presenti nel sottoalbero dell
# directory corrente.. La lista di output deve essere ordinata dal file più recentemente modificato al file
# con ultima modifica più remota.
# inazittutto devo salvare in un vettore tutti file del sottoalbero della current directroy, poi a seconda del tempo di modifica li sorto
import sys, os
import re

pattern = input("Enter pattern: ")
pattern = re.compile(pattern)
root = "./"
list = []
for path, subdirs, files in os.walk(root):
    for name in files:
        filename = os.path.join(path, name)
        textfile = open(filename, 'r', encoding="ISO-8859-1")
        filetext = textfile.read()
        textfile.close()
        if(re.search(pattern, filetext)):
            list.append(filename)

list = sorted(list, key=lambda t: os.stat(t).st_mtime)
print(list)