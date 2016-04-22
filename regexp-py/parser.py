from nfa import *

def concat(left_nfa, right_nfa):
    n_states = left_nfa.count_states() + right_nfa.count_states() - 1
    state_list = []
    for i in range(n_states):
        state_list.append(State('q' + str(i)))

    res = NFA(state_list, n_states-1)

    i = 0
    for trans in left_nfa.transitions:
        i += 1
        res.add_transition(trans.t_from, trans.t_to, trans.t_symbol)

    for trans in right_nfa.transitions:
        res.add_transition(trans.t_from+i, trans.t_to+i, trans.t_symbol)
    return res

def kleene_star(nfa):
    pass

def or_selection(nfa_list, n_selections):
    pass

def re_to_nfa(regexp):
    pass

def main():
    q1 = State('q1')
    q2 = State('q2')
    _nfa_ = NFA([q1, q2], 1)
    # _nfa_.get_state(0).add_transition(_nfa_.get_state(1), 'a')
    _nfa_.add_transition(0, 1, 'a')
    print 'NFA 1'
    _nfa_.display()
    print ''


    _nfa_2 = NFA()
    _nfa_2.add_state('s1')
    _nfa_2.add_state('s2')
    _nfa_2.add_transition(0, 1, 'b')
    _nfa_2.set_final_state(1)
    print 'NFA 2'
    _nfa_2.display()
    print ''

    print 'CONCAT'
    concat(_nfa_, _nfa_2).display()
    print ''


if __name__ == '__main__':
    main()
