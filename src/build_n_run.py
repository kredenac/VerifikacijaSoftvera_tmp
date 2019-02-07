import subprocess
import os
print("hi")

def bash(command):
    arr = command.split()
    res = None
    try:
        res = subprocess.check_output(arr)
    except BaseException as error:
        print('An exception occurred: {}'.format(error))
    if res is None:
        return
    print("command '"+command+"' result:")

    for line in res.splitlines():
        print("\t",line)

folder = "what_we_test"
os.chdir(folder)

folder = "build-cov"
#remove the folder and contents
bash("pwd")
bash("ls")
bash("rm -rf "+folder)
bash("ls")

try:
    os.makedirs(folder)
except OSError as e:
    print(e)

os.chdir(folder)
bash("pwd")

projName = "string_distance_test"
projPath = "../Root/" + projName + "/" + projName + ".pro"

bash("qmake "+projPath)
bash("make -B")
fileName = "tst_"+projName 
bash("./"+fileName)
bash("gcov "+fileName+".cpp")


print("bye")