from gi.repository import Gtk
from urllib import parse
from mimetypes import MimeTypes

class Cookie:
    UI_FILE = "/usr/share/getit/ui/elements/cookie.ui"

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
        self.root_view = builder.get_object("grd_cookie")
        self.cbtn_enabled = builder.get_object("cbtn_enabled")
        self.et_key = builder.get_object("et_key")
        self.et_value = builder.get_object("et_value")
        self.btn_remove = builder.get_object("btn_remove")

    def is_active(self):
        """
            Get state of enabled check button
        """

        return self.cbtn_enabled.get_active() and self.get_key() != "" and self.get_value() != ""

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

    def show(self):
        """
            Show all widgets
        """

        self.root_view.show()
        self.cbtn_enabled.show()
        self.et_key.show()
        self.et_value.show()
        self.btn_remove.show()

    def btn_remove_clicked(self, caller, widget, parent, request):
        """
            Remove self from request cookies list
            Remove widget from parent
            Destroy widget
        """

        request.remove_cookie(self)
        parent.remove(self.root_view)
        self.root_view.destroy()
