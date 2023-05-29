# Esercizio 3: Python o bash: 10  punti
# Scrivere   uno   script   bash   o   python   difidr   che   date   due   directory   ne   crei   una   terza   e   una   quarta
# Le nuove directory devono contenere solamente i file aventi lo stesso nome  presenti nella prima e nella seconda
# albero. Ogni file della terza directory deve contenere una copia del file nella versione della prima directory,
# mentre nella quarta directory la versione della seconda.
# es.
# * se la direcotry a contiene i file alpha, beta, gamma, delta e la directory b i file beta, delta, epsilon, zeta
# il comando "difdir a b newa newb" crea le directory newa e newb ed entrambe le directory devono
# contenere solo beta e delta (i nomi in comune). newa/beta deve essere una copia di a/beta mentre
# newb/beta una copia di b/beta. In modo simile per a/delta b/delta newa/delta e newb/delta.
# controllare se ci sono file nomi presenti in entrambi le directory se si', copiare a/file su anew/file, b/file su bnewfile

import os
import sys
import shutil

def search_file(directory = None, file = None):
    assert os.path.isdir(directory)
    for cur_path, directories, files in os.walk(directory):
        if file in files:
            return os.path.join(cur_path, file)
    return None

if(len(sys.argv) == 5):
    if not os.path.exists(sys.argv[3]):
        os.mkdir(sys.argv[3])
    if not os.path.exists(sys.argv[4]):
        os.mkdir(sys.argv[4])
    for path, subdir, files in os.walk(sys.argv[1]):
        for file in files:
            res = search_file(sys.argv[2], file)
            if res:
                if not os.path.exists(os.path.join(sys.argv[3], file)):
                    shutil.copy(os.path.join(path, file), os.path.join(sys.argv[3], file))
                if not os.path.exists(os.path.join(sys.argv[4], file)):
                    shutil.copy(res, os.path.join(sys.argv[4], file))