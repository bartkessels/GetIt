from gi.repository import Gtk

class HeaderKeyValuePair:
    UI_FILE = "/usr/share/getit/ui/header_key_value_pair.ui"

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.grd_key_value_pair = builder.get_object("grd_key_value_pair")
        self.cbtn_enabled = builder.get_object("cbtn_enabled")
        self.et_key = builder.get_object("et_key")
        self.et_value = builder.get_object("et_value")
        self.btn_remove = builder.get_object("btn_remove")

    def is_active(self):
        return self.cbtn_enabled.get_active() and self.et_key.get_text() != "" and self.et_value.get_text() != ""

    def get_key(self):
        return self.et_key.get_text()

    def get_value(self):
        return self.et_value.get_text()

    def show(self):
        self.grd_key_value_pair.show()
        self.cbtn_enabled.show()
        self.et_key.show()
        self.et_value.show()
        self.btn_remove.show()

    def hide(self):
        self.grd_key_value_pair.hide()
        self.cbtn_enabled.hide()
        self.et_key.hide()
        self.et_value.hide()
        self.btn_remove.hide()
