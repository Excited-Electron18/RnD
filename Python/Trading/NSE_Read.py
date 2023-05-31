import numpy as np
import pandas as pd
import requests
import xlsxwriter
import math
import yfinance as yf
import plotly.graph_objs as go
import matplotlib.pyplot as plt
from nsetools import Nse
from nsepython import *

print("Import Done")

nse = Nse()
print("Data Request Start")
data = nse.get_quote("TCS")
print(data)

##print(data['lastPrice'])
##print("previousClose : ",nse_eq("TCS")['priceInfo']['previousClose'])
##print("open : ",nse_eq("TCS")['priceInfo']['open'])
##print("close : ",nse_eq("TCS")['priceInfo']['close'])
##print("lastPrice : ",nse_eq("TCS")['priceInfo']['lastPrice'])

