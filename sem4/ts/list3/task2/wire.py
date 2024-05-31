import time

class Wire:
    DEFAULT_SIGNAL = 0
    SIGNAL_LATENCY_MILLISECONDS = 10

    def __init__(self, length: int) -> None:
        self._wire = [0] * length

    def set_signal(self, position: int, signal: int) -> None:
        time.sleep(self.SIGNAL_LATENCY_MILLISECONDS)
        self._wire[position] = signal

    def reset_signal(self, position: int) -> None:
        time.sleep(self.SIGNAL_LATENCY_MILLISECONDS)
        self._wire[position] = self.DEFAULT_SIGNAL

    def is_collision(self, position: int) -> bool:
        return self._wire[position] != self.DEFAULT_SIGNAL
