import os
import subprocess
import sys

test_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                        'tests')

def run_test(test_filename):
    exit_code = subprocess.call([sys.executable, test_filename])
    
    test_result_dir = os.path.join(test_dir, '..', 
        '_' + os.path.basename(test_filename).replace('.', '_'))
    test_result_file = os.path.join(test_result_dir, 'result.txt')
    
    if os.path.isfile(test_result_file) and file(test_result_file).read().strip() == 'PASS':
        return True
        
    return False

def run_all_tests():
    test_result_list = []
    
    for dirpath, dirnames, filenames in os.walk(test_dir):
        for filename in filenames:
            if filename.endswith('.py') and not filename.startswith('_'):
                test_path = os.path.join(dirpath, filename)
                test_result = {'name': os.path.relpath(
                    test_path, test_dir)}
                test_result['result'] = run_test(test_path)                
                test_result_list.append(test_result)
                
    print('='*70)
    all_tests_pass = True
    for test_result in test_result_list:
        if test_result['result']:
            print 'PASS',
        else:
            print 'FAIL',
            all_tests_pass = False
        print(test_result['name'])
        
    if all_tests_pass:
        print('PASS')
    else:
        print('FAIL')

if __name__ == "__main__":
    run_all_tests()
