#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int VALID_COINS[] = {500, 100, 50, 10};
const int COIN_COUNT = 4;
const int PRICE = 200;
int balance = 0;

void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

int parse_int(const char *s, int *out) {
    char *end;
    long v = strtol(s, &end, 10);
    if (end == s) return 0;
    while (*end == ' ' || *end == '\t') end++;
    if (*end != '\0') return 0;
    if (v < INT_MIN || v > INT_MAX) return 0;
    *out = (int)v;
    return 1;
}

int is_valid_coin(int coin) {
    for (int i = 0; i < COIN_COUNT; i++) {
        if (VALID_COINS[i] == coin) return 1;
    }
    return 0;
}

void return_module() {
    printf("\n[거스름돈 반환 모듈]\n");
    printf("반환 시작\n");

    int counts[4] = {0, 0, 0, 0};
    int remaining = balance;
    int has_change = 0;

    for (int i = 0; i < COIN_COUNT; i++) {
        counts[i] = remaining / VALID_COINS[i];
        if (counts[i] > 0) {
            has_change = 1;
            remaining %= VALID_COINS[i];
        }
    }

    if (has_change) {
        printf("거스름돈 반환 내역:\n");
        for (int i = 0; i < COIN_COUNT; i++) {
            if (counts[i] > 0) {
                printf("%d원 x %d\n", VALID_COINS[i], counts[i]);
            }
        }
    } else {
        printf("반환할 거스름돈 없음\n");
    }

    balance = 0;
    printf("잔액 0원 초기화\n");
    printf("반환 종료\n\n");
}

int main() {
    char signal[64];
    char coin_input[64];

    while (1) {
        printf("현재 잔액: %d원\n", balance);
        printf("어떤 신호인가? (동전 투입 / 지급 버튼 / 반환 버튼 / 종료): ");

        if (!fgets(signal, sizeof(signal), stdin)) break;
        trim_newline(signal);

        if (strcmp(signal, "동전 투입") == 0) {
            int coin;
            printf("동전 금액 입력: ");
            if (!fgets(coin_input, sizeof(coin_input), stdin)) break;
            trim_newline(coin_input);

            if (!parse_int(coin_input, &coin)) {
                printf("잘못된 동전 입력\n");
                continue;
            }

            if (!is_valid_coin(coin)) {
                printf("해당 동전 반환: %d원\n", coin);
                continue;
            }

            if (coin < PRICE) {
                printf("200원 미만 동전 반환: %d원\n", coin);
                continue;
            }

            balance += coin;
            printf("잔액 합산 -> 현재 잔액: %d원\n", balance);

        } else if (strcmp(signal, "지급 버튼") == 0) {
            if (balance >= PRICE) {
                printf("음료 지급\n");
                balance -= PRICE;
                printf("200원 차감 -> 현재 잔액: %d원\n", balance);

                if (balance < PRICE) {
                    return_module();
                }
            } else {
                printf("잔액 부족, 지급 불가\n");
            }

        } else if (strcmp(signal, "반환 버튼") == 0) {
            return_module();

        } else if (strcmp(signal, "종료") == 0) {
            printf("프로그램 종료\n");
            break;
        }
    }

    return 0;
}
