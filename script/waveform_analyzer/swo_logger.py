import pylink
try:
    import StringIO
except ImportError:
    import io as StringIO
import string
import sys
import time
import subprocess
from jlinkhelper import *

device_choice = input("Please select connected device:\n1. Apollo\n2.Apollo2 or Apollo2Blue\n3.Apollo3\n")

if device_choice == "1":
    device = "APOLLO512-KBR"
elif device_choice == "2":
    device = "AMAPH1KK-KBR"
elif device_choice == "3":
    device = "AMA3B1KK-KBR"

log_path = input("Please input SWO log file name: ")
    
# To solve terminal print crush in Windows
sys.stdout = StringIO.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

exit(serial_wire_viewer(device, log_path))
