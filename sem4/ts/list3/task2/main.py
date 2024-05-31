from device import Device

def main() -> None:
    wire = [0] * 100
    devices = [Device(wire, (i * 10) - 1) for i in range(10)]


if __name__ == '__main__':
    main()