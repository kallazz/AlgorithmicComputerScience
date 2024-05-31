from typing import List
import time
from wire import Wire


class Device:
    def __init__(self, wire: Wire, position_in_wire: int) -> None:
        self._wire = wire
        self._position = position_in_wire

    def _generate_random_time_interval(self) -> float:
        pass

    def _resolve_collision(self) -> None:
        pass

    def _spread_signal(self) -> bool:
        for i in range(len(self._wire), start=self._position):
            if self._is_collision(i):
                return False
            self._wire.set_signal(i, self._position)

        for i in range(len(self._wire), start=self._position):
            if self._is_collision(i):
                return False
            self._wire.reset_signal(i)

        return True

    def send_packet(self) -> None:
        was_successful = self._spead_signal()
        if not was_successful:
            self._resolve_collision()
