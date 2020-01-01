"""Tests the audacity pipe.
Keep pipe_test.py short!!
You can make more complicated longer tests to test other functionality
or to generate screenshots etc in other scripts.
Make sure Audacity is running first and that mod-script-pipe is enabled
before running this script.
Requires Python 2.7 or later. Python 3 is strongly recommended.
"""

import os
import sys

class AudacityPipe(object):
    def __init__(self):
        self.TONAME = ''
        self.FROMNAME = ''
        self.EOL = ''
        if sys.platform == 'win32':
            print("audacity pipe is running on windows")
            self.TONAME = '\\\\.\\pipe\\ToSrvPipe'
            self.FROMNAME = '\\\\.\\pipe\\FromSrvPipe'
            self.EOL = '\r\n\0'
        else:
            print("audacity is running on linux or mac")
            self.TONAME = '/tmp/audacity_script_pipe.to.' + str(os.getuid())
            self.FROMNAME = '/tmp/audacity_script_pipe.from.' + str(os.getuid())
            self.EOL = '\n'
        
        print("Write to  \"" + self.TONAME +"\"")
        if not os.path.exists(self.TONAME):
            print(" ..does not exist.  Ensure Audacity is running with mod-script-pipe.")
            sys.exit()
        
        print("Read from \"" + self.FROMNAME +"\"")
        if not os.path.exists(self.FROMNAME):
            print(" ..does not exist.  Ensure Audacity is running with mod-script-pipe.")
            sys.exit()
        
        print("-- Both pipes exist.  Good.")
        
        self.TOFILE = open(self.TONAME, 'w')
        print("-- File to write to has been opened")
        self.FROMFILE = open(self.FROMNAME, 'rt')
        print("-- File to read from has now been opened too\r\n")


    def __send_command(self, command):
        """Send a single command."""
        print("Send: >>> \n"+command)
        self.TOFILE.write(command + self.EOL)
        self.TOFILE.flush()
    
    def __get_response(self):
        """Return the command response."""
        result = ''
        line = ''
        while line != '\n':
            result += line
            line = self.FROMFILE.readline()
            #print(" I read line:["+line+"]")
        return result
    
    def do_command(self, command):
        """Send one command, and return the response."""
        self.__send_command(command)
        response = self.__get_response()
        print("Rcvd: <<< \n" + response)
        return response

    def import_audio(self, file_path):
        self.do_command('Import2: Filename=' + file_path)

