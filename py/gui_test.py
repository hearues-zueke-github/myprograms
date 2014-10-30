#! /usr/bin/python3
from gi.repository import Gtk

class MyWindow(Gtk.Window):

  def __init__(self):
    Gtk.Window.__init__(self, title="Hello World")

    button = Gtk.Button(label="Click Here!!")
    button.connect("clicked", self.on_button_clicked)
    button.resize(30,40)
    self.add(button)

    self.connect("delete-event", Gtk.main_quit)

  def on_button_clicked(self, widget):
    print("Hello World")

win = MyWindow()
win.resize(300,200)
win.show_all()
Gtk.main()