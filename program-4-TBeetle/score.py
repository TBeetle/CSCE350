import pathlib
import shutil
import os
import subprocess

unit_test_exec = './runUnitTests'

build_path = './build'

def run_named_test(test_exec, test_name, score_if_passed):

    try:
        subprocess.check_call([test_exec, '--gtest_filter='+test_name+'*'])
        return score_if_passed
    except subprocess.CalledProcessError:
        return 0


#clean and remake dir
try:
    shutil.rmtree(build_path)
except:
    print('no ' + build_path+' to delete')

pathlib.Path(build_path).mkdir(parents=True,exist_ok=True)


#make runUnitTests in build dir
old_cwd = os.getcwd()
os.chdir('./build')

subprocess.run(['cmake', '..'])
subprocess.run(['make'])
subprocess.run([unit_test_exec])

test_wts = []
test_wts.append( ('ex_8_11_Warshalls', 10) )
test_wts.append( ('run_Slides_War_1', 10) )
test_wts.append( ('test_Floyd_slide_1', 10) )
test_wts.append( ('test_Floyd_slide_2', 10) )
test_wts.append( ('test_anyAnagrams', 60) )

score = 0
for (test,wt) in test_wts:
    score = score + run_named_test(unit_test_exec,test,wt)
print ("SCORE= "+str(score))

os.chdir(old_cwd)
