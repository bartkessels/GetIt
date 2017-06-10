from gi.repository import Notify

class Notification:

    def send(title, message):
        notification = Notify.Notification.new(title, message, "network-transmit")
        notification.set_app_name("GetIt")

        notification.show()
