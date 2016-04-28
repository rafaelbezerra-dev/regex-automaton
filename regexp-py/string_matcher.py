from py_dfa import *


class StringMatcher:
    def __init__(self, regexp):
        self.regexp = regexp
        # nfa = DFA_Builder.re_to_nfa(self.regexp)
        # nfa.display()
        # nfa.displayTable()
        self.dfa = DFA_Builder.re_to_dfa(self.regexp)
        # self.dfa.display()
        # self.dfa.displayTable()
        self.matched_indexes = []


    def match_agaisnt(self, source):
        dfa_table = self.dfa.table

        curr_state_index = 0
        # curr_state = self.dfa.get_state(curr_state_index)
        matched_index = None
        letter_index = 0

        for letter in source:
            next_state_index = 0

            if letter in dfa_table.tb[curr_state_index]:
                next_state_index = dfa_table.tb[curr_state_index][letter][0]
                if curr_state_index != next_state_index and not matched_index:
                    matched_index = [letter_index]
                next_state = self.dfa.get_state(next_state_index)
                if next_state and next_state.is_final:
                    matched_index.append(letter_index)
                    self.matched_indexes.append(matched_index)
                    matched_index = None
                if next_state_index == 0:
                    matched_index = None

            curr_state_index = next_state_index
            letter_index += 1

        print '\n\n### MATCH STRING RESULT ###'
        for matched_index in self.matched_indexes:
            letter_from, letter_to = matched_index
            print source[letter_from: letter_to+1], matched_index



