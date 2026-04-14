VALID_COINS = [500, 100, 50, 10]
PRICE = 200

balance = 0


def return_module():
    global balance

    print("\n[거스름돈 반환 모듈]")
    print("반환 시작")

    change = {}
    remaining = balance

    for coin in VALID_COINS:
        count = remaining // coin
        if count > 0:
            change[coin] = count
            remaining %= coin

    if change:
        print("거스름돈 반환 내역:")
        for coin, count in change.items():
            print(f"{coin}원 x {count}")
    else:
        print("반환할 거스름돈 없음")

    balance = 0
    print("잔액 0원 초기화")
    print("반환 종료\n")


while True:
    print(f"현재 잔액: {balance}원")
    signal = input("어떤 신호인가? (동전 투입 / 지급 버튼 / 반환 버튼 / 종료): ").strip()

    if signal == "동전 투입":
        try:
            coin = int(input("동전 금액 입력: ").strip())
        except ValueError:
            print("잘못된 동전 입력")
            continue

        if coin in VALID_COINS:
            if coin < PRICE:
                print(f"200원 미만 동전 반환: {coin}원")
            else:
                balance += coin
                print(f"잔액 합산 -> 현재 잔액: {balance}원")
        else:
            print(f"해당 동전 반환: {coin}원")

    elif signal == "지급 버튼":
        if balance >= PRICE:
            print("음료 지급")
            balance -= PRICE
            print(f"200원 차감 -> 현재 잔액: {balance}원")

            if balance < PRICE:
                return_module()
        else:
            print("잔액 부족, 지급 불가")

    elif signal == "반환 버튼":
        return_module()

    elif signal == "종료":
        print("프로그램 종료")
        break

    else:
        print("잘못된 신호 무시")
