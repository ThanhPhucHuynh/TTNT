#include <stdio.h>
#include "bai1.c"
#include <malloc.h>
typedef struct Node {
	State state;
	struct Node* Parent;
	int no_function;
}Node;

//const char*  action[] = {"first State", "pour Water Full X", "pour Water Full Y","pour Water Empty X", "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"
//};

typedef struct {
	Node* Elements[Maxlength];
	int Top_idx;
}Stack;

void makeNull_Stack(Stack* S) {
	S->Top_idx = Maxlength;	
}

int empty_Stack(Stack S) {
	return S.Top_idx == Maxlength;	
}

int full_Stack(Stack S) {
	return S.Top_idx == 0;	
}

void push(Node* x, Stack* stack) {
	if(full_Stack(*stack)) printf("Error! Stack is full");
	else {
		stack->Top_idx -= 1;
		stack->Elements[stack->Top_idx] = x;
	}
}
// Tra ve phan tu tren dinh ngan xep
Node* top(Stack S) {
	if(!empty_Stack(S))
		return S.Elements[S.Top_idx];
	return NULL;
}

// Xoa phan tu tai dinh ngan xep
void pop(Stack* S) {
	if(!empty_Stack(*S))
		S->Top_idx+=1;
	else printf("Error! Stack is empty");
}

int compareStates(State s1, State s2) {
	if(s1.x == s2.x && s1.y == s2.y)
		return 1;
	else return 0;
}

int find_State(State state, Stack openStack) {
	while(!empty_Stack(openStack)) {
		if(compareStates(top(openStack)->state, state))
			return 1;
		pop(&openStack);
	}	
	return 0;
}

// Giai thuan tim kiem chieu sau depth - first - search

Node* DFS_Algorithm(State state) {
	//Khoi tao ngan xep
	Stack Open_DFS;
	Stack Close_DFS;
	makeNull_Stack(&Open_DFS);
	makeNull_Stack(&Close_DFS);
	// Tao nut trang thai cha
	Node* root = (Node* )malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	push(root, &Open_DFS);
	
	while(!empty_Stack(Open_DFS))  {
		//Lay mot dinh trong ngan xep 
		Node* node = top(Open_DFS);
		pop(&Open_DFS);
		push(node, &Close_DFS);
		
		// Check dinh lay ra co phai trang thai muc tieu?
		
		if(goalcheck(node->state))
			return node;
		int opt;
		
		// Goi cac phep toan tren trang thai
		for(opt=1 ; opt<=6 ; opt++) {
			State newstate;
			makeNullState(&newstate);
			if(call_operator(node->state, &newstate, opt)) {
				//Neu trang thai moi sinh ra da ton tai thi bo qua
				if(find_State(newstate, Close_DFS) || find_State(newstate, Open_DFS))
					continue;
				
				//Neu trang thai moi chua ton tai thi them vao ngan xep
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->state = newstate;
				newNode->Parent = node;
				newNode->no_function = opt;
				push(newNode, &Open_DFS);
			}	
		}
	}
	return NULL;
}



void print_WaysToGetGoal(Node* node) {
	Stack stackPrint;
	makeNull_Stack(&stackPrint);
	// Duyet nguoc ev nut parent
	while(node->Parent != NULL) {
		push(node, &stackPrint);
		node = node->Parent;	
	}
	push(node, &stackPrint);
	// In ra thu tu hanh dong chuyen nuoc
	int no_action = 0;
	while(!empty_Stack(stackPrint)) {
		printf("\nAction %d: %s", no_action, action[top(stackPrint)->no_function]);	
		print_State(top(stackPrint)->state);
		pop(&stackPrint);
		no_action++;
	}
}
int main() {
	State cur_state = {0, 0};
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
	
}
