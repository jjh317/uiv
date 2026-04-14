#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int balance;
} VendingMachine;

void handle_return(VendingMachine *vm) {
    int units[] = { 500, 100, 50, 10 };
    printf("반환 내역: ");
    for (int i = 0; i < 4; i++) {
        int count = vm->balance / units[i];
        if (count > 0) printf("[%d원:%d개] ", units[i], count);
        vm->balance %= units[i];
    }
    printf("\n");
}

void input_signal(VendingMachine *vm, int type, int val) {
    switch (type) {
    case 1: 
        if (val == 500 || val == 100 || val == 50 || val == 10) {
            vm->balance += val;
            printf("%d원 투입. 현재 잔액: %d원\n", val, vm->balance);
        } else {
            printf("인식 불가 동전입니다: %d원 반환\n", val);
        }
        break;

    case 2:
        if (vm->balance >= 200) {
            printf("음료 지급 완료\n");
            vm->balance -= 200;
            printf("남은 잔액: %d원\n", vm->balance);
            
            if (vm->balance < 200) { 
                printf("잔액 200원 미만 자동 반환 작동\n");
                handle_return(vm);
            }
        } else {
            printf("잔액 부족 (현재 %d원)\n", vm->balance);
        }
        break;

    case 3: 
        printf("반환 버튼 눌림\n");
        handle_return(vm); 
        break;
    }
}

int main() 
{
    VendingMachine vm = {0};
    printf("--- 자판기 시뮬레이션 시작 ---\n");

    input_signal(&vm, 1, 1000); 
    input_signal(&vm, 1, 500);  
    input_signal(&vm, 2, 0);   
    input_signal(&vm, 2, 0);    
    return 0;
}