"""Beautifying the VOS source code is the first step of code cleaning.
"""

import os 
import code_cleaner


# get the dictionary of all configurations of the config file. The value in this dics is not valid
def get_all_configurations(macro_config_file):
    # macro config table, the returned dictionary after execution
    macro_config_table = {}
    #open the file
    config_file = open(macro_config_file, 'r')

    header_name = os.path.basename(macro_config_file)
    file_macro_define = (header_name.replace('.', '_')).upper()
    for line in config_file.readlines():
        if file_macro_define not in line:             # eliminate the macro def at start of config header file
            # delete the space and \n 
            # comment following the code is not allowed
            line = line.replace('\n', '')
            line = line.replace(' ', '')
            line = line.replace('\t', '')
            if "#define" == line[0:7]:
                macro_config_table[line[7:-1]] = int(line[-1])
    #don't forget to close the file
    config_file.close()
    return macro_config_table

# 1. add VOS_ to macro configuration of VOS source code
# 2. add the end-indicator after the comment

def VOS_config_complete(input_source_file, output_file):
#    macro_config_table = get_all_configurations(macro_config_file)
#    config_list = macro_config_table.keys()
    in_file = open(input_source_file, 'r')
    out_file = open(output_file, 'w')
    macro_if_else_pair_list = []
    macro_if_end_pair_list = []
    for in_line in in_file.readlines():
        dummy_input_line = in_line.replace(' ', '')
        dummy_input_line = dummy_input_line.replace('\n', '')
        dummy_input_line = dummy_input_line.replace('\t', '')
        if '#if' == dummy_input_line[0:3]:
            macro_if_else_pair_list.append(dummy_input_line[3:])
            macro_if_end_pair_list.append(dummy_input_line[3:])
            start_index = in_line.index('#')
            out_file.writelines(in_line[start_index:])
        elif '#else' == dummy_input_line[0:5]:
            new_line = dummy_input_line[0:5] + "    // " + macro_if_else_pair_list[-1] + "\n"
            macro_if_else_pair_list.pop()
            out_file.writelines(new_line)
        elif '#endif' == dummy_input_line[0:6]:
            new_line = dummy_input_line[0:6] + "    // " + macro_if_end_pair_list[-1]  + "\n"
            if len(macro_if_else_pair_list):
                if macro_if_end_pair_list[-1] == macro_if_else_pair_list[-1]:
                    macro_if_else_pair_list.pop()
            macro_if_end_pair_list.pop()
            out_file.writelines(new_line)
        else:
            out_file.writelines(in_line)
    if len(macro_if_end_pair_list):
        print("if-end pair list isn't empty! The following items stay in the list:")
        print(macro_if_end_pair_list)
    if len(macro_if_else_pair_list):
        print("if-else pair list isn't empty! The following items stay in the list:")
        print(macro_if_else_pair_list)
    in_file.close()
    out_file.close()
            
        

