from gi.repository import Gtk
from gi.repository import GtkSource

class Response:
    UI_FILE = "/usr/share/getit/ui/response.ui"

    def __init__(self):
        builder = Gtk.Builder()
        builder.add_from_file(self.UI_FILE)

        # Load elements from UI file
        self.sw_response = builder.get_object("sw_response")
        self.vp_response = builder.get_object("vp_response")
        self.grd_response = builder.get_object("grd_response")

    def display_values(self, status_code, reason, headers, body):
        # Clear self
        self.clear()

        # Get mime-type
        mime_type = headers['Content-Type'].split(';')[0].split('/')[1]

        # Status code
        lbl_status_code = Gtk.Label()
        lbl_status_code.set_xalign(0)
        lbl_status_code.set_markup_with_mnemonic("<b>Status</b> &#8594; " + str(status_code) + "(" + reason + ")")
        lbl_status_code.set_margin_bottom(2)

        # Add statuscode to self
        self.grd_response.add(lbl_status_code)
        lbl_status_code.show()

        # Loop through headers
        for key, value in headers.items():
            lbl_header = Gtk.Label()
            lbl_header.set_xalign(0)
            lbl_header.set_markup_with_mnemonic("<b>" + key + "</b> &#8594; " + value)
            lbl_header.set_margin_top(2)
            lbl_header.set_margin_bottom(2)

            self.grd_response.add(lbl_header)
            lbl_header.set_justify(Gtk.Justification.LEFT)
            lbl_header.show()

        # Add another separator
        separator = Gtk.Separator()
        separator.set_orientation(Gtk.Orientation.HORIZONTAL)

        self.grd_response.add(separator)
        separator.show()

        # Body
        language_manager = GtkSource.LanguageManager()

        source_buffer = GtkSource.Buffer.new_with_language(language_manager.get_language(mime_type))
        source_buffer.set_text(body)
        tv_body = GtkSource.View.new_with_buffer(source_buffer)
        tv_body.set_indent(True)
        tv_body.set_show_line_numbers(True)
        tv_body.set_wrap_mode(Gtk.WrapMode.WORD)

        # Add body to self
        self.grd_response.add(tv_body)
        tv_body.show()

    def clear(self):
        for widget in self.grd_response.get_children():
            self.grd_response.remove(widget)
