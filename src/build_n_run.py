import subprocess
import os
print("hi")

def bash(command):
    arr = command.split()
    res = subprocess.check_output(arr)
    for line in res.splitlines():
        print("fromPy:",line)

folder = "what_we_test"
os.chdir(folder)
folder = "build-cov"
try:
    os.makedirs(folder)
except OSError as e:
    print(e)

os.chdir(folder)

bash("ls")
bash("rm *")
bash("ls")

