#include <stdio.h>

struct uint1024_t {
    unsigned short int numbers[80];
};

struct uint1024_t clear_number(struct uint1024_t number_for_clean) {
    for (int i = 0; i <= 79; i++)
        number_for_clean.numbers[i] = 0;
    return number_for_clean;
}

int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int get_number_by_key(int x, int y) {
    switch (y) {
        case 1 : return x % 10;
        case 2 : return (x % 100) / 10;
        case 3 : return (x % 1000) / 100;
        case 4 : return (x % 10000) / 1000;
    }
}

int transfer(int x, int y) {
    switch (x / 10000) {
        case 0 : return x + 10000 + y;
        case 1 : return x + 10000 + y * 10;
        case 2 : return x + 10000 + y * 100;
        case 3 : return x + 10000 + y * 1000;
    }
}

struct uint1024_t remake_number(struct uint1024_t n) {
    struct uint1024_t m;
    m = clear_number(n);
    int i = 79;
    int j = 79;
    while (n.numbers[i] == 0)
        i--;
    int pos_now = 1;
    int pos_limit = n.numbers[i] / 10000;
    while (n.numbers[0] != 0) {
        int transfer_number = get_number_by_key(n.numbers[i], pos_now);
        m.numbers[j] = transfer(m.numbers[j], transfer_number);
        if (pos_now == pos_limit) {
            n.numbers[i] = 0;
            pos_now = 0;
            pos_limit = 4;
            i--;
        }
        if (m.numbers[j] / 10000 == 4)
            j--;
        pos_now++;
    }
    return m;
}

struct uint1024_t scanf_value() {
    struct uint1024_t new;
    new = clear_number(new);
    char c;
    int k = 0;
    while ((c = getchar()) != '\n') {
        c = c - 48;
        new.numbers[k / 4] = ((new.numbers[k / 4] % 10000) * 10) + c + (k % 4 + 1) * 10000;
        k++;
    }
    new = remake_number(new);
    return new;
}

struct uint1024_t from_int_to_uint1024(int x) {
    struct uint1024_t new;
    new = clear_number(new);
    int power = 1;
    while (power * 10 <= x)
        power = power * 10;
    int k = 0;
    while (power != 0) {
        new.numbers[k / 4] = ((new.numbers[k / 4] % 10000) * 10) + x / power + (k % 4 + 1) * 10000;
        x = x % power;
        power = power / 10;
        k++;
    }
    new = remake_number(new);
    return new;
}

int int_pow(int x, int y) {
    int result = 1;
    for (int power = 1; power <= y; power++)
        result = result * x;
    return result;
}

void printf_numbers(int x) {
    int a[4];
    for (int pos = 1; pos <= 4; pos++)
        a[pos-1] = (x % int_pow(10, pos)) / int_pow(10, pos - 1);
    for (int pos = x / 10000 - 1; pos >= 0; pos--)
        printf("%d", a[pos]);
}

void printf_value(struct uint1024_t n) {
    for (int i = 0; i <= 79; i++)
        if (n.numbers[i] != 0)
            printf_numbers(n.numbers[i]);
}

int correct(int x) {
    if (x % 10000 >= 1000)
        return x % 10000 + 40000;
    else if (x % 10000 >= 100)
        return x % 10000 + 30000;
    else if (x % 10000 >= 10)
        return x % 10000 + 20000;
    else if(x % 10000 >= 1)
        return x % 10000 + 10000;
}

struct uint1024_t add(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t z;
    z = clear_number(z);
    int next = 0;
    int i = 79;
    while (x.numbers[i] % 10000 != 0 || y.numbers[i] % 10000 != 0 || next != 0) {
        z.numbers[i] = ((x.numbers[i] % 10000) + (y.numbers[i] % 10000) + next) % 10000;
        next = ((x.numbers[i] % 10000) + (y.numbers[i] % 10000) + next) / 10000;
        z.numbers[i] = z.numbers[i] + max(x.numbers[i] / 10000, y.numbers[i] / 10000) * 10000;
        i--;
    }
    z.numbers[i + 1] = correct(z.numbers[i + 1]);
    return z;
}

struct uint1024_t difference(struct uint1024_t x, struct  uint1024_t y) {
    struct uint1024_t z;
    z = clear_number(z);
    int next = 0;
    int i = 79;
    while (x.numbers[i] / 10000 != 0 || next != 0) {
        if (x.numbers[i] % 10000 > y.numbers[i] % 10000) {
            z.numbers[i] = ((x.numbers[i] % 10000) - (y.numbers[i] % 10000) - next) % 10000;
            next = 0;
            if (z.numbers[i - 1] == 0)
                z.numbers[i] = correct(z.numbers[i]);
            else
                z.numbers[i] = z.numbers[i] + 40000;
        }
        else {
            z.numbers[i] = ((x.numbers[i] % 10000) + 10000 - (y.numbers[i] % 10000) - next) % 10000;
            if (x.numbers[i - 1] % 10000 == 1)
                z.numbers[i] = correct(z.numbers[i]);
            else
                z.numbers[i] = z.numbers[i] + 40000;
            next = 1;
        }
        i--;
    }
    return z;
}

int main() {
    struct uint1024_t a, b, c;
    a = clear_number(a);
    a = scanf_value();
    b = clear_number(b);
    b = scanf_value();
    c = add(a, b);
    printf_value(c);
    return 0;
}