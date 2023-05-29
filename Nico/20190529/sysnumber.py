import subprocess, sys

sc = subprocess.run(["gcc", "-dD", "-E", "-"], input=b"#include <sys/syscall.h>", stdout=subprocess.PIPE).stdout.decode().split("\n# 21 \"/usr/include/asm/unistd.h\" 2 3 4")[0].split("_ASM_UNISTD_64_H")[1].strip()
list = ["#include <stdio.h>\n", "#include <string.h>\n", "#include <ctype.h>\n", "#include <stdlib.h>\n"]
sysname = []
number = []
for line in sc.splitlines():
    if line.startswith("#define __NR"):
        sysname.append(line.replace("__NR_", "").split(" ")[1])
        number.append(line.replace("__NR_", "").split(" ")[-1])
new_list = [f'\tsyscall[{x}] = "{y}";\n' for x, y in zip(number, sysname)]
list.extend(["int main(int argc, char *argv[]){\n", "\tchar *syscall[449] = {","};\n"])
list.extend(new_list)
list.extend(["    int length = strlen (argv[1]);\n    int isnumber = 1;\n    for (int i=0;i<length; i++){\n        if (!isdigit(argv[1][i])){\n            isnumber = 0;\n            break;\n        }\n    }\n", "\tfor(int i = 0; i < 449; i++){\n", "\t\tif(syscall[i] == NULL) continue;\n","\t\tif(strcmp(syscall[i], argv[1]) == 0) ",' printf("%d\\n", i);\n', '\t\tif(isnumber && i == atoi(argv[1])) printf("%s\\n", syscall[i]);\n\t}\n', "\treturn(0);", "\n}\n"])
c = open('sysnumber.c', 'w')
c.writelines(list)
c.close()
