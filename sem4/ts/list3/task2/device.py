import random
from enum import Enum

from wire import Wire


class Device:
    class State(Enum):
        RECEIVING = 0
        TRANSMITTING = 1
        WAITING_FOR_WIRE = 2
        JAMMING = 3
        BACKOFF = 4

    _MAX_BACKOFF_TRANSMISSION_ATTEMPS = 16

    def __init__(self, symbol: str, wire: Wire, position_in_wire: int) -> None:
        self._symbol = symbol
        self._wire = wire
        wire.add_device_info(symbol, position_in_wire)
        self._position_in_wire = position_in_wire

        self._min_packet_time = 2 * wire.length
        self._tick_counter = 0
        self._retransmissions_counter = 0
        self._backoff_waiting_ticks = 0
        self._state = self.State.RECEIVING
        self._is_ready_to_transmit = True

        self._successfull_transmissions = 0
        self._failed_transmissions = 0

    @property
    def successfull_transmissions(self) -> int:
        return self._successfull_transmissions

    @property
    def failed_transmissions(self) -> int:
        return self._failed_transmissions

    def tick(self) -> None:
        if self._state == self.State.TRANSMITTING:
            self._transmit()
        elif self._state == self.State.WAITING_FOR_WIRE:
            self.send_packet()
        elif self._state == self.State.JAMMING:
            self._jam()
        elif self._state == self.State.BACKOFF:
            self._backoff()

    def send_packet(self) -> None:
        if self._is_ready_to_transmit:
            if self._wire.is_collision(self._position_in_wire, self._symbol):
                self._state = self.State.WAITING_FOR_WIRE
            else:
                self._state = self.State.TRANSMITTING
                self._tick_counter = 0
                self._wire.add_signal(self._position_in_wire, self._symbol, self._min_packet_time)
                self._is_ready_to_transmit = False

    def _transmit(self) -> None:
        if self._wire.is_collision(self._position_in_wire, self._symbol):
            if self._wire.is_jammed(self._position_in_wire):
                self._state = self.State.BACKOFF
                self._retransmissions_counter = 0
            else:
                self._state = self.State.JAMMING
                self._wire.add_jam_signal(self._position_in_wire, self._min_packet_time)
                self._tick_counter = 0
            self._failed_transmissions += 1
        else:
            self._tick_counter += 1
            if self._tick_counter == self._min_packet_time:
                self._state = self.State.RECEIVING
                self._is_ready_to_transmit = True
                self._successfull_transmissions += 1

    def _jam(self) -> None:
        self._tick_counter += 1
        if self._tick_counter == self._min_packet_time:
            self._state = self.State.BACKOFF
            self._retransmissions_counter = 0
            self._calculate_exponential_backoff()

    def _backoff(self) -> None:
        self._backoff_waiting_ticks -= 1
        if self._backoff_waiting_ticks <= 0:
            if self._wire.is_free(self._position_in_wire, self._symbol):
                self._state = self.State.TRANSMITTING
                self._tick_counter = 0
                self._wire.add_signal(self._position_in_wire, self._symbol, self._min_packet_time)
            else:
                self._calculate_exponential_backoff()
                self._failed_transmissions += 1

    def _calculate_exponential_backoff(self) -> None:
        self._retransmissions_counter += 1
        if self._retransmissions_counter == self._MAX_BACKOFF_TRANSMISSION_ATTEMPS:
            raise Exception("Max transmission attempts reached.")
        k = min(self._retransmissions_counter, 10)
        self._backoff_waiting_ticks = random.randint(0, 2**k) * self._min_packet_time
