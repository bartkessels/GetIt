import sys
import gi

gi.require_version('Gtk', '3.0')
gi.require_version('GtkSource', '3.0')
gi.require_version('Notify', '0.7')

from gi.repository import GObject
from gi.repository import Notify

from .getit import GetIt

GObject.threads_init()

def main():
    # Initialize notifications
    Notify.init("GetIt")

    # Create application
    application = GetIt()
    exit_status = application.run(sys.argv)
    sys.exit(exit_status)
