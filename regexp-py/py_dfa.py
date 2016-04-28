from py_finite_automaton import *

class DFA:
    def __init__(self, states=None, transitions=None):
        # type: (List[State], int) -> NFA
        self.table = DFA_TABLE()
        self.transitions = []
        self.final_states = []
        self.states = states if states else []

        if transitions:
            for trans in transitions:
                self.add_transition(trans.t_from, trans.t_to, trans.t_symbol)

    def get_states(self):
        return self.states

    def count_states(self):
        return len(self.states)

    def add_state(self, name):
        self.states.append(State(name))
        i = len(self.states) - 1

    def add_final_state(self, i):
        if i < len(self.states) and self.states[i]:
            self.states[i].set_final(True)
            self.table.add_final_state(i)

    def get_state(self, i):
        if i < len(self.states) and self.states[i]:
            return self.states[i]
        return None

    def get_final_states(self):
        return self.table.final_state_indexes

    def add_transition(self, state_from, state_to, symbol):
        s_from = self.states[state_from]
        s_to = self.states[state_to]
        trans = Transition(s_from, s_to, symbol)
        s_from.add_trans(trans)

        self.transitions.append(Transition(state_from, state_to, symbol))
        self.table.add_transition(state_from, state_to, symbol)

    def display(self):
        print '\n### DFA ###'
        for st in self.states:
            for trans in st.transitions:
                name = trans.t_to.name
                state_to = '{' + name + '}' if trans.t_to.is_final else ' ' + name + ' '
                print trans.t_from.name, ' -->', state_to, ' : Symbol - ', trans.t_symbol


class DFA_TABLE:
    def __init__(self):
        self.tb = dict([])
        self.alphabet = []
        self.final_state_indexes = []

    def add_final_state(self, i):
        self.final_state_indexes.append(i)

    def add_transition(self, state_from, state_to, symbol):
        if symbol not in self.alphabet:
            self.alphabet.append(symbol)
        if state_from in self.tb:
            row = self.tb[state_from]
            if symbol in row:
                row[symbol].append(state_to)
            else:
                row[symbol] = [state_to]
        else:
            self.tb[state_from] = dict([(symbol, [state_to])])

    def display(self):
        from tabulate import tabulate
        print '\n### DFA TRANSITION TABLE ###'
        print_table = []
        headers = ['States']
        for symbol in self.alphabet:
            headers.append(symbol)
        print_table.append(headers)

        for state, row in self.tb.iteritems():
            l = str(state)
            if state in self.final_state_indexes:
                l = '{' + l + '}'
            line = [l]
            for symbol in self.alphabet:
                if symbol in row:
                    line.append(str(row[symbol]))
                else:
                    line.append('--')
            print_table.append(line)
        # print tabulate([["Name", "Age"], ["Alice", 24], ["Bob", 19]], headers="firstrow")
        print tabulate(print_table, headers="firstrow")
