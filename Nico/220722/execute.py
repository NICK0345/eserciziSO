import subprocess
import os
import sys
directory = sys.argv[1] if len( sys.argv ) > 1 else '.'
files = {}
for file in os.listdir(directory):
    if(file != 'execute.py'):
        if(file.endswith('.py')):
            subprocess.run(['python3', file, directory])
        elif(file.endswith('.sh')):
            subprocess.run(['.', file])
