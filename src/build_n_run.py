import subprocess
import os
import re

def bash(command):
    arr = command.split()
    res = None
    try:
        res = subprocess.check_output(arr)
    except BaseException as error:
        print('error, an exception occurred: {}'.format(error))
    if res is None:
        return
    #print("command '"+command+"' result:")

    #for line in res.splitlines():
        #print("\t",line)

    return res

def coverage_percent(gcov_out):
    gcov_out = gcov_out.decode("utf-8")
    lines_covered = 0
    all_lines = 0

    for block in gcov_out.split("\n\n"):
        func_out = block.splitlines()

        if len(func_out) < 2:
            continue

        # TODO: if curr function is not in test project pass
        #if projectName not in func_out[1]:
        #    pass

        if "Lines executed" in func_out[1]:
            func_info = re.findall(r"[-+]?\d*\.\d+|\d+", func_out[1])
            func_info = [float(i) for i in func_info]
            lines_covered += round(0.01*func_info[0]*func_info[1])
            all_lines += func_info[1]

    return lines_covered/all_lines

folder = "what_we_test"
os.chdir(folder)

folder = "build-cov"
#remove the folder and contents
#bash("pwd")
#bash("ls")
bash("rm -rf "+folder)
#bash("ls")

try:
    os.makedirs(folder)
except OSError as e:
    print("error " + e)

os.chdir(folder)
#bash("pwd")

projName = "string_distance_test"
projPath = "../Root/Haming/" + projName + "/" + projName + ".pro"

bash("qmake "+projPath)
bash("make -B")
fileName = "tst_"+projName 
bash("./"+fileName)
#gcov_out = bash("gcov "+fileName+".cpp")

gcov_out = bash("gcov string_distance.cpp")
cvg_percent = coverage_percent(gcov_out)
print("%.6f" % cvg_percent)
