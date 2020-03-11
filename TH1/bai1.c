#include <stdio.h>
#include <conio.h>

//khai bai bien local
#define tankcapacity_X 9 //cuc chua binh x
#define tankcapacity_Y 4
#define emmty 0
#define goal 6 //muc tieu can dong duoc
#define Maxlength 100 // su dung stack

const char* action[] = {"Frist State","pour Water Full X","pour Water Full X",
                        "pour Water Empty X","pour Water Empty Y",
                        "pour Water X to Y","pour Water y to X"
                        };


typedef struct 
{
    int x;
    int y;
}State ;

int max(int a,int b){
    (a>b) ?  a :  b;
}
int min(int a,int b){
    a<b ? a:b;
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
        result->x = tankcapacity_X;
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

void print_a(State result,int option){
    printf("thuc hien hanh dong %d thanh conf",action[option]);
            print_State(result);
}

int main(){
    
    State cur_state={5,4}, result;
    printf("Trang thai bat dau: ");
    print_State(cur_state);
    int option;
    for(option=1 ; option <=6; option++){
        if (call_operator(cur_state, &result, option)==1) {
            printf("\nthuc hien hanh dong %s thanh cong\n",action[option]);
            print_State(result);
        }
        else
        {
            printf("\nkhong Thanh cong %s\n", action[option]);
        }
        
    }

    printf("asdasd");

    return 0;
}
