# -*- coding: utf-8 -*-
#
# Jlink command tools by pthon.
#
# This module provide both SWD viewer and flash downloader python interface
# and command line interface

usage = """
 Usage: jlinkhelper.py [d/v] device [file-path] [addr] [jlink_serial_number] 

        d/v/l: d is to download, 
               v is a real-time SWO viewer,
               l i s to list the j-link devices
        file-path: flash file, or swo log file
        addr: flash download start address
"""

import pylink

try:
    import StringIO
except ImportError:
    import io as StringIO
import string
import sys
import time
import subprocess

def connect_target(device, jlink_serial=None):
    JLINK_RESET = '''\
        device {part}
        si SWD
        speed 1000
        connect
        exit
        '''
    cmdfile = open('connect.jlink', 'w')
    cmdfile.write(JLINK_RESET.format(part=device))
    cmdfile.close()
    if sys.platform == 'darwin':
        # in Mac OS
        JLink_CL = "JLinkExe"
    elif sys.platform == 'win32':
        JLink_CL = "jlink.exe"

    if (jlink_serial == None):
      subprocess.run([JLink_CL,
                      "-Device", device,
                      "-If", "SWD",
                      "-Speed", "1000",
                      "-ExitOnError", "1"
                      "-CommandFile", "connect.jlink"])
    else:
      subprocess.run([JLink_CL,
                      "-Device", device,
                      "-SelectEmuBySN", jlink_serial,
                      "-If", "SWD",
                      "-Speed", "1000",
                      "-ExitOnError", "1"
                      "-CommandFile", "connect.jlink"])

def reset_target(device, jlink_serial=None):
    JLINK_RESET = '''\
        device {part}
        si SWD
        speed 1000
        connect
        rx 1000
        g
        exit
        '''
    cmdfile = open('reset.jlink', 'w')
    cmdfile.write(JLINK_RESET.format(part=device))
    cmdfile.close()
    if sys.platform == 'darwin':
        # in Mac OS
        JLink_CL = "JLinkExe"
    elif sys.platform == 'win32':
        JLink_CL = "jlink.exe"

    if (jlink_serial == None):
      subprocess.run([JLink_CL,
                      "-Device", device,
                      "-If", "SWD",
                      "-Speed", "1000",
                      "-ExitOnError", "1"
                      "-CommandFile", "reset.jlink"])
    else:
      subprocess.run([JLink_CL,
                      "-Device", device,
                      "-SelectEmuBySN", jlink_serial,
                      "-If", "SWD",
                      "-Speed", "1000",
                      "-ExitOnError", "1"
                      "-CommandFile", "reset.jlink"])

def flash_downloader(device, path, addr, jlink_serial=None):
    """Implements a flash downloader.

    A flash downloaer allows us to download binary to target

    Args:
      jlink_serial (str): the J-Link serial number
      device (str): the target CPU
      path: the binary file path

    Returns:
      Always returns ``0``.

    Raises:
      JLinkException: on error
    """
    print("J-link download " + device + " file " + path)
    buf = StringIO.StringIO()
    jlink = pylink.JLink(log=buf.write, detailed_log=buf.write)
    jlink.open(serial_no=jlink_serial)

    # Use Serial Wire Debug as the target interface.  Need this in order to use
    # Serial Wire Output.
    jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
    jlink.connect(device, verbose=True)
    jlink.flash_file(path, addr)
    #if (device != 'AMA3B1KK-KBR'):
    #  jlink.coresight_configure()
    #  jlink.set_reset_strategy(pylink.enums.JLinkResetStrategyCortexM3.CORE)

    #  # Have to halt the CPU before getitng its speed.
    #  # jlink.reset()
    #  # jlink.halt()

    #  # Reset the core without halting so that it runs.
    #  jlink.reset(ms=1000, halt=False)
    #else:
    jlink.close()
    reset_target(device, jlink_serial)

swo_running = False

def serial_wire_viewer(device, path="", jlink_serial=None):
    """Implements a Serial Wire Viewer (SWV).

    A Serial Wire Viewer (SWV) allows us implement real-time logging of output
    from a connected device over Serial Wire Output (SWO).

    Args:
      jlink_serial (str): the J-Link serial number
      device (str): the target CPU
      path: the log file path

    Returns:
      Always returns ``0``.

    Raises:
      JLinkException: on error
    """
    global swo_running
    buf = StringIO.StringIO()
    jlink = pylink.JLink(log=buf.write, detailed_log=buf.write)
    jlink.open(serial_no=jlink_serial)

    # Use Serial Wire Debug as the target interface.  Need this in order to use
    # Serial Wire Output.
    jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
    jlink.connect(device, verbose=True)
    jlink.coresight_configure()
    jlink.set_reset_strategy(pylink.enums.JLinkResetStrategyCortexM3.CORE)

    # Have to halt the CPU before getitng its speed.
#    jlink.reset()
#    jlink.halt()

    cpu_speed = 47860   #jlink.cpu_speed()   # 47860
    swo_speed = 1000000 # jlink.swo_supported_speeds(cpu_speed, 10)[9]

    # Start logging serial wire output.
    jlink.swo_start(swo_speed)
    jlink.swo_flush()

    # Output the information about the program.
    sys.stdout.write('Reading data from port 0:\n\n')
    # To solve file write crush in Windows
    f = open(path, "w", encoding='utf-8')

    # Reset the core without halting so that it runs.
    #jlink.reset(ms=10, halt=False)
    connect_target(device, jlink_serial)
    swo_running = True
    log_line = []
    # Use the `try` loop to catch a keyboard interrupt in order to stop logging
    # serial wire output.
    try:
        while swo_running:
            # Check for any bytes in the stream.
            num_bytes = jlink.swo_num_bytes()

            if num_bytes == 0:
                # If no bytes exist, sleep for a bit before trying again.
                time.sleep(0.1)
                continue

            data = jlink.swo_read_stimulus(0, num_bytes)
            # transfer to ASCII encode
            data_str = ''.join(map(chr, data))
            data_list = list(data_str)
            for idx, item in enumerate(data_list):
                log_line.append(item)
                if item == '\n':
                    ct = time.time()
                    local_time = time.localtime(ct)
                    data_head = time.strftime("%Y-%m-%d %H:%M:%S", local_time)
                    data_secs = (ct - int(ct)) * 1000
                    time_stamp = "%s.%03d" % (data_head, data_secs)
                    log_line.insert(0, '['+time_stamp+'] ')
                    data_str = "".join(log_line)
                    sys.stdout.write(data_str)
                    f.write(data_str)
                    sys.stdout.flush()
                    f.flush()
                    log_line = []
#                else:
#                    log_line.append(item)
    except KeyboardInterrupt:
        pass

    sys.stdout.write('\n')
    f.write('\n')
    f.close()

    # Stop logging serial wire output.
    jlink.swo_stop()

    return 0

def go_and_expect_swo(device, keyword, reset = False, breakpoint = None, timeout = 5, jlink_serial=None):
    """Implements a Serial Wire Viewer (SWV).

    A Serial Wire Viewer (SWV) allows us implement real-time logging of output
    from a connected device over Serial Wire Output (SWO).

    Args:
      jlink_serial (str): the J-Link serial number
      device (str): the target CPU
      path: the log file path

    Returns:
      Always returns ``0``.

    Raises:
      JLinkException: on error
    """
    global swo_running
    buf = StringIO.StringIO()
    jlink = pylink.JLink(log=buf.write, detailed_log=buf.write)
    jlink.open(serial_no=jlink_serial)

    # Use Serial Wire Debug as the target interface.  Need this in order to use
    # Serial Wire Output.
    jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
    jlink.connect(device, verbose=True)
    jlink.coresight_configure()
    jlink.set_reset_strategy(pylink.enums.JLinkResetStrategyCortexM3.CORE)

    # Have to halt the CPU before getitng its speed.
    #if reset:
    #  jlink.reset()
    jlink.halt()

    # set breakpoint 
    jlink.breakpoint_clear_all()
    jlink.breakpoint_set(breakpoint)

    #cpu_speed = jlink.cpu_speed()   # 47860
    swo_speed = 1000000 # jlink.swo_supported_speeds(cpu_speed, 10)[9]

    # Start logging serial wire output.
    jlink.swo_start(swo_speed)
    jlink.swo_flush()

    # Output the information about the program.
    sys.stdout.write('Reading data from port 0:\n\n')

    # Reset the core without halting so that it runs.
    if (reset):
      reset_target(device, jlink_serial)
    else:
      jlink._dll.JLINKARM_Go()
    swo_running = True
    log = ''

    # Use the `try` loop to catch a keyboard interrupt in order to stop logging
    # serial wire output.
    try:
        while swo_running:
            # Check for any bytes in the stream.
            num_bytes = jlink.swo_num_bytes()

            if num_bytes == 0:
                if (timeout == 0):
                  break
                else:
                  timeout == 1
                # If no bytes exist, sleep for a bit before trying again.
                time.sleep(1)
                continue

            data = jlink.swo_read_stimulus(0, num_bytes)
            log.join(map(chr, data)) 
            sys.stdout.write(''.join(map(chr, data)))
            sys.stdout.flush()
            if (log.find(keyword)):
              return True
        return False
    except KeyboardInterrupt:
        pass
        return False
        
    finally:
      sys.stdout.write('\n')
      # Stop logging serial wire output.
      jlink.swo_stop()

    return 0
def list_devices():
    """list current j-link device serial numbers

    Returns:
      Always returns ``0``.

    Raises:
      JLinkException: on error
    """
    jlink = pylink.JLink()
    print(" *** Found these Jlink devices ***")
    l = jlink.connected_emulators()
    for j in l:
        print("\t" + str(j.SerialNumber))

if  __name__ == '__main__':
    # To solve terminal print crush in Windows
    sys.stdout = StringIO.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
    if (len(sys.argv) == 1):
        print(usage)
        list_devices()
    elif (sys.argv[1].lower() == 'd'):
        if (sys.argv.count == 5):
            flash_downloader(sys.argv[2], sys.argv[3], sys.argv[4])
        if (sys.argv.count == 6):
            flash_downloader(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
    elif (sys.argv[1].lower() == 'v'):
        exit(serial_wire_viewer(sys.argv[2], sys.argv[3]))
    else:
        list_devices()
