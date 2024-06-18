from dataclasses import dataclass
from enum import Enum


class Wire:
    DEFAULT_SIGNAL_SYMBOL = "_"
    OVERLAPPING_SIGNAL_SYMBOL = "#"
    JAM_SIGNAL_SYMBOL = "!"

    class SignalDirection(Enum):
        LEFT = 0
        RIGHT = 1
        BOTH = 2

    @dataclass
    class Signal:
        symbol: str
        ticks_left: int
        direction: "Wire.SignalDirection"
        ticks_to_propagate: int = 1

        def tick(self) -> None:
            self.ticks_left -= 1
            self.ticks_to_propagate -= 1

        @property
        def is_active(self) -> bool:
            return self.ticks_left >= 0

        @property
        def is_ready_to_propagate(self) -> bool:
            return self.ticks_to_propagate == 0

    def __init__(self, length: int) -> None:
        self._length = length
        self._symbols = [self.DEFAULT_SIGNAL_SYMBOL] * length
        self._signal_groups = [[] for _ in range(length)]

    @property
    def length(self) -> int:
        return len(self._symbols)

    def is_position_valid(self, position: int) -> bool:
        return 0 <= position <= self.length - 1

    def tick(self) -> None:
        self._spread_signals()

        self._signal_groups = [[signal for signal in signals if signal.tick() or signal.is_active] for signals in self._signal_groups]

        self._update_segment_symbols()

    def _spread_signals(self) -> None:
        new_signals = []

        for position, signal_group in enumerate(self._signal_groups):
            for signal in signal_group:
                if signal.is_ready_to_propagate:
                    if (signal.direction == self.SignalDirection.LEFT or signal.direction == self.SignalDirection.BOTH) and self.is_position_valid(position - 1):
                        new_signals.append((self.Signal(signal.symbol, signal.ticks_left + 1, self.SignalDirection.LEFT), position - 1))
                    if (signal.direction == self.SignalDirection.RIGHT or signal.direction == self.SignalDirection.BOTH) and self.is_position_valid(position + 1):
                        new_signals.append((self.Signal(signal.symbol, signal.ticks_left + 1, self.SignalDirection.RIGHT), position + 1))

        for new_signal, position in new_signals:
            self._signal_groups[position].append(new_signal)

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

    def send_signal(self, device_position: int, signal_symbol: str, tick_lifetime: int) -> None:
        self._signal_groups[device_position].append(self.Signal(signal_symbol, tick_lifetime, self.SignalDirection.BOTH))

    def send_jam_signal(self, device_position: int, tick_lifetime: int) -> None:
        self._signal_groups[device_position].append(self.Signal(self.JAM_SIGNAL_SYMBOL, tick_lifetime, self.SignalDirection.BOTH))

    def is_free(self, position: int, signal_symbol: str) -> bool:
        return self._symbols[position] == self.DEFAULT_SIGNAL_SYMBOL or self._symbols[position] == signal_symbol

    def is_collision(self, position: int, signal_symbol: str) -> bool:
        return not self.is_free(position, signal_symbol)

    def is_jammed(self, position: int) -> bool:
        return self._symbols[position] == self.JAM_SIGNAL_SYMBOL

    def __str__(self) -> str:
        return "".join(self._symbols)
