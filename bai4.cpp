#include <stdio.h>
#include <malloc.h>
#include <stack>

#define tankcapacity_X 9 //cuc chua binh x
#define tankcapacity_Y 4
#define emmty 0
#define goal 6 //muc tieu can dong duoc
#define Maxlength 100 // su dung stack
const char*  action[] = {"first State", "pour Water Full X", "pour Water Full Y","pour Water Empty X", "pour Water Empty Y", "pour Water X to Y", "pour Water Y to X"
};
using namespace std;

typedef struct 
{
    int x;
    int y;
}State ;

int max(int a,int b){
    return (a>b) ?  a :  b;
}
int min(int a,int b){
   return  (a<b) ? a:b;
}

void makeNullState(State *state){
    state->x = 0;
    state->y = 0;
}
void print_State(State state){
    printf("\n X: %d ---- Y: %d",state.x,state.y);
}
//kiem tra co dung muc tieu
int goalcheck(State state){ 
    return(state.x==goal || state.y == goal);
}
int poutWaterFullX(State cur_state, State *result){
    if(cur_state.x <tankcapacity_X){
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int poutWaterFullY(State cur_state, State *result){
    if(cur_state.y <tankcapacity_Y){
        result->y = tankcapacity_Y;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}
int poutWaterEmptyX(State cur_state, State *result){
    if(cur_state.x > 0){
        result->x = emmty;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}

int poutWaterEmptyY(State cur_state, State *result){
        if(cur_state.y > 0){
        result->y = emmty;
        result->x = cur_state.x;
        return 1;
    }
    return 0;
}

int poutWaterXY(State cur_state, State *result){
    if(cur_state.x > 0 && cur_state.y < tankcapacity_Y){
        result->x = max(cur_state.x - (tankcapacity_Y - cur_state.y ), emmty);
        result->y = min(cur_state.x + cur_state.y, tankcapacity_Y);
        return 1;
    }
    return 0;
}

int poutWaterYX(State cur_state, State *result){
    if(cur_state.y > 0 && cur_state.x < tankcapacity_X){
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x ), emmty);
        result->x = min(cur_state.y + cur_state.x, tankcapacity_X);
        return 1;
    }
    return 0;
}

int call_operator(State cur_state, State *result, int option){
    switch (option)
    {
    case 1: return poutWaterFullX(cur_state, result);
    case 2: return poutWaterFullY(cur_state, result);
    case 3: return poutWaterEmptyX(cur_state, result);
    case 4: return poutWaterEmptyY(cur_state, result);
    case 5: return poutWaterXY(cur_state, result);
    case 6: return poutWaterYX(cur_state, result);
    
    default: printf("Erro calls oparator");
        return 0;
        //break;
    }
}



typedef struct Node {
	State state;
	struct Node* Parent;
	int no_function;
}Node;


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
// int compareStates(State a, State b){
//     (a.x == b.x && a.y == b.y) ? 1 : 0;
// }

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

int find_State(State state, stack<Node*> openStack) {
	while(!openStack.empty()) {
		if(compareStates(openStack.top()->state, state))
			return 1;
		openStack.pop();
	}	
	return 0;
}

// Giai thuan tim kiem chieu sau depth - first - search

Node* DFS_Algorithm(State state) {
	//Khoi tao ngan xep
	stack<Node*> Open_DFS;
	stack<Node*> Close_DFS;
	// Open_DFS.
	// Close_DFS);
	// Tao nut trang thai cha
	Node* root = (Node* )malloc(sizeof(Node));
	root->state = state;
	root->Parent = NULL;
	root->no_function = 0;
	//push(root, &Open_DFS);
	Open_DFS.push(root);
	while(!(Open_DFS.empty()))  {
		//Lay mot dinh trong ngan xep 
		Node* node = Open_DFS.top();//top(Open_DFS);
		//pop(&Open_DFS);
        Open_DFS.pop();
		//push(node, &Close_DFS);
        Close_DFS.push(node);
		
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
				//push(newNode, &Open_DFS);
                Open_DFS.push(newNode);
			}	
		}
	}
	return NULL;
}



void print_WaysToGetGoal(Node* node) {
	stack<Node*> stackPrint;
	//makeNull_Stack(&stackPrint);
	// Duyet nguoc ev nut parent
	while(node->Parent != NULL) {
		//push(node, &stackPrint);
        stackPrint.push(node);
		node = node->Parent;	
	}
//	push(node, &stackPrint);
    stackPrint.push(node);
	// In ra thu tu hanh dong chuyen nuoc
	int no_action = 0;
	while(!stackPrint.empty()) {
		printf("\nAction %d: %s", no_action, action[stackPrint.top()->no_function]);	
		print_State(stackPrint.top()->state);
		stackPrint.pop();
		no_action++;
	}
}

int main() {
	State cur_state = {0, 0};
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
	
}