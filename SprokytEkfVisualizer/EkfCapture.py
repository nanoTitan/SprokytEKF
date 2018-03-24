from bluetooth import *


class EkfCapture:
    def __init__(self):
        find_devices()
        return

    def find_devices(self):
        nearby_devices = bluetooth.discover_devices(lookup_names=True)
        print("found %d devices" % len(nearby_devices))

        for addr, name in nearby_devices:
            print("  %s - %s" % (addr, name))

    def connect(self, device_name, device_addr):
        # Create the client socket
        client_socket = BluetoothSocket(RFCOMM)
        client_socket.connect((device_addr, 3))     # example: address - "00:12:D2:5A:BD:E4", port - 3
        client_socket.send("Hello World")

        print "Finished"

        client_socket.close()
        return