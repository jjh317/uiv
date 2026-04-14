import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    static final int[] VALID_COINS = {500, 100, 50, 10};
    static final int PRICE = 200;
    static int balance = 0;

    static boolean isValidCoin(int coin) {
        for (int c : VALID_COINS) {
            if (c == coin) return true;
        }
        return false;
    }

    static void returnModule() {
        System.out.println("\n[거스름돈 반환 모듈]");
        System.out.println("반환 시작");

        Map<Integer, Integer> change = new LinkedHashMap<>();
        int remaining = balance;

        for (int coin : VALID_COINS) {
            int count = remaining / coin;
            if (count > 0) {
                change.put(coin, count);
                remaining %= coin;
            }
        }

        if (!change.isEmpty()) {
            System.out.println("거스름돈 반환 내역:");
            for (Map.Entry<Integer, Integer> entry : change.entrySet()) {
                System.out.println(entry.getKey() + "원 x " + entry.getValue());
            }
        } else {
            System.out.println("반환할 거스름돈 없음");
        }

        balance = 0;
        System.out.println("잔액 0원 초기화");
        System.out.println("반환 종료\n");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("현재 잔액: " + balance + "원");
            System.out.print("어떤 신호인가? (동전 투입 / 지급 버튼 / 반환 버튼 / 종료): ");
            String signal = sc.nextLine().trim();

            if (signal.equals("동전 투입")) {
                System.out.print("동전 금액 입력: ");
                String input = sc.nextLine().trim();

                int coin;
                try {
                    coin = Integer.parseInt(input);
                } catch (NumberFormatException e) {
                    System.out.println("잘못된 동전 입력");
                    continue;
                }

                if (isValidCoin(coin)) {
                    if (coin < PRICE) {
                        System.out.println("200원 미만 동전 반환: " + coin + "원");
                    } else {
                        balance += coin;
                        System.out.println("잔액 합산 -> 현재 잔액: " + balance + "원");
                    }
                } else {
                    System.out.println("해당 동전 반환: " + coin + "원");
                }

            } else if (signal.equals("지급 버튼")) {
                if (balance >= PRICE) {
                    System.out.println("음료 지급");
                    balance -= PRICE;
                    System.out.println("200원 차감 -> 현재 잔액: " + balance + "원");

                    if (balance < PRICE) {
                        returnModule();
                    }
                } else {
                    System.out.println("잔액 부족, 지급 불가");
                }

            } else if (signal.equals("반환 버튼")) {
                returnModule();

            } else if (signal.equals("종료")) {
                System.out.println("프로그램 종료");
                break;

            } else {
                System.out.println("잘못된 신호 무시");
            }
        }

        sc.close();
    }
}
