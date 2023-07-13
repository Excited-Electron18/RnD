import time;
import logging;
from class_test import ABC,XYZ

def log_erase():
    log_file = open("test.log", 'r+')
    log_file.truncate(0)
    log_file.close()

def log_write(str_val):
    log_file = open("test.log", "a+")
    log_file.write(str(str_val))
    log_file.close()

def log_Start():
    localtime = time.asctime( time.localtime(time.time()) )
    Log_str = "================= " + localtime + " =================\n"
    log_write(Log_str)

def Log_TEST1():
    log_erase()
    log_Start()
    File_Rd = open("RdFile.txt", "r+")
    Log_str = File_Rd.readlines(2)
    log_write(Log_str)
    x=2
    y=3
    z=x+y
    Log_str = "\naddition : " + str(z)
    log_write(Log_str)

    logging.debug('Debugging information')
    logging.info('Informational message')
    logging.warning('Warning:config file %s not found', 'server.conf')
    logging.error('Error occurred')
    logging.critical('Critical error -- shutting down')

def Log_TEST2():
    log_erase()
    log_Start()
    Obj_ABC = ABC()
    Obj_XYZ = XYZ()
    log_write(str(Obj_ABC.A))
    log_write(str(Obj_XYZ.Y))

Log_TEST2()
Log_TEST1()

