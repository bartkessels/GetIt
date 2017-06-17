from gi.repository import Gtk
from gi.repository import Gio
from gi.repository import Gdk

from .dialog import Dialog
from .jsonparser import JsonParser
from .mainwindow import MainWindow

class GetIt(Gtk.Application):

    def __init__(self):
        """
            Initialize GetIt
        """

        Gtk.Application.__init__(self)

    def do_activate(self):
        """
            Activate application
        """

        # Display main window
        self.main_window = MainWindow(self)

        # Bind keys
        self.main_window.connect("key-press-event", self.key_pressed_event)

    def do_startup(self):
        """
            Startup GetIt
        """

        Gtk.Application.do_startup(self)

        # create a menu
        menu = Gio.Menu()
        menu.append("Save Request", "app.save_request")
        menu.append("Open Request", "app.open_request")
        menu.append("Clear Request", "app.clear_request")

        self.set_app_menu(menu)

        # Save Request
        action_save_request = Gio.SimpleAction.new("save_request", None)
        action_save_request.connect("activate", self.save_request)
        self.add_action(action_save_request)

        # Open Request
        action_open_request = Gio.SimpleAction.new("open_request", None)
        action_open_request.connect("activate", self.open_request)
        self.add_action(action_open_request)

        # Clear request
        action_clear_request = Gio.SimpleAction.new("clear_request", None)
        action_clear_request.connect("activate", self.clear_request)
        self.add_action(action_clear_request)

    def key_pressed_event(self, widget, event):
        """
            Bind hotkeys to application
        """

        keyval = event.keyval
        keyval_name = Gdk.keyval_name(keyval)
        state = event.state

        ctrl = (state & Gdk.ModifierType.CONTROL_MASK)

        # CTRL + Return / Enter: send request
        if ctrl and (keyval_name == 'Return' or keyval_name == 'KP_Enter'):
            widget.btn_send_request_clicked(widget)

        # Escape: Cancel request
        elif keyval_name == 'Escape':
            widget.btn_cancel_request_clicked(widget)

        # CTRL + S: Save request
        elif ctrl and keyval_name == 's':
            self.save_request(None, None)

        # CTRL + O: Open request
        elif ctrl and keyval_name == 'o':
            self.open_request(None, None)

    def save_request(self, action, parameter):
        """
            Save request to file
        """

        file_chooser_dialog = Gtk.FileChooserDialog("Save the request", self.main_window, Gtk.FileChooserAction.SAVE,
                                                                        (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
                                                                        Gtk.STOCK_SAVE, Gtk.ResponseType.OK))
        self.file_dialog_add_filters(file_chooser_dialog)
        response = file_chooser_dialog.run()

        if response != Gtk.ResponseType.OK:
            file_chooser_dialog.destroy()
            return

        # Body
        body_method = self.main_window.cb_body_method.get_active()
        body_url = self.main_window.et_body_url.get_text()
        body_data_type = self.main_window.stack_body_data.get_visible_child_name()
        body_data_raw_language = self.main_window.cb_body_data_raw_syntax.get_active()
        text_buffer = self.main_window.sv_body_data_raw_input.get_buffer()
        body_data_raw = text_buffer.get_text(text_buffer.get_start_iter(), text_buffer.get_end_iter(), True)

        body_form_data = []

        for form_data in self.main_window.request.body:
            body_form_data.append({
                'enabled': form_data.cbtn_enabled.get_active(),
                'key': form_data.et_key.get_text(),
                'value': form_data.et_value.get_text(),
                'file': form_data.fcbtn_file.get_filename(),
                'type': form_data.cb_type.get_active()
            })

        # Authentication
        auth_method = self.main_window.cb_authentication_method.get_active()

        auth_basic_username = self.main_window.et_authentication_basic_username.get_text()
        auth_basic_password = self.main_window.et_authentication_basic_password.get_text()

        auth_digest_username = self.main_window.et_authentication_digest_username.get_text()
        auth_digest_password = self.main_window.et_authentication_digest_password.get_text()

        # Cookies
        cookies = []

        for cookie in self.main_window.request.cookies:
            cookies.append({
                'enabled': cookie.cbtn_enabled.get_active(),
                'key': cookie.et_key.get_text(),
                'value': cookie.et_value.get_text()
            })

        # Headers
        headers = []

        for header in self.main_window.request.headers:
            headers.append({
                'enabled': header.cbtn_enabled.get_active(),
                'key': header.et_key.get_text(),
                'value': header.et_value.get_text()
            })

        try:
            JsonParser.write_file(
                body_method = body_method,
                body_url = body_url,
                body_selected_data = body_data_type,
                body_data_form = body_form_data,
                body_data_raw_language = body_data_raw_language,
                body_data_raw = body_data_raw,
                auth_selected = auth_method,
                auth_basic_username = auth_basic_username,
                auth_basic_password = auth_basic_password,
                auth_digest_username = auth_digest_username,
                auth_digest_password = auth_digest_password,
                cookies = cookies,
                headers = headers,
                filename = file_chooser_dialog.get_filename()
             )
        except Exception as e:
            print(e)
            Dialog(self.main_window, "Error", "Something went wrong saving the request")
        finally:
            file_chooser_dialog.destroy()


    def open_request(self, action, parameters):
        """
            Open request from file
        """

        # Clear current request
        self.clear_request(action, parameters)

        file_chooser_dialog = Gtk.FileChooserDialog("Open a request", self.main_window, Gtk.FileChooserAction.OPEN,
                                                                        (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
                                                                        Gtk.STOCK_OPEN, Gtk.ResponseType.OK))
        self.file_dialog_add_filters(file_chooser_dialog)
        response = file_chooser_dialog.run()

        if response != Gtk.ResponseType.OK:
            file_chooser_dialog.destroy()
            return

        try:
            request = JsonParser.read_file(file_chooser_dialog.get_filename())
            request_body = request['body']
            request_auth = request['authentication']
            request_auth_basic = request_auth['basic']
            request_auth_digest = request_auth['digest']
            request_cookies = request['cookies']
            request_headers = request['headers']
        except Exception as e:
            print(e)
            Dialog(self.main_window, "Error", "Something went wrong opening the request")
        finally:
            file_chooser_dialog.destroy()

        # Body
        self.main_window.cb_body_method.set_active(request_body['method'])
        self.main_window.et_body_url.set_text(request_body['url'])
        self.main_window.stack_body_data.set_visible_child_name(request_body['selected_data'])
        self.main_window.cb_body_data_raw_syntax.set_active(request_body['raw_language'])
        self.main_window.sv_body_data_raw_input.get_buffer().set_text(request_body['raw'], len(request_body['raw']))

        for form_data in request_body['form']:
            self.main_window.btn_body_data_form_data_add_clicked(
                self.main_window.btn_body_data_form_data_add,
                enabled = form_data['enabled'],
                key = form_data['key'],
                value = form_data['value'],
                file = form_data['file'],
                type = form_data['type']
            )

        # Authentication
        self.main_window.cb_authentication_method.set_active(request_auth['selected'])

        self.main_window.et_authentication_basic_username.set_text(request_auth_basic['username'])
        self.main_window.et_authentication_basic_password.set_text(request_auth_basic['password'])

        self.main_window.et_authentication_digest_username.set_text(request_auth_digest['username'])
        self.main_window.et_authentication_digest_password.set_text(request_auth_digest['password'])

        # Cookies
        for cookie in request_cookies:
                self.main_window.btn_cookies_add_clicked(
                    self.main_window.btn_cookies_add,
                    enabled = cookie['enabled'],
                    key = cookie['key'],
                    value = cookie['value']
                )

        # Headers
        for header in request_headers:
                self.main_window.btn_headers_add_clicked(
                    self.main_window.btn_headers_add,
                    enabled = header['enabled'],
                    key = header['key'],
                    value = header['value']
                )

    def clear_request(self, action, parameters):
        """
            Clear everything that is entered
        """

        # Body
        self.main_window.et_body_url.set_text('')
        self.main_window.cb_body_method.set_active(0)
        self.main_window.stack_body_data.set_visible_child_name('body_data_form_data')

        while len(self.main_window.request.body) > 0:
            body_item = self.main_window.request.body[0]

            body_item.btn_remove_clicked(body_item.btn_remove, body_item.root_view, self.main_window.grd_body_data_form_data, self.main_window.request)

        self.main_window.sv_body_data_raw_input.get_buffer().set_text('', 0)
        self.main_window.cb_body_data_raw_syntax.set_active(0)

        # Authentication
        self.main_window.cb_authentication_method.set_active(0)

        self.main_window.et_authentication_basic_username.set_text('')
        self.main_window.et_authentication_basic_password.set_text('')

        self.main_window.et_authentication_digest_username.set_text('')
        self.main_window.et_authentication_digest_password.set_text('')

        # Cookies
        while len(self.main_window.request.cookies) > 0:
            cookie = self.main_window.request.cookies[0]
            cookie.btn_remove_clicked(cookie.btn_remove, cookie.root_view, self.main_window.grd_content_cookies, self.main_window.request)

        # Headers
        while len(self.main_window.request.headers) > 0:
            header = self.main_window.request.headers[0]
            header.btn_remove_clicked(header.btn_remove, header.root_view, self.main_window.grd_content_headers, self.main_window.request)

        # Response
        self.main_window.btn_cancel_request_clicked(self.main_window.btn_cancel_request)

        self.main_window.header_bar.set_subtitle('')
        self.main_window.stack_main_content.set_visible_child_name('content_body')

    def file_dialog_add_filters(self, dialog):
        """
            Add filters to file dialogs
        """

        filter = Gtk.FileFilter()
        filter.set_name("GetIt")
        filter.add_mime_type("application/octet-stream")
        dialog.add_filter(filter)
