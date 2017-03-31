import sys
import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GtkSource', '3.0')
from gi.repository import Gtk

from .mainwindow import MainWindow

def main():
    window = MainWindow()
    window.connect("delete-event", Gtk.main_quit)
    window.set_default_size(800, 500)
    window.set_border_width(5)
    window.show_all()

    Gtk.main()
