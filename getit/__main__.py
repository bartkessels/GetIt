import sys
import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GtkSource', '3.0')
from gi.repository import Gtk
from gi.repository import GObject

from .mainwindow import MainWindow

GObject.threads_init()

def main():
    main_window = MainWindow()
    main_window.connect("delete-event", Gtk.main_quit)

    Gtk.main()
