class VendingMachine {
    int balance = 0;
}

public class Main {
    public static void handleReturn(VendingMachine vm) {
        int[] units = {500, 100, 50, 10};
        System.out.print("반환 내역: ");
        for (int i = 0; i < 4; i++) {
            int count = vm.balance / units[i];
            if (count > 0) {
                System.out.print("[" + units[i] + "원:" + count + "개] ");
            }
            vm.balance %= units[i];
        }
        System.out.println();
    }

    public static void inputSignal(VendingMachine vm, int type, int val) {
        switch (type) {
            case 1:
                if (val == 500 || val == 100 || val == 50 || val == 10) {
                    vm.balance += val;
                    System.out.println(val + "원 투입. 현재 잔액: " + vm.balance + "원");
                } else {
                    System.out.println("인식 불가 동전입니다: " + val + "원 반환");
                }
                break;
                
            case 2:
                if (vm.balance >= 200) {
                    System.out.println("음료 지급 완료");
                    vm.balance -= 200;
                    System.out.println("   남은 잔액: " + vm.balance + "원");

                    if (vm.balance < 200) {
                        System.out.println("잔액 200원 미만 자동 반환 작동");
                        handleReturn(vm);
                    }
                } else {
                    System.out.println("잔액 부족 (현재 " + vm.balance + "원)");
                }
                break;
                
            case 3: 
                System.out.println("반환 버튼 눌림");
                handleReturn(vm);
                break;
        }
    }

    public static void main(String[] args) {
        VendingMachine vm = new VendingMachine();
        System.out.println("--- 자판기 시뮬레이션 시작 ---");

        inputSignal(vm, 1, 1000); 
        inputSignal(vm, 1, 500);  
        inputSignal(vm, 2, 0);
        inputSignal(vm, 2, 0);  
    }
}
