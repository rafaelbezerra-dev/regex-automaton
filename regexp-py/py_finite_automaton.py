class Transition:
    def __init__(self, t_from, t_to, t_symbol):
        self.t_from = t_from
        self.t_to = t_to
        self.t_symbol = t_symbol

class State:
    def __init__(self, name=None):
        self.name = name
        self.transitions = []
        self.is_final = False

    def set_final(self, is_final):
        self.is_final = is_final

    def add_trans(self, trans):
        self.transitions.append(trans)


class FiniteAutomaton:
    EPSILON = ":e:"
