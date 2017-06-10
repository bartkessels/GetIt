from gi.repository import Gtk
from gi.repository import GtkSource
from gi.repository import GObject
from requests.auth import HTTPBasicAuth
from requests.auth import HTTPDigestAuth
from threading import Thread
from multiprocessing import Queue
import sys

from .cookie import Cookie
from .dialog import Dialog
from .form_data import FormData
from .header import Header
from .request import Request

class MainWindow(Gtk.Window):
    UI_FILE = "/usr/share/getit/ui/mainwindow.ui"

    def __init__(self):
        """
            Add all widgets from UI file to self, connect the signals and
            set properties for window
        """

        Gtk.Window.__init__(self, title = "GetIt")

        GObject.type_register(GtkSource.View)
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Create queue for threads
        self.queue = Queue()

        '''
            --------------------------------------------------------------------
            GET WIDGETS FROM UI FILE
            --------------------------------------------------------------------
        '''
        # Main
        self.lb_recent_requests = builder.get_object("lb_recent_requests")
        self.stack_main_content = builder.get_object("stack_main_content")

        # Body
        self.stack_body_data = builder.get_object("stack_body_data")
        self.cb_body_method = builder.get_object("cb_body_method")
        self.et_body_url = builder.get_object("et_body_url")
        self.grd_body_data_form_data = builder.get_object("grd_body_data_form_data")
        self.btn_body_data_form_data_add = builder.get_object("btn_body_data_form_data_add")
        self.cb_body_data_raw_syntax = builder.get_object("cb_body_data_raw_syntax")
        self.sv_body_data_raw_input = builder.get_object("sv_body_data_raw_input")

        # Authentication
        self.cb_authentication_method = builder.get_object("cb_authentication_method")
        self.grd_authentication_basic = builder.get_object("grd_authentication_basic")
        self.grd_authentication_digest = builder.get_object("grd_authentication_digest")
        self.et_authentication_basic_username = builder.get_object("et_authentication_basic_username")
        self.et_authentication_basic_password = builder.get_object("et_authentication_basic_password")
        self.et_authentication_digest_username = builder.get_object("et_authentication_digest_username")
        self.et_authentication_digest_password = builder.get_object("et_authentication_digest_password")

        # Cookies
        self.grd_content_cookies = builder.get_object("grd_content_cookies")
        self.btn_cookies_add = builder.get_object("btn_cookies_add")

        # Headers
        self.grd_content_headers = builder.get_object("grd_content_headers")
        self.btn_headers_add = builder.get_object("btn_headers_add")

        # Response
        self.sw_content_response = builder.get_object("sw_content_response")
        self.grd_response_headers = builder.get_object("grd_response_headers")
        self.sv_response_output = builder.get_object("sv_response_output")
        self.lbl_response_default_message = builder.get_object("lbl_response_default_message")
        self.grd_response_sending = builder.get_object("grd_response_sending")

        # Add root widget to window
        self.stack_main_content.unparent()
        self.add(self.stack_main_content)

        '''
            --------------------------------------------------------------------
            CONNECT SIGNALS
            --------------------------------------------------------------------
        '''
        # Body
        self.cb_body_method.connect("changed", self.cb_body_method_changed)
        self.btn_body_data_form_data_add.connect("clicked", self.btn_body_data_form_data_add_clicked)
        self.cb_body_data_raw_syntax.connect("changed", self.cb_body_data_raw_syntax_changed)

        # Authentication
        self.cb_authentication_method.connect("changed", self.cb_authentication_method_changed)

        # Cookies
        self.btn_cookies_add.connect("clicked", self.btn_cookies_add_clicked)

        # Headers
        self.btn_headers_add.connect("clicked", self.btn_headers_add_clicked)


        '''
            --------------------------------------------------------------------
            CREATE HEADERBAR
            --------------------------------------------------------------------
        '''
        # Headerbar widgets
        self.btn_send_request = Gtk.Button(label = "Send")
        self.btn_send_request.get_style_context().add_class("suggested-action")
        self.btn_send_request.set_tooltip_text("Send Request (Ctrl + Return)")
        self.btn_send_request.connect("clicked", self.btn_send_request_clicked)

        self.btn_cancel_request = Gtk.Button(label = "Cancel")
        self.btn_cancel_request.get_style_context().add_class("destructive-action")
        self.btn_cancel_request.set_tooltip_text("Cancel Request (Esc)")
        self.btn_cancel_request.connect("clicked", self.btn_cancel_request_clicked)

        self.ss_main_content = Gtk.StackSwitcher()
        self.ss_main_content.set_stack(self.stack_main_content)

        self.sp_sending = Gtk.Spinner()

        # Headerbar
        self.header_bar = Gtk.HeaderBar()
        self.header_bar.set_show_close_button(True)
        self.header_bar.set_title("GetIt")
        self.header_bar.pack_start(self.ss_main_content)
        self.header_bar.pack_end(self.btn_cancel_request)
        self.header_bar.pack_end(self.btn_send_request)
        self.header_bar.pack_end(self.sp_sending)

        self.set_titlebar(self.header_bar)

        '''
            --------------------------------------------------------------------
            WINDOW PROPERTIES
            --------------------------------------------------------------------
        '''
        self.set_border_width(5)
        self.set_default_size(1000, 600)
        self.show_all()


        '''
            --------------------------------------------------------------------
            INITIALIZING
            --------------------------------------------------------------------
        '''
        # Create new request object
        self.request = Request()

        # Hide widgets
        self.cb_authentication_method_changed(self.cb_authentication_method)
        self.response_screen_default()
        self.stop_loading()

    def cb_body_method_changed(self, widget):
        """
            Combobox method changed

            Change http method for request
        """

        tree_iter = self.cb_body_method.get_active_iter()
        if tree_iter != None:
            model = self.cb_body_method.get_model()
            method = model[tree_iter][0]
            self.request.method = method

    def btn_body_data_form_data_add_clicked(self, widget):
        """
            Add new form_data key value pair to request
        """

        form_data = FormData()
        form_data.btn_remove.connect("clicked", form_data.btn_delete_clicked, form_data, self.grd_body_data_form_data, self.request)
        self.request.add_body_item(form_data)

        self.grd_body_data_form_data.add(form_data.root_view)
        form_data.show()

    def cb_body_data_raw_syntax_changed(self, widget):
        """
            Change syntax highlighting raw body sourceview
        """

        tree_iter = self.cb_body_data_raw_syntax.get_active_iter()
        if tree_iter != None:
            model = self.cb_body_data_raw_syntax.get_model()
            selected_highlighting = model[tree_iter][1]

            language_manager = GtkSource.LanguageManager()
            language = language_manager.get_language(selected_highlighting)

            self.sv_body_data_raw_input.get_buffer().set_language(language)

    def cb_authentication_method_changed(self, widget):
        """
            Hide all authentication methods except the
            one that is selected
        """

        self.grd_authentication_basic.hide()
        self.grd_authentication_digest.hide()

        if self.get_authentication_method() == "auth_basic":
            self.grd_authentication_basic.show_all()
        elif self.get_authentication_method() == "auth_digest":
            self.grd_authentication_digest.show_all()

    def get_authentication_method(self):
        """
            Get selected authentication method
        """

        tree_iter = self.cb_authentication_method.get_active_iter()

        if tree_iter != None:
            model = self.cb_authentication_method.get_model()
            return model[tree_iter][1]

    def get_authentication(self):
        """
            Get authentication object basic off selected authentication method
        """

        authentication_method = self.get_authentication_method()

        if authentication_method == "auth_basic":
            return HTTPBasicAuth(self.et_authentication_basic_username.get_text(),
                                 self.et_authentication_basic_password.get_text())
        elif authentication_method == "auth_digest":
            return HTTPDigestAuth(self.et_authentication_digest_username.get_text(),
                                  self.et_authentication_digest_password.get_text())

        return None

    def btn_cookies_add_clicked(self, widget):
        """
            Add cookie key value pair to request
        """
        cookie = Cookie()
        cookie.btn_remove.connect("clicked", cookie.btn_delete_clicked, cookie, self.grd_content_cookies, self.request)
        self.request.add_cookie(cookie)

        self.grd_content_cookies.add(cookie.root_view)
        cookie.show()

    def btn_headers_add_clicked(self, widget):
        """
            Add header key value pair to request
        """

        header = Header()
        header.btn_remove.connect("clicked", header.btn_delete_clicked, header, self.grd_content_headers, self.request)
        self.request.add_header(header)

        self.grd_content_headers.add(header.root_view)
        header.show()

    def btn_send_request_clicked(self, widget):
        """
            Send request
        """

        # Set properties for request
        self.request.url = self.et_body_url.get_text()
        self.request.body_type = self.stack_body_data.get_visible_child_name()
        self.request.authentication = self.get_authentication()

        # Get data from raw sourceview
        text_buffer = self.sv_body_data_raw_input.get_buffer()
        self.request.body_raw = text_buffer.get_text(text_buffer.get_start_iter(), text_buffer.get_end_iter(), True)

        # Check if url is given
        if self.request.url == None or self.request.url == "":
            Dialog(self, "Warning", "Please enter a valid URL")
            return

        # Start loading animation
        self.stack_main_content.set_visible_child(self.sw_content_response)
        self.start_loading()
        self.response_screen_sending()

        self.header_bar.set_subtitle(self.request.method + ": " + self.request.url)

        # Send request
        self.thread = Thread(target = self.request.send_request, args=(self.queue, self.request_done,))
        self.thread.setDaemon(True)
        self.thread.start()

    def btn_cancel_request_clicked(self, widget):
        """
            Cancel sending request

            Stop loading and remove subtitle and set response stack to display
            default message
        """
        self.request.stop_request(self.queue, self.request_done)
        self.stop_loading()

        self.header_bar.set_subtitle("")
        self.response_screen_default()

    def request_done(self):
        """
            Method is being called when the request has been sent
        """

        if not hasattr(self.request, 'response_code'):
            return

        '''
            --------------------------------------------------------------------
            FILL RESPONSE STACK
            --------------------------------------------------------------------
        '''
        # Remove widgets
        for widget in self.grd_response_headers.get_children():
            self.grd_response_headers.remove(widget)
            widget.destroy()

        # Set status code
        lbl_status_code = Gtk.Label()
        lbl_status_code.set_xalign(0)
        lbl_status_code.set_markup_with_mnemonic("<b>Status</b> &#8594; " + str(self.request.response_code) + "(" + self.request.response_reason + ")")
        lbl_status_code.set_margin_bottom(2)

        # Add statuscode to self
        self.grd_response_headers.add(lbl_status_code)
        lbl_status_code.show()

        # Loop through headers
        for key, value in self.request.response_headers.items():
            lbl_header = Gtk.Label()
            lbl_header.set_xalign(0)
            lbl_header.set_markup_with_mnemonic("<b>" + key + "</b> &#8594; " + value)
            lbl_header.set_margin_top(2)
            lbl_header.set_margin_bottom(2)

            self.grd_response_headers.add(lbl_header)
            lbl_header.set_justify(Gtk.Justification.LEFT)
            lbl_header.show()

        # Response body
        if self.request.response_body != None:
            mime_type = "plain"
            if "Content-Type" in self.request.response_headers:
                mime_type = self.request.response_headers['Content-Type'].split(';')[0].split('/')[1]

            language_manager = GtkSource.LanguageManager()
            language = language_manager.get_language(mime_type)

            source_buffer = GtkSource.Buffer.new()
            if language != None:
                source_buffer = GtkSource.Buffer.new_with_language(language)

            source_buffer.set_text(self.request.response_body)
            self.sv_response_output.set_buffer(source_buffer)


        # Stop loading animation
        self.stop_loading()
        self.response_screen_output()

    def start_loading(self):
        """
            Setup headerbar to let user know it's doing something
            Display loading spinner, hide send button and show cancel button
        """

        self.btn_send_request.set_visible(False)
        self.btn_cancel_request.set_visible(True)
        self.sp_sending.start()

    def stop_loading(self):
        """
            Setup headerbar to let user know it's not doing anything
            Hide loading spinner, display send button and hide cancel button
        """

        self.btn_send_request.set_visible(True)
        self.btn_cancel_request.set_visible(False)
        self.sp_sending.stop()

    def response_screen_default(self):
        """
            Change widgets response screen to display default message
        """

        self.sv_response_output.set_visible(False)
        self.grd_response_headers.set_visible(False)
        self.lbl_response_default_message.set_visible(True)
        self.grd_response_sending.set_visible(False)

    def response_screen_output(self):
        """
            Change widgets response screen to hide default message
        """

        self.sv_response_output.set_visible(True)
        self.grd_response_headers.set_visible(True)
        self.lbl_response_default_message.set_visible(False)
        self.grd_response_sending.set_visible(False)

    def response_screen_sending(self):
        """
            Change widgets response screen to display sending message
        """

        self.sv_response_output.set_visible(False)
        self.grd_response_headers.set_visible(False)
        self.lbl_response_default_message.set_visible(False)
        self.grd_response_sending.set_visible(True)
        
