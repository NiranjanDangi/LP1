import tkinter as tk

window = tk.Tk()
window.title("Railway Management System")
window.geometry("420x400")
window.config(bg="light cyan")

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

tk.Label(window,text="Seat Type",font=("Arial",10,"bold"),bg="light cyan").grid(row=5,column=0,sticky="w",padx=10)
train_label_seat = tk.Entry(window,width=30,relief="solid")
train_label_seat.grid(row=5,column=1,padx=5,pady=5)

def styled_button(text,color):
    return tk.Button(window,text=text,bg=color,fg="white",font=("Arial",10,"bold"),width=12,relief="flat",activebackground="gray")

styled_button("Add Train","blue").grid(row=6,column=1,padx=10,pady=5)
styled_button("Clear","orange").grid(row=7,column=2,padx=10,pady=5)

tk.Button(window,text = "Exit",bg="red",fg="white",font=("Arial",10,"bold"),command = window.destroy,width=12,relief="flat",activebackground="dark red").grid(row=8,column=0,columnspan=3,pady = 10)

window.mainloop()