from tkinter import *
import requests

root = Tk()
play_button=PhotoImage(file='001-switch-on.png')
pause_button=PhotoImage(file='002-toggle.png')
forward_button=PhotoImage(file='003-forwards.png')
backward_button=PhotoImage(file='004-backward.png')
temp_logo=PhotoImage(file='001-thermometer.png')
wind_logo=PhotoImage(file='002-wind-energy.png')
map_logo=PhotoImage(file='003-map.png')
humidity_logo=PhotoImage(file='004-humidity.png')

def device_button_click(value):
    if(value==0):
        off_button.grid_forget()
        switch_on()
    elif(value==1):
        on_button.grid_forget()
        switch_off()

def switch_on():
    global on_button
    on_button = Button(root, font=('calibri', 30, 'bold'),bg='#81BDE6',padx=40,foreground='black',compound="right",image=play_button,command=lambda: device_button_click(1))
    on_button.grid(row=0, column=1, sticky='nw')
def switch_off():
    global off_button
    off_button = Button(root,font=('calibri', 30, 'bold'),bg='#81BDE6',foreground='black',compound="right",image=pause_button,command=lambda: device_button_click(0))
    off_button.grid(row=0, column=1,sticky='nw')

switch_off()
switch_on()



root.mainloop()
"""

#    appliances7.grid_forget()
#    appliances8.grid_forget()
#    appliances9.grid_forget()
#    appliances10.grid_forget()
    if(x==1):
        x=str(100*room_name + 10*device_current_no+1)
        device_bin_value=1
        s.send(bytes(x, 'utf-8'))
#        device_power_status=s.recv(1024).decode()
    else:
        x = str(100 + 10 * device_current_no + 2)
        device_bin_value=0
        s.send(bytes(x, 'utf-8'))
#        device_power_status=s.recv(1024).decode()
#    device_status_frame()
"""
