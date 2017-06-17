from gi.repository import Gtk
from urllib import parse
from mimetypes import MimeTypes

class FormData:
    UI_FILE = "/usr/share/getit/ui/elements/form_data.ui"

    def __init__(self):
        """
            Load widgets from UI file
        """

        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        '''
            --------------------------------------------------------------------
            GET WIDGETS FROM UI FILE
            --------------------------------------------------------------------
        '''
        self.root_view = builder.get_object("grd_form_data")
        self.cbtn_enabled = builder.get_object("cbtn_enabled")
        self.et_key = builder.get_object("et_key")
        self.et_value = builder.get_object("et_value")
        self.fcbtn_file = builder.get_object("fcbtn_file")
        self.cb_type = builder.get_object("cb_type")
        self.btn_remove = builder.get_object("btn_remove")

        '''
            --------------------------------------------------------------------
            CONNECT SIGNALS
            --------------------------------------------------------------------
        '''
        self.cb_type.connect("changed", self.cb_type_changed)

    def cb_type_changed(self, widget):
        """
            Change visibility of widgets based on selected type
        """

        if self.get_type() == "text":
            self.et_value.show()
            self.fcbtn_file.hide()
        else:
            self.et_value.hide()
            self.fcbtn_file.show()

    def is_active(self):
        """
            Get state of enabled check button
        """

        if self.get_type() == "text":
            return self.cbtn_enabled.get_active() and self.get_key() != "" and self.get_value() != ""

        return self.cbtn_enabled.get_active() and self.get_key() != "" and self.fcbtn_file.get_uri() != ""

    def get_type(self):
        """
            Get selected type
        """

        tree_iter = self.cb_type.get_active_iter()

        if tree_iter == None:
            return None

        model = self.cb_type.get_model()

        return model[tree_iter][1]

    def get_key(self):
        """
            Get text from et_key
        """

        return parse.quote_plus(self.et_key.get_text())

    def get_value(self):
        """
            Get text from et_value
        """

        return parse.quote_plus(self.et_value.get_text())

    def get_file(self):
        """
            Get file from self if file is selected as type
        """

        mime = MimeTypes()

        return (
            self.get_key(), (
                self.fcbtn_file.get_filename(),                 # Filename
                open(self.fcbtn_file.get_filename(), 'rb'),     # Path to file
                mime.guess_type(self.fcbtn_file.get_filename()) # Mimetype
            )
        )

    def show(self):
        """
            Show all widgets
        """

        self.root_view.show()
        self.cbtn_enabled.show()
        self.et_key.show()
        self.et_value.show()
        self.btn_remove.show()

        self.cb_type_changed(self.cb_type)

    def btn_remove_clicked(self, caller, widget, parent, request):
        """
            Remove self from request cookies list
            Remove widget from parent
            Destroy widget
        """

        parent.remove(self.root_view)
        request.remove_body_item(self)
        self.root_view.destroy()
