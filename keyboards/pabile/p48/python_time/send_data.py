import ctypes
import os

# Get the current directory
current_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the full path to the DLL
dll_path = os.path.join(current_dir, 'hidapi.dll')

ctypes.CDLL(dll_path)

import sys
import hid
import time

# Replace with your keyboard's Vendor ID and Product ID
vendor_id = 0x8065
product_id = 0x8048

usage_page    = 0xFF60
usage         = 0x61
report_length = 32

def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if len(raw_hid_interfaces) == 0:
        return None

    interface = hid.Device(path=raw_hid_interfaces[0]['path'])

    print(f"Manufacturer: {interface.manufacturer}")
    print(f"Product: {interface.product}")

    return interface

interface = get_raw_hid_interface()
if interface is None:
    print("No device found")
    sys.exit(1)

try:
    while True:
        # Get the current time as a string formatted as HHMM
        current_time = time.strftime("%H%M")

        # Prepare the data to send (must be 32 bytes)
        data = bytearray(32)
        data[0] = 0  # Set the command ID
        data[1:1+len(current_time)] = current_time.encode('utf-8')

        # Convert bytearray to list of integers
        data_list = bytes(data)

        # Send the data
        interface.write(data_list)

        print(f"Sent time: {current_time}")

        # Wait for 1 second
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    # Close the device
    interface.close()
