from gi.repository import Gtk

class Authentication:
    UI_FILE = "/home/bkessels/Git-projects/Linux/GetIt/data/mainwindow.ui"

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.sw_authentication = builder.get_object("sw_authentication")
        self.vp_authentication = builder.get_object("vp_authentication")
        self.grd_authentication = builder.get_object("grd_authentication")
        self.cb_authentication_method = builder.get_object("cb_authentication_method")
        self.grd_authentication_values = builder.get_object("grd_authentication_values")

        # Connect signals
        self.cb_authentication_method.connect("changed", self.cb_authentication_method_changed)

    def cb_authentication_method_changed(self, widget):
        tree_iter = self.cb_authentication_method.get_active_iter()
        if tree_iter == None:
            return

        model = self.cb_authentication_method.get_model()
        auth_mode = model[tree_iter][1]

        if auth_mode == "basic_auth":
            self.show_basic_auth()
        elif auth_mode == "digest_auth": # digest auth has the same values as basic auth
            self.show_basic_auth()
        elif auth_mode == "oauth1":
            self.show_oauth()
        elif auth_mode == "oauth2":
            self.show_oauth2()
        else:
            self.hide_all()

    def show_basic_auth(self):
        self.hide_all()

        et_username = Gtk.Entry()
        et_password = Gtk.Entry()

        et_username.set_placeholder_text("Username")
        et_password.set_placeholder_text("Password")

        self.grd_authentication_values.attach(et_username, 0, 0, 1, 1)
        self.grd_authentication_values.attach_next_to(et_password, et_username, Gtk.PositionType.RIGHT, 1, 1)

        et_username.show()
        et_password.show()

    def show_oauth(self):
        self.hide_all()

        et_app_key = Gtk.Entry()
        et_app_secret = Gtk.Entry()
        et_user_token = Gtk.Entry()
        et_user_token_secret = Gtk.Entry()

        et_app_key.set_placeholder_text("App Key")
        et_app_secret.set_placeholder_text("App Secret")
        et_user_token.set_placeholder_text("User Token")
        et_user_token_secret.set_placeholder_text("User Token Secret")

        self.grd_authentication_values.attach(et_app_key, 0, 0, 1, 1)
        self.grd_authentication_values.attach_next_to(et_app_secret, et_app_key, Gtk.PositionType.RIGHT, 1, 1)
        self.grd_authentication_values.attach_next_to(et_user_token, et_app_key, Gtk.PositionType.BOTTOM, 1, 1)
        self.grd_authentication_values.attach_next_to(et_user_token_secret, et_user_token, Gtk.PositionType.RIGHT, 1, 1)

        et_app_key.show()
        et_app_secret.show()
        et_user_token.show()
        et_user_token_secret.show()

    def show_oauth2(self):
        print("OAuth2")

    def hide_all(self):
        for widget in self.grd_authentication_values.get_children():
            self.grd_authentication_values.remove(widget)
