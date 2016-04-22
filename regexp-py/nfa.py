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


class NFA:
    def __init__(self, states=[], final_state_index=0):
        self.states = states
        self.transitions = []
        self.final_state_index = final_state_index
        self.set_final_state(final_state_index)

    def get_states(self):
        return self.states

    def count_states(self):
        return len(self.states)

    def add_state(self, name):
        self.states.append(State(name))

    def set_final_state(self, i):
        if i < len(self.states) and self.states[i]:
            self.states[self.final_state_index].set_final(False)
            self.states[i].set_final(True)
            self.final_state_index = i

    def get_state(self, i):
        if i < len(self.states) and self.states[i]:
            return self.states[i]
        return None

    def get_final_state(self):
        return self.final_state_index

    def add_transition(self, state_from, state_to, symbol):
        self.transitions.append(Transition(state_from, state_to, symbol))
        s_from = self.states[state_from]
        s_to = self.states[state_to]
        trans = Transition(s_from, s_to, symbol)
        s_from.add_trans(trans)

    def display(self):
        for st in self.states:
            for trans in st.transitions:
                name = trans.t_to.name
                state_to = '{' + name + '}' if trans.t_to.is_final else ' ' + name + ' '
                print trans.t_from.name, ' -->', state_to, ' : Symbol - ', trans.t_symbol

                #
                # void display() {
                #     trans new_trans;
                #     cout<<"\n";
                #     for(int i = 0; i < transitions.size(); i++) {
                #         new_trans = transitions.at(i);
                #         cout<<"q"<<new_trans.vertex_from<<" --> q"<<new_trans.vertex_to<<" : Symbol - "<<new_trans.trans_symbol<<endl;
                #     }
                #     cout<<"\nThe final state is q"<<get_final_state()<<endl;
                # }


class DFA:
    pass
