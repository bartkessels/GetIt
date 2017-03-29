from gi.repository import Gtk
from collections import namedtuple

from .key_value_pair import KeyValuePair

class Body:
    UI_FILE = "/usr/share/getit/mainwindow.ui"

    key_value_pairs = []

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.sw_body = builder.get_object("sw_body")
        self.vp_body = builder.get_object("vp_body")
        self.grd_body = builder.get_object("grd_body")
        self.cb_method = builder.get_object("cb_method")
        self.et_url = builder.get_object("et_url")
        self.btn_add_body = builder.get_object("btn_add_body")

        # Connect signals
        self.btn_add_body.connect("clicked", self.btn_add_body_clicked)

    def get_method(self):
        tree_iter = self.cb_method.get_active_iter()
        if tree_iter != None:
            model = self.cb_method.get_model()
            return model[tree_iter][0]

    def get_url(self):
        return self.et_url.get_text()

    def get_body(self):
        body = {}

        for key_value_pair in self.key_value_pairs:
            if key_value_pair.is_active():
                body[key_value_pair.get_key()] = key_value_pair.get_value()

        return body

    def btn_add_body_clicked(self, widget):
        # Get row (2 is the number of rows already present)
        row = 2 + len(self.key_value_pairs)

        # Create key value pair
        key_value_pair = KeyValuePair()
        self.key_value_pairs.append(key_value_pair)

        # Add key value pair to self
        self.grd_body.attach(key_value_pair.cbtn_enabled, 0, row, 1, 1)
        self.grd_body.attach_next_to(key_value_pair.et_key, key_value_pair.cbtn_enabled, Gtk.PositionType.RIGHT, 4, 1)
        self.grd_body.attach_next_to(key_value_pair.et_value, key_value_pair.et_key, Gtk.PositionType.RIGHT, 4, 1)
        self.grd_body.attach_next_to(key_value_pair.btn_remove, key_value_pair.et_value, Gtk.PositionType.RIGHT, 1, 1)

        # Set remove button handler
        key_value_pair.btn_remove.connect("clicked", self.btn_remove_clicked, key_value_pair)

        # Show elements
        key_value_pair.show()

    def btn_remove_clicked(self, widget, key_value_pair):
        self.key_value_pairs.remove(key_value_pair)
        key_value_pair.hide()
