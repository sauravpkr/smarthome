from tkinter import Tk, Scale

root = Tk()

w = Scale(root, from_=0, to=200)
w.grid(row=0,column=0)
w.set(200)  # Set the initial value to 100
p="OFF"
if(p=="OFF"):
    print("Correct")
else:
    print("Not Correct")


root.mainloop()