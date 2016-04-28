# from collections import deque
# from Queue import *
from collections import deque

from py_finite_automaton import *
from py_nfa import *


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

    def displayTable(self):
        self.table.display()

    def from_nfa_table(self, nfa_table):
        # states_visited = []
        visited_sets = []
        queue = deque([])
        first_set = nfa_table.tb[0][FiniteAutomaton.EPSILON]
        queue.append(first_set)
        dfa_state_count = 0
        dfa_state_mapping = dict([(str(first_set), dfa_state_count)])
        self.add_state(str(first_set))
        nfa_states_count = len(nfa_table.tb)
        # for i in range(nfa_states_count):
        #     states_visited.append(False)

        while len(queue) > 0:
            curr_state_set = queue.popleft()
            if len(curr_state_set) == 0 or str(curr_state_set) in visited_sets:
                continue
            visited_sets.append(str(curr_state_set))
            state_name = str(curr_state_set)
            # dfa_state = State(str(curr_state_set))
            # if dfa_state.state_name not in dfa_state_mapping:
            #     # self.add_state()
            #     self.states.append(dfa_state)
            #     dfa_state_count += 1
            #     dfa_state_mapping[dfa_state.name] = dfa_state_count

            # complete_state_set = []
            is_final_state = False
            states_visited = [False] * nfa_states_count
            for curr_state in curr_state_set:
                states_visited[curr_state] = True
            for curr_state in curr_state_set:
                eclosure = nfa_table.tb[curr_state][FiniteAutomaton.EPSILON]
                for eclosure_state in eclosure:
                    if not states_visited[eclosure_state]:
                        curr_state_set.append(eclosure_state)
                        states_visited[eclosure_state] = True
            # print state_name, '(', curr_state_set, ')'
            for symbol in nfa_table.alphabet:
                if symbol == FiniteAutomaton.EPSILON:
                    continue
                next_set = []
                states_visited = [False] * nfa_states_count
                for curr_state in curr_state_set:
                    if curr_state == nfa_table.final_state_index:
                        is_final_state = True
                    if symbol in nfa_table.tb[curr_state]:
                        next_states = nfa_table.tb[curr_state][symbol]
                        for ns in next_states:
                            eclosure = nfa_table.tb[ns][FiniteAutomaton.EPSILON]
                            for eclosure_state in eclosure:
                                if not states_visited[eclosure_state]:
                                    next_set.append(eclosure_state)
                                    states_visited[eclosure_state] = True

                if len(next_set) > 0:
                    # print symbol, ' --> ', next_set
                    next_state_name = str(next_set)
                    if next_state_name not in dfa_state_mapping:
                        self.add_state(next_state_name)
                        dfa_state_count += 1
                        dfa_state_mapping[next_state_name] = dfa_state_count
                    self.add_transition(dfa_state_mapping[state_name], dfa_state_mapping[next_state_name], symbol)
                else:
                    self.add_transition(dfa_state_mapping[state_name], 0, symbol)
                if is_final_state:
                    self.add_final_state(dfa_state_mapping[state_name])

                if len(next_set) > 0 and str(next_set) not in visited_sets:
                    # visited_sets.append(str(next_set))
                    queue.append(next_set)

        self.display()
        self.displayTable()


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

