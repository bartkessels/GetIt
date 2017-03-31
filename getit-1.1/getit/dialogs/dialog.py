from gi.repository import Gtk

class Dialog(Gtk.Dialog):
    def __init__(self, parent, title, message):
        Gtk.Dialog.__init__(self, title, parent, Gtk.DialogFlags.MODAL, (
            Gtk.STOCK_CLOSE, Gtk.ResponseType.CLOSE
        ))

        self.set_border_width(5)

        # Add message to self
        area = self.get_content_area()
        area.add(Gtk.Label(message))

        self.show_all()

        self.run()
        self.destroy()
