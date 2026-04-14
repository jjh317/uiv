class VendingMachine:
    def __init__(self):
        self.balance = 0

def handle_return(vm):
    units = [500, 100, 50, 10]
    print("반환 내역: ", end="")
    for unit in units:
        count = vm.balance // unit
        if count > 0:
            print(f"[{unit}원:{count}개] ", end="")
        vm.balance %= unit
    print()

def input_signal(vm, type_val, val=0):
    if type_val == 1:
        if val in [500, 100, 50, 10]:
            vm.balance += val
            print(f"{val}원 투입. 현재 잔액: {vm.balance}원")
        else:
            print(f"인식 불가 동전입니다: {val}원 반환")
            
    elif type_val == 2:
        if vm.balance >= 200:
            print("음료 지급 완료")
            vm.balance -= 200
            print(f"남은 잔액: {vm.balance}원")

            if vm.balance < 200:
                print("잔액 200원 미만 자동 반환 작동")
                handle_return(vm)
        else:
            print(f"잔액 부족 (현재 {vm.balance}원)")
            
    elif type_val == 3:
        print("반환 버튼 눌림")
        handle_return(vm)

if __name__ == "__main__":
    vm = VendingMachine()
    print("--- 자판기 시뮬레이션 시작 ---")

    input_signal(vm, 1, 1000)
    input_signal(vm, 1, 500)
    input_signal(vm, 2, 0)
    input_signal(vm, 2, 0)