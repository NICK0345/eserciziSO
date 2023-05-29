# Esercizio 3: Python o bash: 10 punti
# Sia data una directory che contiene file di testo.
# Scopo dell'esercizio e' di scrivere un programma Python o uno script bash chiamato ccpl che conti i
# caratteri delle corrispondenti righe di testo di tutti i file della directory, si vuole cioe' sapere il numero
# totale di caratteri presenti nelle prime righe di tutti i file, nelle seconde linee, ecc.
# $ ccpl mydir
# 1 234
# 2 21
# 3 333
# …..
# l'ouput significa che se contiamo tutti i caratteri contenuti nella prima riga di tutti i file in mydir
# otteniamo 234 (mydir/file1 puo' avere 40 caratteri nella prima riga, mydir/file2 ne puo' avere 20, ecc...
# procedendo per tutti i file di mydir la somma fa 234).
# data una dir accedo a una dir, e accedo a soli file di testo, conto riga per riga i caratteri e le stampo

import os
import sys

if(len(sys.argv) < 2):
    print("Too few arguments")
    exit()

if not os.path.isdir(sys.argv[1]):
    print("argv[1] is not a directory")
    exit()

files = [os.path.join(sys.argv[1], f) for f in os.listdir(sys.argv[1]) if os.path.isfile(os.path.join(sys.argv[1], f))]

list = []

for file in files:
    with open(file) as f:
        ind = 1
        for line in f:
            if(ind >= len(list)):
                list.append(len(line))
            else:
                list[ind] += len(line)
            ind += 1

for i in range (0, len(list)):
    print(f"{i+1} {list[i]}")



