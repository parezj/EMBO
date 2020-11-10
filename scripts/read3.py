import serial
import time
import datetime
import numpy as np
import math
import matplotlib.pyplot as plt

channels = 2
ch_buff_len = 500
buff_len = ch_buff_len * channels * 2

ser = serial.Serial('COM12', 115200, timeout=1, 
    parity=serial.PARITY_NONE, 
    stopbits=serial.STOPBITS_ONE, 
    bytesize=serial.EIGHTBITS)

ser.write(str.encode("*IDN?\r\n"))
time.sleep(0.1)
print(ser.readline())


plt.ion()
fig=plt.figure()
fig.canvas.set_window_title('UniLabTool - Demo')
it = 0        
no_trig = str.encode("\"0\"\r\n")

major_ticks_x = np.arange(0, ch_buff_len + 50, 50)
minor_ticks_x = np.arange(0, ch_buff_len, 10)
major_ticks_y = np.linspace(0, 3.3, 10)
minor_ticks_y = np.linspace(0, 3.3, 20)

try:
    while True:
        start_time = datetime.datetime.now()
        ser.write(str.encode("SCOPE:READ:ALL?\r\n"))
        #time.sleep(0.3)
        
        total_len = buff_len + 8
        data = ser.read(total_len)
        end_time = datetime.datetime.now()
                
        if (data == no_trig):
            print("waiting for trigger...")
            print("-----------")
            continue
        if (len(data) != total_len):
            print("-----------")
            print("Invalid data:")
            print(data)
            continue
            

        data = data[6:-2]
        buff_raw = np.frombuffer(data, dtype=np.uint8)

        buff = []
        for i in range(0, int(len(buff_raw) / 2)):
            j = i * 2
            buff.append((buff_raw[j + 1] << 8 | buff_raw[j]))
             
        ch1 = []  
        ch2 = []  

        for i in range(0, int(len(buff) / channels)):
            j = i * channels
            ch2.append(float(buff[j] / 10000.0))
            ch1.append(float(buff[j + 1] / 10000.0))
            
        t = np.arange(len(ch1))
        time_diff = (end_time - start_time)
        el = time_diff.total_seconds() * 1000

        print(str(it) + f"., {(float(len(data)) / 1024.0):.1f} KB, " + str(int(el)) + " ms")
        print("ch1: " + f"{ch1[0]:.4f} V" )
        print("ch2: " + f"{ch2[0]:.4f} V")
        print("-----------")
        plt.clf()
        plt.plot(t, ch1, 'b', label="ch1", linewidth=1.0)
        plt.plot(t, ch2, 'g', label="ch2", linewidth=3.0)
        plt.legend(loc="lower right")
        plt.xlabel("samples")
        plt.ylabel("voltage")
        ax = plt.gca()
        ax.set_xticks(major_ticks_x)
        ax.set_xticks(minor_ticks_x, minor=True)
        ax.set_yticks(major_ticks_y)
        ax.set_yticks(minor_ticks_y, minor=True)
        ax.grid(which='major', alpha=0.9)
        plt.grid(True, linestyle=':')
        plt.ylim(0, 3.3)
        plt.xlim(0, ch_buff_len)
        plt.axvline(x=int(ch_buff_len / 2), color='k', linestyle='--', linewidth=2.5, alpha=0.8)
        plt.axhline(y=3.3 / 2.0, color='k', linestyle='--', linewidth=2.5, alpha=0.8)
        plt.show()
        plt.pause(0.0001)
        it = it + 1
        
except KeyboardInterrupt:
    pass

ser.close()