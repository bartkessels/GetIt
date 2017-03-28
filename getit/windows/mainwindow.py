from gi.repository import Gtk
import requests
import sys

from .authentication import Authentication
from .dialog import Dialog
from .body import Body
from .headers import Headers
from .response import Response

class MainWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="GetIt")

        # Create elements
        self.body = Body()
        self.headers = Headers()
        self.authentication = Authentication()
        self.response = Response()

        # Create send button
        btn_send = Gtk.Button(label="Send")
        btn_send.get_style_context().add_class("suggested-action")
        btn_send.connect("clicked", self.send_button_clicked)

        # Create the headerbar
        self.header_bar = Gtk.HeaderBar()
        self.header_bar.set_show_close_button(True)
        self.header_bar.set_title("GetIt")
        self.header_bar.pack_end(btn_send)

        self.set_titlebar(self.header_bar)

        # Create stack
        stack = Gtk.Stack()
        stack.set_transition_type(Gtk.StackTransitionType.SLIDE_LEFT_RIGHT)
        self.add(stack)

        # Create stackswitcher
        stack_switcher = Gtk.StackSwitcher()
        stack_switcher.set_stack(stack)

        # Add elements to stack
        stack.add_titled(self.body.sw_body, "body", "Body")
        stack.add_titled(self.headers.sw_headers, "headers", "Headers")
        stack.add_titled(self.authentication.sw_authentication, "authentication", "Authentication")
        stack.add_titled(self.response.sw_response, "response", "Response")

        # Add stackswitcher to headerbar
        self.header_bar.pack_start(stack_switcher)

    def send_button_clicked(self, widget):
        method = self.body.get_method()
        url = self.body.get_url()
        body = self.body.get_body()
        headers = self.headers.get_headers()

        # Check if method is selected
        if method == "" or method == None:
            Dialog(self, "Warning", "Please select a method")
            return
        # Check if url is not empty
        elif url == "" or url == None:
            Dialog(self, "Warning", "Please enter a URL")
            return

        # Set subtitle for headerbar (method: url)
        self.header_bar.set_subtitle(method + ": " + url)

        try:
            # Setup authentication
            auth = None
            '''if self.headers.get_authentication_enabled():
                auth_username = self.headers.et_auth_username.get_text()
                auth_password = self.headers.et_auth_password.get_text()

                auth = (auth_username, auth_password)'''

            # Create request
            request = requests.request(method, url, data=body, headers=headers, auth=auth)

            response_code = request.status_code
            response_reason = request.reason
            response_headers = request.headers
            response_body = request.text

            self.response.display_values(response_code, response_reason, response_headers, response_body)
        except:
            print(sys.exc_info())
            Dialog(self, "Error", "Something went wrong sending the request...")
