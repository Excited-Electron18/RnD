#from File_Access import log_erase,log_write,log_Start

class ABC:
    A = 4
    B = 3
    C = "ABC"

    def Print_Var(self):
        print("Print_Var in ABC : %d" %(self.A))

class XYZ:
    X = 5
    Y = 6
    Z = "XYZ"

    def Print_Var(self):
        print("Print_Var in XYZ : %d" %(self.Y))     

class Class_TEST1():
    Obj_ABC = ABC()
    Obj_XYZ = XYZ()

    def Test_result(self):
        print("Test_result %d %d " % (self.Obj_ABC.A,self.Obj_XYZ.X) )

def Class_TEST2():
    Obj_TEST = Class_TEST1()
    Obj_ABC1 = ABC()
    Obj_XYZ1 = XYZ()
  #  log_erase()
   # log_Start()
    Obj_TEST.Test_result()

   # log_write(Obj_TEST.Obj_ABC.B)
   # log_write(str(Obj_ABC1.A))
    #log_write(str(Obj_XYZ1.Y))
