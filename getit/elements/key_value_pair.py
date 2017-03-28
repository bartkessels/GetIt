from gi.repository import Gtk
from urllib import parse

class KeyValuePair:
    def __init__(self):
        # Create elements
        self.cbtn_enabled = Gtk.CheckButton()
        self.et_key = Gtk.Entry()
        self.et_value = Gtk.Entry()
        self.btn_remove = Gtk.Button()

        # Give elements a value
        self.cbtn_enabled.set_active(True)
        self.et_key.set_placeholder_text("Key")
        self.et_value.set_placeholder_text("Value")
        self.btn_remove.set_image(Gtk.Image().new_from_icon_name("edit-delete", 0))

    def is_active(self):
        return self.cbtn_enabled.get_active() and self.et_key.get_text() != "" and self.et_value.get_text() != ""

    def get_key(self):
        return parse.quote_plus(self.et_key.get_text())

    def get_value(self):
        return parse.quote_plus(self.et_value.get_text())

    def show(self):
        # Show all elements
        self.cbtn_enabled.show()
        self.et_key.show()
        self.et_value.show()
        self.btn_remove.show()

    def hide(self):
        # Hide all elements
        self.cbtn_enabled.hide()
        self.et_key.hide()
        self.et_value.hide()
        self.btn_remove.hide()
