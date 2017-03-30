from gi.repository import Gtk
from requests.auth import HTTPBasicAuth, HTTPDigestAuth

class Authentication:
    UI_FILE = "/usr/share/getit.ui"

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.sw_authentication = builder.get_object("sw_authentication")
        self.vp_authentication = builder.get_object("vp_authentication")
        self.grd_authentication = builder.get_object("grd_authentication")
        self.cb_authentication_method = builder.get_object("cb_authentication_method")
        self.grd_auth_basic = builder.get_object("grd_auth_basic")
        self.grd_auth_digest = builder.get_object("grd_auth_digest")
        self.et_auth_basic_username = builder.get_object("et_auth_basic_username")
        self.et_auth_basic_password = builder.get_object("et_auth_basic_password")
        self.et_auth_digest_username = builder.get_object("et_auth_digest_username")
        self.et_auth_digest_password = builder.get_object("et_auth_digest_password")

        self.cb_authentication_method.connect("changed", self.cb_authentication_method_changed)

    def get_auth_mode(self):
        tree_iter = self.cb_authentication_method.get_active_iter()
        if tree_iter == None:
            return None

        model = self.cb_authentication_method.get_model()
        return model[tree_iter][1]

    def cb_authentication_method_changed(self, widget):
        tree_iter = self.cb_authentication_method.get_active_iter()
        if tree_iter == None:
            return

        model = self.cb_authentication_method.get_model()
        auth_mode = model[tree_iter][1]

        # Hide all authentication elements
        self.hide_all()

        if auth_mode == "basic_auth":
            self.grd_auth_basic.set_visible(True)
        elif auth_mode == "digest_auth":
            self.grd_auth_digest.set_visible(True)

    def get_authentication(self):
        auth_mode = self.get_auth_mode()

        if auth_mode == "basic_auth":
            return HTTPBasicAuth(self.et_auth_basic_username.get_text(),
                                 self.et_auth_basic_password.get_text())
        elif auth_mode == "digest_auth":
            return HTTPDigestAuth(self.et_auth_digest_username.get_text(),
                                  self.et_auth_digest_password.get_text())

        # No auth mode
        return None

    def hide_all(self):
        self.grd_auth_basic.set_visible(False)
        self.grd_auth_digest.set_visible(False)
