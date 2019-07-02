"""code cleaner test
Usage:
    code_clean_test.py clean_file <input_config_file> [<output_file>]
    code_clean_test.py clean_folder <folder_needs_clean> <folder_to_output>
    code_clean_test.py -h|--help

Options: 
    -h --help                                   Show this screen.
"""

from docopt import docopt
import os
import glob
import code_cleaner
import vos_code_beautician as vcb

args = docopt(__doc__)

print(args)

try:
    if args['clean_file'] is True:
    
        input_file = args['<input_source_file>']
    
        if args['<output_file>'] is not None:
            output_file =args['<output_file>']
        else:
            output_file = "./cleaner_output.c"
    
        vcb.VOS_config_complete(input_file, output_file)
    elif args['clean_folder'] is True:
        input_folder = args['<folder_needs_clean>']
        in_exist = os.path.exists(input_folder)
        print(in_exist)
        if not in_exist:
            raise ValueError("Input folder path doesn't exist!", input_folder)
        output_folder = args['<folder_to_output>']
        if not os.path.exists(output_folder):
            os.makedirs(output_folder)
        filelist = glob.glob(input_folder+'*.c') + glob.glob(input_folder+'*.h')
        for f in filelist:
            out_f = output_folder + '/' + os.path.basename(f) 
            print("Processing file: %s" % os.path.basename(f))
            vcb.VOS_config_complete(f, out_f)
            print("Done...")
except ValueError:
    print("Input folder path doesn't exist." % input_folder)
