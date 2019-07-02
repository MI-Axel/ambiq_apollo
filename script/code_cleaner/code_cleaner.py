"""clean the unused code in the source file
"""

import os

def get_config(macro_config_file):
    # macro config table, the returned dictionary after execution
    macro_config_table = {}
    # indicate the code block is used or not
    code_block_using = 1

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
            if "#define" == line[0:7] and code_block_using == 1:
                macro_config_table[line[7:-1]] = int(line[-1])
            elif "#if" == line[0:3]:
                if "||" in line: 
                    or_config_sublist = line[3:].split("||")
                    for config in or_config_sublist:
                        if macro_config_table[config] == 1:
                            code_block_using = 1
                elif "&&" in line:
                    and_config_sublist = line[3:].split("&&")
                    config_combo_result = 1
                    for config in and_config_sublist:
                        if macro_config_table[config] == 0:
                            config_combo_result = 0
                    if config_combo_result == 1:
                        code_block_using = 1
                elif line[3:] in macro_config_table.keys() and macro_config_table[line[3:]] == 1:
                    code_block_using = 1
                else:
                    code_block_using = 0
            elif "#endif" == line[0:6] or "#else" == line[0:5]: 
                code_block_using = 0
    #don't forget to close the file
    config_file.close()
    return macro_config_table

# garbage code cleaner 
def c_code_clean(input_file, macro_config_file, output_file):
    configuration_table = get_config(macro_config_file)
    # common code block flag
    common_code_block = 1
    # configuration code block flag
    config_code_block = 0
    # indicating whether the config code block using or not
    code_block_using = 0
    input_file = open(input_file, 'r')
    output_file = open(output_file, 'w')
    for input_line in input_file.readlines():
        dummy_input_line = input_line.replace(' ', '')
        dummy_input_line = dummy_input_line.replace('\n', '')
        dummy_input_line = dummy_input_line.replace('\t', '')
        if "#if" == dummy_input_line[0:3]:
            common_code_block = 0
            config_code_block = 1
            if dummy_input_line[3:] in configuration_table.keys() and configuration_table[dummy_input_line[3:]] == 1:
                code_block_using = 1
            else:
                code_block_using = 0
            output_file.writelines("\n")
        elif "#else" == dummy_input_line[0:5]:
            if code_block_using == 1:
                code_block_using = 0
            else:
                code_block_using = 1
        elif "#endif" == dummy_input_line[0:6]:
            common_code_block = 1
            config_code_block = 0
            code_block_using = 0
            output_file.writelines("\n")
        elif common_code_block == 1 and config_code_block == 0:
            output_file.writelines(input_line)
        elif config_code_block == 1 and code_block_using == 1 and common_code_block == 0:
            output_file.writelines(input_line)

    input_file.close()
    output_file.close()




