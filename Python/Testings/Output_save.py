import time;

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

def f(x,y):     # Function from where results will come
  z0 = 1582379255.22592
  z1 = "M2.DataIn"
  z2 = x+y
  z3 = x-y
  z4 = x*y
  z5 = 9530309824
  z6 = 12994845628
  z7 = 293402972
  z8 = 143395747
  z9 = 6453422820
  z10 = 0
  z11 = 6345138
  z12 = x/y
  return (z0,z1,z2,z3,z4,z5,z6,z7,z8,z9,z10,z11,z12)


log_erase()     # Log file Erase
log_Start()     # Log file Erase
A0 = f(10,5)    # First result of Function
A1 = f(20,12)   # Second result of Function

A2 = [0,0,0,0,0,0,0,0,0,0,0]

print(A0)
Log_str = "\nFirst Output : " + str(A0)
log_write(Log_str)
print(A1)
Log_str = "\nSecond Output : " + str(A1)
log_write(Log_str)

for i in range(len(A1)-2):
        A2[i] = A1[i+2] - A0[i+2]   # Diffrence of results of Function
        
print(A2)
Log_str = "\nDiffrence in Outputs : " + str(A2)
log_write(Log_str)
