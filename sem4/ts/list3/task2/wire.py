import time
from dataclasses import dataclass


class Wire:
    @dataclass
    class Signal:
        symbol: str
        left_position: int
        right_position: int
        jam: bool = False

    DEFAULT_SIGNAL_SYMBOL = "0"
    JAM_SIGNAL_SYMBOL = "#"
    SIGNAL_LATENCY_MILLISECONDS = 10

    def __init__(self, length: int, tick_time_ms: int) -> None:
        self._wire_segments = [0] * length
        self._signals = []
        self._tick_time_ms = tick_time_ms

    @property
    def length(self) -> int:
        return len(self._wire_segments)

    def tick(self) -> None:
        for signal in self._signals:
            self._wire_segments[signal.left_position] = signal.symbol
            self._wire_segments[signal.right_position] = signal.symbol
            signal.left_position -= 1
            signal.right_position += 1

    def add_signal(self, device_position: int, signal_symbol: str) -> None:
        self._signals.append(self.Signal(signal_symbol, device_position, device_position))

    def remove_signal(self, signal_symbol: str) -> None:
        for i, signal in enumerate(self._signals):
            if signal.symbol == signal_symbol:
                self._signals.pop(i)
                return

    def add_jam_signal(self, device_position: int) -> None:
        self._signals.append(self.Signal(self.JAM_SIGNAL_SYMBOL, device_position, device_position, True))

    def remove_jam_signal(self, device_position: int) -> None:
        self._signals.remove(self.Signal(self.JAM_SIGNAL_SYMBOL, device_position, device_position, True))

    def is_free(self, position: int, signal_symbol: str) -> bool:
        return self._wire_segments[position] != self.DEFAULT_SIGNAL and self._wire_segments[position] != signal_symbol
