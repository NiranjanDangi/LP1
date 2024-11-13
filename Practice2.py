#changes will be done in this code only
import tkinter as tk
from tkinter import messagebox #Change 1
window = tk.Tk()
window.title("Railway Management System")
window.geometry("420x450") #Change 2
window.config(bg="light cyan")

#Change 3
def clearWindow():
    train_label_number.delete(0,tk.END);
    train_label_name.delete(0,tk.END);
    train_label_sstation.delete(0,tk.END);
    train_label_dstation.delete(0,tk.END);
    seat_type_var.set("Select Seat Type")

#Change 4
def addTrain():
    if (train_label_number.get() and train_label_name.get() and train_label_sstation.get() and train_label_dstation.get() and seat_type_var.get() != "Select Seat Type"):
        messagebox.showinfo("Success","Train Added Successfully !! ")
    else:
        messagebox.showerror("Error","Please Fill In all the details");

tk.Label(window,text="Railway Management System",font=("Helvetica",16,"bold"),bg="light cyan").grid(row=0,column=0,columnspan=2,pady=15)

tk.Label(window,text="Train Name",font=("Arial",10,"bold"),bg="light cyan").grid(row=1,column=0,sticky="w",padx=10)
train_label_name = tk.Entry(window,width=30,relief="solid")
train_label_name.grid(row=1,column=1,padx=5,pady=5)

tk.Label(window,text="Train Number",font=("Arial",10,"bold"),bg="light cyan").grid(row=2,column=0,sticky="w",padx=10)
train_label_number = tk.Entry(window,width=30,relief="solid")
train_label_number.grid(row=2,column=1,padx=5,pady=5)

tk.Label(window,text="Source Station",font=("Arial",10,"bold"),bg="light cyan").grid(row=3,column=0,sticky="w",padx=10)
train_label_sstation = tk.Entry(window,width=30,relief="solid")
train_label_sstation.grid(row=3,column=1,padx=5,pady=5)

tk.Label(window,text="Destination Station",font=("Arial",10,"bold"),bg="light cyan").grid(row=4,column=0,sticky="w",padx=10)
train_label_dstation = tk.Entry(window,width=30,relief="solid")
train_label_dstation.grid(row=4,column=1,padx=5,pady=5)

#Change 5 : Done here in adding optionMenu
tk.Label(window,text="Seat Type",font=("Arial",10,"bold"),bg="light cyan").grid(row=5,column=0,sticky="w",padx=10)
seat_type_var = tk.StringVar(value="Select Seat Type")
seat_type_window = tk.OptionMenu(window,seat_type_var,"AC","NON-AC","Sleeper","General")
seat_type_window.config(width=26,relief="solid")
seat_type_window.grid(row=5,column=1,padx=5,pady=5)

#Change 7 : Command added 
def styled_button(text,color,command):
    return tk.Button(window,text=text,bg=color,fg="white",font=("Arial",10,"bold"),width=12,relief="flat",activebackground="gray",command=command)
#Change 8 and 9(extra command option and 7 1 in grid of Clear)
styled_button("Add Train","blue",addTrain).grid(row=6,column=1,padx=10,pady=5)
styled_button("Clear","orange",clearWindow).grid(row=7,column=1,padx=10,pady=5)

tk.Button(window,text = "Exit",bg="red",fg="white",font=("Arial",10,"bold"),command = window.destroy,width=12,relief="flat",activebackground="dark red").grid(row=8,column=1,columnspan=3,pady = 10)

window.mainloop()