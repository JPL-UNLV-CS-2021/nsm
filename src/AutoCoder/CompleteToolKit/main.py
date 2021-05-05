import os
import sys

if len(sys.argv) != 3:
    print("Usage:")
    print("\tmain.py <StateMachineXMLFile> <StateMachineEventInput>")
    quit()

os.chdir("Generator")
os.system("cmake Generation")
os.system("cmake --build .")
os.chdir("../")
os.system("parser.py " + sys.argv[1])
os.system("Generator/debug/generation.exe JSON/qsmIn.json")
os.chdir("Output_Files/generated_code")
os.system("mkdir build")
os.chdir("build")
os.system("cmake ../")
os.system("cmake --build .")
os.chdir("../../../")
os.system("Output_Files/generated_code/build/Debug/GeneratedHSM.exe in.txt")
