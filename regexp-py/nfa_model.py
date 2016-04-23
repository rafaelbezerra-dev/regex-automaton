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
    pass

class NFA:
    EPSILON = ":e:"

    def __init__(self, states=None, final_state_index=0, transitions=None):
        # type: (List[State], int) -> NFA
        self.table = NFA_TABLE()

        self.states = states if states else []
        i = 0
        for state in self.states:
            self.table.add_transition(i, i, NFA.EPSILON)
            i+=1

        self.transitions = []
        if transitions:
            for trans in transitions:
                self.add_transition(trans.t_from, trans.t_to, trans.t_symbol)
        self.final_state_index = final_state_index
        self.set_final_state(final_state_index)

    def get_states(self):
        return self.states

    def count_states(self):
        return len(self.states)

    def add_state(self, name):
        self.states.append(State(name))
        i = len(self.states) - 1
        self.table.add_transition(i, i, NFA.EPSILON)

    def set_final_state(self, i):
        if i < len(self.states) and self.states[i]:
            self.states[self.final_state_index].set_final(False)
            self.states[i].set_final(True)
            self.final_state_index = i
            self.table.set_final_state(i)

    def get_state(self, i):
        if i < len(self.states) and self.states[i]:
            return self.states[i]
        return None

    def get_final_state(self):
        return self.final_state_index

    def add_transition(self, state_from, state_to, symbol):
        s_from = self.states[state_from]
        s_to = self.states[state_to]
        trans = Transition(s_from, s_to, symbol)
        s_from.add_trans(trans)

        self.transitions.append(Transition(state_from, state_to, symbol))
        self.table.add_transition(state_from, state_to, symbol)
        # alph_key = "{}__{}".format(state_from, symbol)
        # self.alphabet[alph_key] = state_to

    def display(self):
        for st in self.states:
            for trans in st.transitions:
                name = trans.t_to.name
                state_to = '{' + name + '}' if trans.t_to.is_final else ' ' + name + ' '
                print trans.t_from.name, ' -->', state_to, ' : Symbol - ', trans.t_symbol


class DFA:
    pass


class NFA_TABLE():
    EPSILON = NFA.EPSILON

    def __init__(self):
        self.tb = dict([])
        self.alphabet = []
        self.final_state_index = 0
        pass

    def set_final_state(self, i):
        self.final_state_index = i

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

    def to_dfa_table(self):
        alphabet = list(self.alphabet)
        alphabet.remove(NFA_TABLE.EPSILON)
        start = [0]
        stack = [start]
        dfa_tb = dict([])
        automata = NFA([State('q' + str(start))])
        i = 0
        while len(stack) > 0:
            # dict([(symbol, [state_to])])
            dfa_st = dict([])
            state_set = stack.pop()
            for state_index in state_set:
                st = self.tb[state_index]
                for symbol, states in st.iteritems():
                    if symbol in dfa_st:
                        for s in states:
                            if s not in dfa_st[symbol]:
                                dfa_st[symbol].append(s)
                    else:
                        dfa_st[symbol] = list(states)

            dfa_tb[i] = dfa_st
            j = i + 1
            for symbol in alphabet:
                if symbol in dfa_st:
                    # print row[symbol]
                    next = dfa_st[symbol][0]
                    next_set = self.tb[next][NFA_TABLE.EPSILON]
                    stack.append(next_set)
                    automata.add_state('q' + str(next_set))
                    automata.get_state(automata.count_states()-1).is_false = self.final_state_index in next_set
                    automata.add_transition(i, j, symbol)
                    j += 1
            i += 1

        print '\n### DFA ###'
        # automata.display()
        automata.table.display()

    def display(self):
        from tabulate import tabulate
        print '\n### TRANSITION TABLE ###'
        self.alphabet.remove(NFA_TABLE.EPSILON)
        self.alphabet.append(NFA_TABLE.EPSILON)
        print_table = []
        headers = ['States']
        for symbol in self.alphabet:
            headers.append(symbol)
        print_table.append(headers)

        for state, row in self.tb.iteritems():
            l = str(state)
            if self.final_state_index == state:
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

class DFA_TABLE():
    pass