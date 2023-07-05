##import numpy as np
##import pandas as pd
##import requests
##import xlsxwriter
##import math
##import yfinance as yf
##import plotly.graph_objs as go
##import matplotlib.pyplot as plt
from nsetools import Nse
##from nsepython import *

print("Import Done")

nse = Nse()
print("Data Request Start")
if(nse.is_valid_code("TCS")):
    data = nse.get_quote("TCS")
    print(data)
else:
    print("Invalid Code")

nse.get_stock_codes()
##print(data['lastPrice'])
##print("previousClose : ",nse_eq("TCS")['priceInfo']['previousClose'])
##print("open : ",nse_eq("TCS")['priceInfo']['open'])
##print("close : ",nse_eq("TCS")['priceInfo']['close'])
##print("lastPrice : ",nse_eq("TCS")['priceInfo']['lastPrice'])

