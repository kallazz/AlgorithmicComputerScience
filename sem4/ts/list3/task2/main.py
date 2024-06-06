import random

from device import Device
from wire import Wire

WIRE_LENGTH = 30
TRANSMITTION_PROBABILITY = 0.005
TICKS = 2000

OUTPUT_FILENAME = "./output.txt"


def main() -> None:
    wire = Wire(WIRE_LENGTH)
    devices = [
        Device("A", wire, 5),
        Device("B", wire, 15),
        Device("C", wire, 25),
    ]

    output_file = open(OUTPUT_FILENAME, "w")

    for _ in range(TICKS):
        for device in devices:
            if random.random() < TRANSMITTION_PROBABILITY:
                device.send_packet()
            device.tick()
        wire.tick()
        output_file.write(f"{wire}\n")

    for device in devices:
        output_file.write(
            f"Device {device._symbol}: {device.successfull_transmissions} successfull transmissions, {device.failed_transmissions} failed transmissions.\n"
        )

    output_file.close()


if __name__ == "__main__":
    main()
