from typing import Callable, List


class Wire:
    class Signal:
        DEFAULT_SYMBOL = "_"
        OVERLAPPING_SYMBOL = "#"
        JAM_SYMBOL = "!"

        def __init__(self, symbol: str, position: int, tick_lifetime: int, wire: "Wire") -> None:
            self._symbol = symbol
            self._left_propagating_position = position
            self._right_propagating_position = position
            self._left_clearing_position = position
            self._right_clearing_position = position
            self._tick_lifetime = tick_lifetime
            self._tick_counter = 2 * tick_lifetime
            self._wire = wire

        def _propagate_signal(self, position: int) -> None:
            if self._symbol == self.JAM_SYMBOL:
                self._wire.segments[position] = self._symbol
            elif self._wire.segments[position] != self.DEFAULT_SYMBOL and self._wire.segments[position] != self._symbol:
                self._wire.segments[position] = self.OVERLAPPING_SYMBOL
            elif self._wire.segments[position] != self.JAM_SYMBOL:
                self._wire.segments[position] = self._symbol

        def _clear_signal(self, position: int) -> None:
            if self._wire.is_free(position, self._symbol):
                self._wire.segments[position] = self.DEFAULT_SYMBOL

        def _is_position_valid(self, position: int) -> bool:
            return 0 <= position <= self._wire.length - 1

        def _process_signal(self, position: int, signal_method: Callable[[int], None]) -> None:
            if self._is_position_valid(position):
                signal_method(position)

        def is_active(self) -> bool:
            return self._tick_counter > 0

        def tick(self) -> None:
            self._tick_counter -= 1

            if self._tick_counter > self._tick_lifetime:
                self._process_signal(self._left_propagating_position, self._propagate_signal)
                self._process_signal(self._right_propagating_position, self._propagate_signal)

                self._left_propagating_position -= 1
                self._right_propagating_position += 1
            else:
                self._process_signal(self._left_clearing_position, self._clear_signal)
                self._process_signal(self._right_clearing_position, self._clear_signal)

                self._left_clearing_position -= 1
                self._right_clearing_position += 1

    def __init__(self, length: int) -> None:
        self._wire_segments = [self.Signal.DEFAULT_SYMBOL] * length
        self._signals = []
        self._devices_info = []

    @property
    def segments(self) -> List[str]:
        return self._wire_segments

    @property
    def length(self) -> int:
        return len(self._wire_segments)

    def tick(self) -> None:
        for signal in self._signals:
            signal.tick()

        self._signals = [signal for signal in self._signals if signal.is_active()]

    def add_device_info(self, symbol: str, position_in_wire: int) -> None:
        self._devices_info.append((symbol, position_in_wire))

    def add_signal(self, device_position: int, signal_symbol: str, tick_lifetime: int) -> None:
        self._signals.append(self.Signal(signal_symbol, device_position, tick_lifetime, self))

    def add_jam_signal(self, device_position: int, tick_lifetime: int) -> None:
        self._signals.append(self.Signal(self.Signal.JAM_SYMBOL, device_position, tick_lifetime, self))

    def is_free(self, position: int, signal_symbol: str) -> bool:
        return (
            self._wire_segments[position] == self.Signal.DEFAULT_SYMBOL
            or self._wire_segments[position] == signal_symbol
        )

    def is_collision(self, position: int, signal_symbol: str) -> bool:
        return not self.is_free(position, signal_symbol)

    def is_jammed(self, position: int) -> bool:
        return self._wire_segments[position] == self.Signal.JAM_SYMBOL

    def __str__(self) -> str:
        wire = "".join(self._wire_segments)
        devices_first_row = [" "] * self.length
        devices_second_row = [" "] * self.length

        for symbol, position_in_wire in self._devices_info:
            devices_first_row[position_in_wire] = "|"
            devices_second_row[position_in_wire] = symbol

        devices_first_row = "".join(devices_first_row)
        devices_second_row = "".join(devices_second_row)

        return f"{wire}\n{devices_first_row}\n{devices_second_row}\n"
