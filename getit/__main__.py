import sys
import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GtkSource', '3.0')
from gi.repository import Gtk
from gi.repository import Gdk
from gi.repository import GObject

from .mainwindow import MainWindow

GObject.threads_init()

def main():
    main_window = MainWindow()
    main_window.connect("delete-event", Gtk.main_quit)

    # Bind keys
    main_window.connect("key-press-event", key_press_events)

    Gtk.main()

def key_press_events(widget, event):
    """
        Bind hotkeys to application
    """

    keyval = event.keyval
    keyval_name = Gdk.keyval_name(keyval)
    state = event.state

    ctrl = (state & Gdk.ModifierType.CONTROL_MASK)

    # CTRL + Return / Enter: send request
    if ctrl and (keyval_name == 'Return' or keyval_name == 'KP_Enter'):
        widget.btn_send_request_clicked(widget)

    # Escape: Cancel request
    elif keyval_name == 'Escape':
        widget.btn_cancel_request_clicked(widget)
