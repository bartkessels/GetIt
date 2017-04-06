from gi.repository import Gtk

from .header_key_value_pair import HeaderKeyValuePair

class Cookies:
    UI_FILE = "/usr/share/getit/ui/cookies.ui"

    key_value_pairs = []

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        self.sw_cookies = builder.get_object("sw_cookies")
        self.vp_cookies = builder.get_object("vp_cookies")
        self.grd_cookies = builder.get_object("grd_cookies")
        self.btn_add_cookie = builder.get_object("btn_add_cookie")

        # Connect signals
        self.btn_add_cookie.connect("clicked", self.btn_add_cookie_clicked)

    def get_cookies(self):
        cookies = {}

        for key_value_pair in self.key_value_pairs:
            if key_value_pair.is_active():
                cookies[key_value_pair.get_key()] = key_value_pair.get_value()

        return cookies

    def btn_add_cookie_clicked(self, widget):
        # Get row (5 is the number of rows already present)
        row = 5 + len(self.key_value_pairs)

        # Create key value pair
        key_value_pair = HeaderKeyValuePair()
        self.key_value_pairs.append(key_value_pair)

        # Add key value pair to self
        self.grd_cookies.attach(key_value_pair.grd_key_value_pair, 0, row, 10, 1)

        # Set remove button handler
        key_value_pair.btn_remove.connect("clicked", self.btn_remove_clicked, key_value_pair)

        # Show elements
        key_value_pair.show()

    def btn_remove_clicked(self, widget, key_value_pair):
        self.key_value_pairs.remove(key_value_pair)
        key_value_pair.hide()
