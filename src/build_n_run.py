import subprocess
import os
import re
import sys
import glob, os

def bash(command):
    arr = command.split()
    res = None
    try:
        res = subprocess.check_output(arr, stderr=subprocess.STDOUT)
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
    branches_covered = 0
    all_branches = 0
    taken_branches = 0
    if len(gcov_out) == 0:
        return 0,0,0,0,0

    for block in gcov_out.split("\n\n"):
        func_out = block.splitlines()
        if len(func_out) < 2:
            continue

        if func_out[0].find("file is newer than notes") != -1:
            func_out = func_out[2:]


        # TODO: if curr function is not in test project pass
        #if projectName not in func_out[1]:
        #    pass

        if "Lines executed" in func_out[1]:
            func_info = re.findall(r"[-+]?\d*\.\d+|\d+", func_out[1])
            func_info = [float(i) for i in func_info]
            lines_covered += round(0.01*func_info[0]*func_info[1])
            all_lines += func_info[1]
        
        if "Branches executed" in func_out[2]:
            func_info = re.findall(r"[-+]?\d*\.\d+|\d+", func_out[2])
            func_info = [float(i) for i in func_info]
            branches_covered += round(0.01*func_info[0]*func_info[1])
            all_branches += func_info[1]
        
        if "Taken at least once" in func_out[3]:
            func_info = re.findall(r"[-+]?\d*\.\d+|\d+", func_out[3])
            func_info = [float(i) for i in func_info]
            taken_branches += round(0.01*func_info[0]*func_info[1])
    # print(gcov_out)      
    # print(all_lines, all_branches)
    return lines_covered, all_lines, branches_covered, taken_branches, all_branches

pathToProj = ""
executableName = ""
sourcePath = ""

if len(sys.argv) == 4:
    pathToProj = sys.argv[1]
    executableName = sys.argv[2]
    sourcePath = sys.argv[3]
else:
    exit("Error, need pathToProject, executableName and sourcePath")

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

bash("qmake "+pathToProj)
bash("make -B")
bash("./"+executableName)
gcov_out = bash("gcov -b " + executableName)

files = os.listdir(".")
#print(files)
joinWith = "" if sourcePath.endswith("/") else "/"
cppFiles = [os.path.basename(x) for x in glob.glob(sourcePath + joinWith + "*.cpp")]
cvg_percent = None

sumLinesCovered= sumAllLines= sumBranchesCovered= sumBranchesTaken= sumAllBranches = 0
for cpp in cppFiles:
    #print("F" +cpp)
    gcov_out = bash("gcov -b " + cpp) #"string_distance.cpp")
    lines_covered, all_lines, branches_covered, taken_branches, all_branches = coverage_percent(gcov_out)
    sumLinesCovered += lines_covered
    sumAllLines += all_lines
    sumBranchesCovered += branches_covered
    sumBranchesTaken += taken_branches
    sumAllBranches += all_branches

print("%.6f %.6f %.6f" % (sumLinesCovered/sumAllLines, sumBranchesCovered/all_branches, sumBranchesTaken/all_branches))
