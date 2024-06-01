from enum import Enum

from wire import Wire


class Device:
    class State(Enum):
        RECEIVING = 0
        TRANSMITTING = 1
        WAITING_FOR_WIRE = 2
        WAITING_FOR_COLLISION_RESOLUTION = 3

    def __init__(self, symbol: str, wire: Wire, position_in_wire: int, tick_time_ms: int) -> None:
        self._symbol = symbol
        self._wire = wire
        self._position_in_wire = position_in_wire
        self._tick_time_ms = tick_time_ms

        self._wire_max_distnace = 2 * wire.length  # max(position_in_wire + 1, wire.length - position_in_wire + 1)
        self._signal_propagation_counter = 0
        self._state = self.State.RECEIVING

    def tick(self) -> None:
        if self._state == self.State.RECEIVING:
            # do nothing
            pass
        elif self._state == self.State.TRANSMITTING:
            self._transmit()
        elif self._state == self.State.WAITING_FOR_WIRE:
            self.send_packet()
        elif self._state == self.State.WAITING_FOR_COLLISION_RESOLUTION:
            self._resolve_collision()

    def _transmit(self) -> None:
        # check if wire is free and send jam signal and set state to collision resolution
        self._signal_propagation_counter += 1
        if self._signal_propagation_counter == self._wire_max_distnace / 2:
            self._wire.remove_signal(self._position_in_wire, self._symbol)
        elif self._signal_propagation_counter == self._wire_max_distnace:
            self._state = self.State.RECEIVING

    def send_packet(self) -> None:
        if self._wire.is_free(self._position_in_wire, self._symbol):
            self._state = self.State.TRANSMITTING
            self._signal_propagation_counter = 0
            self._wire.add_signal(self._position_in_wire, self._symbol)
        else:
            self._state = self.State.WAITING_FOR_WIRE

    def _generate_random_time_interval(self) -> float:
        pass

    def _resolve_collision(self) -> None:
        pass
