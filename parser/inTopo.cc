#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<vector>

using namespace std;

stack<char> stack_s;
queue<char> queue_t;
//vector<char> input_s;

string input(){
	cout<<"input Inorder: ";
	string expression;
	cin>> expression;
	return expression;
}
void change(const char *p){
	//char e;
	int flag = 1;
	while(*p){
		if((*p >= 'a' && *p<='z') ||(*p>='A'&&*p<='Z')||(*p>='0'&&*p<='9')){
			queue_t.push(*p);
			queue_t.push(' ');
		}
		else{
			if(*p == '(' || *p == ')'){
				if(*p == '(')
					stack_s.push(*p);
				else{
					while(stack_s.top()!='('){
						queue_t.push(stack_s.top());
						stack_s.pop();
						queue_t.push(' ');
					}
					stack_s.pop();
				}
			}
			else{
				if(*p == '*'|| *p == '+' || *p == '?'){
					if(stack_s.empty()||stack_s.top()=='|'||stack_s.top()=='.'||stack_s.top()=='(')
						stack_s.push(*p);
					else{
						while(!stack_s.empty()&&(stack_s.top()=='*'||stack_s.top()=='+' || stack_s.top() == '?')){
							queue_t.push(stack_s.top());
							stack_s.pop();
							queue_t.push(' ');
						}
						stack_s.push(*p);
					}
				}
				else if(*p == '.'){
					if(stack_s.empty()||stack_s.top() == '|'||stack_s.top()=='(')
						stack_s.push(*p);
					else{
						while(!stack_s.empty()&&((stack_s.top()=='.'||stack_s.top()=='*')||(stack_s.top()=='*'||stack_s.top()=='+'||stack_s.top()=='?'))){
							queue_t.push(stack_s.top());
							stack_s.pop();
							queue_t.push(' ');
						}
						stack_s.push(*p);
					}
				}
				else{
					if(stack_s.empty()||stack_s.top()=='(')
						stack_s.push(*p);
					else{
						while(!stack_s.empty()&&((stack_s.top()=='|'||stack_s.top()=='.')||(stack_s.top()=='*'||stack_s.top()=='+'||stack_s.top()=='?'))){
							queue_t.push(stack_s.top());
							stack_s.pop();
							queue_t.push(' ');
						}
						stack_s.push(*p);
					}
				}
			}
		}
		++p;
	}
	while(!stack_s.empty()){
		queue_t.push(stack_s.top());
		stack_s.pop();
		queue_t.push(' ');
	}
}
void output(){
	cout<<"Reverse Polish Notation：";
	while(!queue_t.empty()) {
			cout<<queue_t.front();
			queue_t.pop();
	}
	cout<<endl;
}

int main(){
	string input_s;
	input_s = input();
	const char *expr = input_s.c_str();
	change(expr);
	output();
}

