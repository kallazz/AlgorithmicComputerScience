from typing import List

import libscrc

CRC_SIZE = 8
FLAG_BYTE = "01111110"
FRAME_SIZE = 32
ONES_RUN_LENGTH = 5


def split_bits_into_frames(bits: str, frame_size: int) -> List[str]:
    return [bits[i : i + frame_size] for i in range(0, len(bits), frame_size)]


def stuff_bits(bits: str, ones_run_length: int) -> str:
    return bits.replace(ones_run_length * "1", ones_run_length * "1" + "0")


def unstuff_bits(bits: str, ones_run_length: int) -> str:
    return bits.replace(ones_run_length * "1" + "0", ones_run_length * "1")


def calculate_crc(bits: str) -> str:
    return bin(libscrc.crc8(bytes(bits, "utf-8")))[2:].zfill(8)


def encode(bits: str) -> str:
    return "".join(
        FLAG_BYTE + stuff_bits(frame + calculate_crc(frame), ONES_RUN_LENGTH) + FLAG_BYTE
        for frame in split_bits_into_frames(bits, FRAME_SIZE)
    )


def decode(bits: str) -> str:
    output = ""
    frames = bits.split(FLAG_BYTE)
    frames = [frame for frame in frames if frame != ""]
    for frame in frames:
        frame = unstuff_bits(frame, ONES_RUN_LENGTH)
        crc = frame[-CRC_SIZE:]
        frame_without_crc = frame[:-CRC_SIZE]
        if crc != calculate_crc(frame_without_crc):
            raise RuntimeError("Invalid CRC!")
        output += frame_without_crc
    return output
