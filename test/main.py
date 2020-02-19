from tkinter import *


root = Tk()

# create a menu bar
menubar= Menu(root)
root.config(menu=menubar)

# create a submenu
submenu= Menu(menubar,tearoff=0)
menubar.add_cascade(label="File",menu=submenu)
submenu.add_command(label="Add new Widget")
submenu.add_command(label="open")
submenu.add_command(label="exit")

# create a submenu
submenu= Menu(menubar,tearoff=0)
menubar.add_cascade(label="Help",menu=submenu)
submenu.add_command(label="How  to connect")

submenu=Menu(menubar,tearoff=0)
menubar.add_cascade(label="About us",menu=submenu)
submenu.add_command(label="contact")


root.geometry('300x300')
root.title("Web Home")
root.iconbitmap(r'home.ico')

text = Label(root,text="Welcome")
text.grid(row=0,column=0)

photo=PhotoImage(file='001-couch.png')
photo1=PhotoImage(file='001-home.png')
photo2=PhotoImage(file='001-couch.png')
photo3=PhotoImage(file='001-couch.png')
photo4=PhotoImage(file='001-couch.png')
photo5=PhotoImage(file='001-couch.png')

def fan_on(val):
    x=int(val)
    if(x==0):
        print("Fan gets OFF")
    if(x==1):
        print("Fan gets ON")
def play():
    print("Hello")

middlframe = Frame(root)
middlframe.grid(row=1,column=1)

button=Button(middlframe,image=photo,bg='green',anchor='w',text="ON",command=play)
button2=Button(middlframe,image=photo2,bg='green',anchor='w',text="ON",command=play)
button3=Button(middlframe,image=photo3,bg='green',anchor='w',text="ON",command=play)
button4=Button(middlframe,image=photo4,bg='green',anchor='w',text="ON",command=play)
button5=Button(middlframe,image=photo5,bg='green',anchor='w',text="ON",command=play)
slide=Scale(middlframe,fg='red',orient=HORIZONTAL,from_=0,to=1,command=fan_on)
button1=Button(middlframe,image=photo1,bg='green',anchor='w',text="ON",command=play)
slide.pack()
button1.pack(side=LEFT,padx=10)
button2.pack(side=LEFT,padx=10)
button3.pack(side=LEFT,padx=10)
button4.pack(side=LEFT,padx=10)
button5.pack(side=LEFT,padx=10)

root.mainloop()