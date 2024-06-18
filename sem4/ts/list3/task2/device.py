import random
from enum import Enum

from wire import Wire


class Device:
    class State(Enum):
        RECEIVING = 0
        TRANSMITTING = 1
        WAITING_FOR_WIRE = 2
        JAMMING = 3
        WAITING_BACK_OFF_TIME = 4

    _MAX_FAILED_ATTEMPTS = 16

    def __init__(self, symbol: str, wire: Wire, position_in_wire: int) -> None:
        if not wire.is_position_valid(position_in_wire):
            raise Exception(f"Position in wire has to be a number in range [0, {wire.length - 1}].")

        self._symbol = symbol
        self._wire = wire
        self._position_in_wire = position_in_wire

        self._min_packet_time = 2 * wire.length
        self._tick_counter = 0
        self._failed_attempts = 0
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

    def _change_state(self, state: State) -> None:
        self._state = state

    def tick(self) -> None:
        if self._state == self.State.TRANSMITTING:
            self._transmit()
        elif self._state == self.State.WAITING_FOR_WIRE:
            self.send_packet()
        elif self._state == self.State.JAMMING:
            self._jam()
        elif self._state == self.State.WAITING_BACK_OFF_TIME:
            self._wait_back_off_time()

    def send_packet(self) -> None:
        if self._is_ready_to_transmit:
            if self._wire.is_collision(self._position_in_wire, self._symbol):
                self._change_state(self.State.WAITING_FOR_WIRE)
            else:
                self._change_state(self.State.TRANSMITTING)
                self._tick_counter = 0
                self._wire.send_signal(self._position_in_wire, self._symbol, self._min_packet_time)
                self._is_ready_to_transmit = False

    def _transmit(self) -> None:
        if self._wire.is_collision(self._position_in_wire, self._symbol):
            if self._wire.is_jammed(self._position_in_wire):
                self._change_state(self.State.WAITING_BACK_OFF_TIME)
                self._calculate_wait_time()
            else:
                self._change_state(self.State.JAMMING)
                self._wire.send_jam_signal(self._position_in_wire, self._min_packet_time)
                self._tick_counter = 0
        else:
            self._tick_counter += 1
            if self._tick_counter == self._min_packet_time:
                self._change_state(self.State.RECEIVING)
                self._is_ready_to_transmit = True
                self._failed_attempts = 0
                self._successfull_transmissions += 1

    def _jam(self) -> None:
        self._tick_counter += 1
        if self._tick_counter == self._min_packet_time:
            self._change_state(self.State.WAITING_BACK_OFF_TIME)
            self._calculate_wait_time()

    def _wait_back_off_time(self) -> None:
        self._backoff_waiting_ticks -= 1
        if self._backoff_waiting_ticks <= 0:
            self._is_ready_to_transmit = True
            self._change_state(self.State.WAITING_FOR_WIRE)

    def _calculate_wait_time(self) -> None:
        self._failed_attempts += 1
        self._failed_transmissions += 1
        if self._failed_attempts == self._MAX_FAILED_ATTEMPTS:
            raise Exception("Too many failed attempts.")
        k = min(self._failed_attempts, 10)
        self._backoff_waiting_ticks = random.randint(1, 2**k) * self._min_packet_time
