from gi.repository import Gtk
from urllib import parse
from mimetypes import MimeTypes

class BodyKeyValuePair:
    UI_FILE = "/usr/share/getit/ui/body_key_value_pair.ui"

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.grd_key_value_pair = builder.get_object("grd_key_value_pair")
        self.cbtn_enabled = builder.get_object("cbtn_enabled")
        self.et_key = builder.get_object("et_key")
        self.et_value = builder.get_object("et_value")
        self.fcbtn_file = builder.get_object("fcbtn_file")
        self.cb_type = builder.get_object("cb_type")
        self.btn_remove = builder.get_object("btn_remove")

        # Connect signals
        self.cb_type.connect("changed", self.cb_type_changed)

    def cb_type_changed(self, widget):
        if self.get_type() == "text":
            self.et_value.show()
            self.fcbtn_file.hide()
        else:
            self.et_value.hide()
            self.fcbtn_file.show()

    def is_active(self):
        if self.get_type() == "text":
            return self.cbtn_enabled.get_active() and self.et_key.get_text() != "" and self.et_value.get_text() != ""

        return self.cbtn_enabled.get_active() and self.et_key.get_text() != "" and self.fcbtn_file.get_uri() != ""

    def get_type(self):
        tree_iter = self.cb_type.get_active_iter()
        if tree_iter == None:
            return None

        model = self.cb_type.get_model()
        return model[tree_iter][1]

    def get_key(self):
        return parse.quote_plus(self.et_key.get_text())

    def get_value(self):
        return parse.quote_plus(self.et_value.get_text())

    def get_file(self):
        mime = MimeTypes()

        return (
            self.get_key(), (
                self.fcbtn_file.get_filename(),                 # Filename
                open(self.fcbtn_file.get_filename(), 'rb'),     # Path to file
                mime.guess_type(self.fcbtn_file.get_filename()) # Mimetype
            )
        )

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
        self.fcbtn_file.hide()
        self.btn_remove.hide()
