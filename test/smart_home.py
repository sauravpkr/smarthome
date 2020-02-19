from tkinter import *
import requests
from time import strftime
import socket
from datetime import date

s= socket.socket()
s.connect(('192.168.43.208',333))
print("Connection successful")

root=Tk()
root.geometry('1080x720')
root.title("Web Home")

s.send(bytes("113",'utf-8'))

def room_button_click(x):
    global room_name
    room_name = x
    global c
    x=str(room_name*100+device_current_no*10+3)
    s.send(bytes(x,'utf-8'))
    print(room_name)

def device_button_click(y):
    global device_current_image
    global device_current_no
    global conn
    global device_power_status

    appliances7.grid_forget()
    appliances8.grid_forget()
#    appliances9.grid_forget()
    appliances10.grid_forget()
    appliances11.grid_forget()                      ######################## 9_2 ######################
    device_current_no = y
    x = str(100 + 10 * device_current_no + 3)
    s.send(bytes(x, 'utf-8'))
    device_power_status = s.recv(1024).decode()
    global device_bin_value
    if(device_power_status=="OFF"):
        device_bin_value=0
        on_button.grid_forget()
        switch_off()
    elif(device_power_status=="ON"):
        device_bin_value=1
        off_button.grid_forget()
        switch_on()
    if(y==1):
        device_current_image=device_1
        print(1)
    elif(y==2):
        device_current_image=device_2
        print(2)
    elif(y==3):
        device_current_image=device_3
    elif(y==4):
        device_current_image=device_4
    elif(y==5):
        device_current_image=device_5
    else:
        device_current_image=device_6
    device_status_frame()
#    switch_off()
    return
def device_status(value):
    global room_name
    global device_current_no
    global device_power_status
    global device_bin_value
#    appliances7.grid_forget()
#    appliances8.grid_forget()
#    appliances9.grid_forget()
#    appliances10.grid_forget()
    if(value==1):
        x=str(100*room_name + 10*device_current_no+1)
        device_bin_value=1
        s.send(bytes(x, 'utf-8'))
        on_button.grid_forget()
        switch_off()
#        device_power_status=s.recv(1024).decode()
    elif(value==0):
        x = str(100 + 10 * device_current_no + 2)
        device_bin_value=0
        s.send(bytes(x, 'utf-8'))
        off_button.grid_forget()
        switch_on()
#        device_power_status=s.recv(1024).decode()
#    device_status_frame()
    return

# ########################### room image ######################

room_1=PhotoImage(file='001-home.png')
room_2=PhotoImage(file='003-bed.png')
room_3=PhotoImage(file='002-living-room.png')
room_4=PhotoImage(file='shower.png')
room_5=PhotoImage(file='003-kitchen.png')
room_6=PhotoImage(file='005-book.png')
room_7=PhotoImage(file='004-dressing-room.png')
#   ######  device image ###################
device_1=PhotoImage(file='005-lightbulb.png')
device_2=PhotoImage(file='006-fan.png')
device_3=PhotoImage(file='007-screen.png')
device_4=PhotoImage(file='010-fridge.png')
device_5=PhotoImage(file='009-router.png')
device_6=PhotoImage(file='004-lamp.png')
temp_logo=PhotoImage(file='001-thermometer.png')
wind_logo=PhotoImage(file='002-wind-energy.png')
map_logo=PhotoImage(file='003-map.png')
humidity_logo=PhotoImage(file='004-humidity.png')
sun_logo=PhotoImage(file='005-solar.png')
play_button=PhotoImage(file='001-play.png')
pause_button=PhotoImage(file='002-pause.png')
forward_button=PhotoImage(file='003-forwards.png')
backward_button=PhotoImage(file='004-backward.png')
switch_on_logo=PhotoImage(file='002-toggle.png')
switch_off_logo=PhotoImage(file='001-switch-on.png')
party_on_logo=PhotoImage(file='trumpet.png')
party_off_logo=PhotoImage(file='stop.png')


#   ################################ global variable ##############################

# ####################### global variable ######################################
device_bin_value=0
device_power_status = s.recv(1024).decode()
if(device_power_status=="ON"):
    device_bin_value=1
elif(device_power_status=="OFF"):
    device_bin_value=0
device_current_image = device_1
device_current_name = ["Bulb","Fan","TV","Fridge","Router","Night Lamp"]
# device_image_list=[device_1,device_2,device_3,device_4,device_5,device_6]
room_name = 1
room_name_list=["Bed Room","Living Room","Washroom","Kitchen","Study Room","Dressing Room"]
device_current_no =  1


# ###########################     creating frame starts here     ####################################
left_frame=Frame(root,borderwidth=5,highlightbackground="green",highlightthickness=1,bg='#85C1E9')
left_frame.pack(side=LEFT,anchor=NW,fill=X,expand=1)
right_frame= Frame(root,borderwidth=5,highlightbackground="green",highlightthickness=1)
right_frame.pack(side=RIGHT,anchor=NW,fill=X,expand=1)
home_frame= LabelFrame(left_frame,highlightbackground="green",highlightthickness=1,bg='#6D8AA7')
home_frame.grid(row=1,column=0,sticky=W,columnspan=3)
right1=Frame(right_frame,highlightbackground="green",highlightthickness=1,bg='#5A5E61')
right1.grid(row=0,column=0,sticky='NW')
right2=Frame(right_frame,highlightbackground="green",highlightthickness=1,bg='#5A5E61')
right2.grid(row=1,column=0,sticky='NW')
right3=Frame(right_frame,highlightbackground="green",highlightthickness=1,bg='#81BDE6')
right3.grid(row=2,column=0,sticky='NW')


# ################################# Frame creations ends here         ################################


text1=Label(left_frame,text="Smart Home (Raayathon 7)",anchor='w',font="Verdana 20 bold",pady=30,bg='#81BDE6')
text1.grid(row=0,column=0,sticky='w',columnspan=3)
text2=Label(home_frame,image=room_1,bg='#6D8AA7')
text2.grid(row=0,column=0,sticky='w',ipadx=100,ipady=10)
text3=Label(home_frame,text="All devices",anchor='c',font="Verdana 20 bold",padx=30,pady=30,bg='#6D8AA7')
text3.grid(row=0,column=1,sticky='w',ipadx=100,ipady=10)
def home():
    room1= Button(left_frame,image=room_2,fg='blue',compound="top",padx=20,pady=10,text="Bed Room",bg='#D1F2EB',command=lambda: room_button_click(1))
    room1.grid(row=2,column=0,sticky='w',ipadx=40,pady=60,padx=10)
    room2= Button(left_frame,image=room_3,fg='blue',compound="top",padx=20,pady=10,text="Living Room",bg='#D1F2EB')
    room2.grid(row=2,column=1,sticky='w',ipadx=40,pady=60,padx=10)
    room3= Button(left_frame,image=room_4,fg='blue',compound="top",padx=20,pady=10,text="WashRoom",bg='#D1F2EB')
    room3.grid(row=2,column=2,sticky='w',ipadx=40,pady=60,padx=10)
    room4= Button(left_frame,image=room_5,fg='blue',compound="top",padx=20,pady=10,text="Kitchen",bg='#D1F2EB')
    room4.grid(row=3,column=0,sticky='w',ipadx=40,pady=60,padx=10)
    room5= Button(left_frame,image=room_6,fg='blue',compound="top",padx=20,pady=10,text="Study Room",bg='#D1F2EB')
    room5.grid(row=3,column=1,sticky='w',ipadx=40,pady=60,padx=10)
    room6= Button(left_frame,image=room_7,fg='blue',compound="top",padx=20,pady=10,text="Dressing Room",bg='#D1F2EB')
    room6.grid(row=3,column=2,sticky='w',ipadx=40,pady=60,padx=10)

# Creating things for right frame

def device_frame():
    appliances1= Button(right1,image=device_1,fg='blue',compound="top",text="Bulb",bg='#D1F2EB',padx=20,command=lambda: device_button_click(1) )
    appliances1.grid(row=0,column=0,padx=5,pady=5)
    appliances2= Button(right1,image=device_2,fg='blue',compound="top",text="Fan",bg='#D1F2EB',padx=20,command=lambda: device_button_click(2))
    appliances2.grid(row=0,column=2,padx=5,pady=5)
    appliances3=Button(right1,image=device_3,fg='blue',compound="top",text="TV",bg='#D1F2EB',padx=20,command=lambda: device_button_click(3))
    appliances3.grid(row=0,column=4,padx=5,pady=5)
    appliances4=Button(right1,image=device_4,fg='blue',compound="top",text="Fridge",bg='#D1F2EB',padx=20,command=lambda: device_button_click(4))
    appliances4.grid(row=1,column=0,padx=5,pady=5)
    appliances5=Button(right1,image=device_5,fg='blue',compound="top",text="Router",bg='#D1F2EB',padx=20)
    appliances5.grid(row=1,column=2,padx=5,pady=5)
    appliances6=Button(right1,image=device_6,fg='blue',compound="top",text="Night lamp",bg='#D1F2EB',padx=20)
    appliances6.grid(row=1,column=4,padx=5,pady=5)
 # ###########################################################################################


    # total appliaances # picture of appliances and status
def device_status_frame():
    global appliances7
    appliances7=Label(right1,fg='blue',text=device_power_status,anchor='nw',bg='#D1F2EB')
    appliances7.grid(row=2,column=1)
    global appliances8
    appliances8=Button(right1,image=device_current_image,fg='blue',bg='#D1F2EB',compound="top",text=device_current_name[device_current_no-1],padx=20,command=device_status)
    appliances8.grid(row=3,column=2)
#    global appliances9
#    appliances9=Scale(right1,fg='blue',orient=HORIZONTAL,from_=0,to=1,width=25,command=device_status)
#    appliances9.grid(row=3,column=3)
#    appliances9.set(device_bin_value)
    global appliances10
    appliances10=Label(right1,fg='blue',text="Intensity",anchor='n',bg='#D1F2EB')
    appliances10.grid(row=4,column=0)
    global appliances11
    appliances11=Scale(right1,orient=HORIZONTAL,bg='#D1F2EB')
    appliances11.grid(row=4,column=2)

def switch_on():
    global on_button
    on_button = Button(right1, font=('calibri', 30, 'bold'),bg='#81BDE6',foreground='black',compound="right",image=switch_on_logo,command=lambda: device_status(1))
    on_button.grid(row=3, column=3, sticky='nw')
def switch_off():
    global off_button
    off_button = Button(right1,font=('calibri', 30, 'bold'),bg='#81BDE6',foreground='black',compound="right",image=switch_off_logo,command=lambda: device_status(0))
    off_button.grid(row=3, column=3,sticky='nw')

#  ###################################################################################


#  #########################   watch   #####################
def time():
    string = strftime('%H:%M:%p')
    lbl.config(text=string)
    lbl.after(1000, time)
def date():
    today =date.today()
    lb2.config(text=today)
    lb2.after(1000, time)
def temperature():
    url = 'https://api.openweathermap.org/data/2.5/weather?q=Hyderabad&appid=e1805a62cf65eabd7a3bc745afcb9b60&units=metric'
    res = requests.get(url)
    data = res.json()
    temp = data['main']['temp']
    humidity = data['main']['humidity']
    coordinate1 = data['coord']['lon']
    coordinate2 = data['coord']['lat']
    pressure = data['main']['pressure']
    wind_speed = data['wind']['speed']

    lb4 = Label(right3, font=('calibri', 30, 'bold'), bg='#81BDE6',foreground='black', text=coordinate1, compound="right",image=map_logo)
    lb4.grid(row=0, column=0,sticky='nw')
    lb5 = Label(right3, font=('calibri', 30, 'bold'), bg='#81BDE6',foreground='black', text=coordinate2,compound="right", image=map_logo)
    lb5.grid(row=0, column=1, sticky='nw')
    lb2 = Label(right3, font=('calibri', 30, 'bold'), bg='#81BDE6', foreground='black', text=temp, compound="right",image=temp_logo)
    lb2.grid(row=1, column=0, sticky='nw')
    lb3 = Label(right3, font=('calibri', 30, 'bold'), bg='#81BDE6', foreground='black', text=humidity, compound="right",image=humidity_logo)
    lb3.grid(row=1, column=1, sticky='nw')
    lb6 = Label(right3,font=('calibri', 30, 'bold'),bg='#81BDE6',foreground='black',text=pressure,compound="right",image=temp_logo)
    lb6.grid(row=1, column=2,sticky='nw')
    lb7 = Label(right3, font=('calibri', 30, 'bold'), bg='#81BDE6', foreground='black', text=wind_speed, compound="right",image=wind_logo)
    lb7.grid(row=1, column=3,sticky='nw')
def music_function(value):
    if(value==155):
        s.send(bytes("155",'utf-8'))
    elif(value==151):
        s.send(bytes("151",'utf-8'))
    elif(value==152):
        s.send(bytes("152",'utf-8'))
    elif(value==154):
        s.send(bytes("154",'utf-8'))
    elif(value==161):
        s.send(bytes("161",'utf-8'))
    elif(value==162):
        s.send(bytes("162",'utf-8'))
def music_play():
    lb6 = Button(right2, bg='#81BDE6', foreground='black',compound="right", image=backward_button,command=lambda:music_function(155))
    lb6.grid(row=0, column=0,sticky='n')
    lb7 = Button(right2, bg='#81BDE6', foreground='black',compound="right", image=play_button,command=lambda:music_function(151))
    lb7.grid(row=0, column=1,sticky='n')
    lb8 = Button(right2, bg='#81BDE6', foreground='black',compound="right", image=pause_button,command=lambda:music_function(152))
    lb8.grid(row=0, column=2,sticky='n')
    lb9 = Button(right2, bg='#81BDE6', foreground='black',compound="right", image=forward_button,command=lambda:music_function(154))
    lb9.grid(row=0, column=3,sticky='n')
    lb10=Button(right2, bg='#81BDE6', foreground='black',compound="right", image=party_on_logo,command=lambda:music_function(161))
    lb10.grid(row=0, column=4,sticky='n')
    lb10 = Button(right2, bg='#81BDE6', foreground='black', compound="right", image=party_off_logo,command=lambda: music_function(162))
    lb10.grid(row=0, column=5, sticky='n')




lbl = Label(right3, font=('calibri', 30, 'bold'),background='#81BDE6',foreground='black')
lbl.grid(row=0,column=2,columnspan=2)
# lb2 = Label(right3, font=('calibri', 40, 'bold'),background='purple',foreground='white')
# lb2.grid(row=1,column=0)
#   ##################### watch ends here #################################

time()
# date()
home()
device_frame()
device_status_frame()
music_play()
time()
temperature()
switch_off()




root.mainloop()
