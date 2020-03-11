#include <stdio.h>
#include <stdlib.h>
#include "TH1-bai2.c"

int main() {
	State cur_state = {0, 0};
	Node* p = DFS_Algorithm(cur_state);
	print_WaysToGetGoal(p);
	return 0;
	
}
