from typing import List
from dataclasses import dataclass


class Wire:
    DEFAULT_SIGNAL_SYMBOL = "_"
    OVERLAPPING_SIGNAL_SYMBOL = "#"
    JAM_SIGNAL_SYMBOL = "!"

    @dataclass
    class Signal:
        symbol: str
        ticks_left: int

        def tick(self) -> None:
            self.ticks_left -= 1

        def is_active(self) -> bool:
            return self.ticks_left > 0

    class SignalPropagator:
        def __init__(self, symbol: str, position: int, tick_lifetime: int, wire: "Wire") -> None:
            self._symbol = symbol
            self._left_position = position
            self._right_position = position
            self._tick_lifetime = tick_lifetime
            self._tick_counter = tick_lifetime
            self._wire = wire

        def _propagate_signal(self, position: int) -> None:
            if self._is_position_valid(position):
                self._wire.signal_groups[position].append(self._wire.Signal(self._symbol, self._tick_lifetime))

        def _is_position_valid(self, position: int) -> bool:
            return 0 <= position <= self._wire.length - 1

        def is_active(self) -> bool:
            return self._tick_counter > 0

        def tick(self) -> None:
            self._tick_counter -= 1

            if self._left_position == self._right_position:
                self._propagate_signal(self._left_position)
            else:
                self._propagate_signal(self._left_position)
                self._propagate_signal(self._right_position)
            self._left_position -= 1
            self._right_position += 1

    def __init__(self, length: int) -> None:
        self._length = length
        self._symbols = [self.DEFAULT_SIGNAL_SYMBOL] * length
        self._signal_groups = [[]] * length
        self._signal_propagators = []

    @property
    def signal_groups(self) -> List[List[str]]:
        return self._signal_groups

    @property
    def length(self) -> int:
        return len(self._symbols)

    def tick(self) -> None:
        self._signal_propagators = [
            signal_propagator
            for signal_propagator in self._signal_propagators
            if signal_propagator.tick() or signal_propagator.is_active()
        ]

        self._signal_groups = [
            [signal for signal in signals if signal.tick() or signal.is_active()] for signals in self._signal_groups
        ]

        self._update_segment_symbols()

    def _update_segment_symbols(self) -> None:
        for index, signals in enumerate(self._signal_groups):
            if len(signals) == 0:
                self._symbols[index] = self.DEFAULT_SIGNAL_SYMBOL
            elif len(signals) == 1:
                self._symbols[index] = signals[0].symbol
            elif self.JAM_SIGNAL_SYMBOL in [signal.symbol for signal in signals]:
                self._symbols[index] = self.JAM_SIGNAL_SYMBOL
            else:
                self._symbols[index] = self.OVERLAPPING_SIGNAL_SYMBOL

    def add_signal(self, device_position: int, signal_symbol: str, tick_lifetime: int) -> None:
        self._signal_propagators.append(self.SignalPropagator(signal_symbol, device_position, tick_lifetime, self))

    def add_jam_signal(self, device_position: int, tick_lifetime: int) -> None:
        self._signal_propagators.append(
            self.SignalPropagator(self.JAM_SIGNAL_SYMBOL, device_position, tick_lifetime, self)
        )

    def is_free(self, position: int, signal_symbol: str) -> bool:
        return self._symbols[position] == self.DEFAULT_SIGNAL_SYMBOL or self._symbols[position] == signal_symbol

    def is_collision(self, position: int, signal_symbol: str) -> bool:
        return not self.is_free(position, signal_symbol)

    def is_jammed(self, position: int) -> bool:
        return self._symbols[position] == self.JAM_SIGNAL_SYMBOL

    def __str__(self) -> str:
        return "".join(self._symbols)
