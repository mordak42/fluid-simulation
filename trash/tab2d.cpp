
#include <iostream>

#define auto_init(variable, value) std::decay<decltype(value)>::type variable = value

namespace mod1
{

class Banane {
public:
    Banane() {
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                for (int k = 0; k < 1000; k++) {
                    a[i][j][k] = 42;
                }
            }
        }
    }
    int a[1000][1000][1000];
};

class Receiver {
public:
    Receiver(const std::shared_ptr<mod1::Banane> &pool);
    ~Receiver();
private:
    const std::shared_ptr<mod1::Banane> meuh = nullptr;
};

Receiver::Receiver(const std::shared_ptr<mod1::Banane> &pool) : meuh(pool) {
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            for (int k = 0; k < 1000; k++) {
                meuh->a[i][j][k] = meuh->a[i][j][k] + 1;
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            for (int k = 0; k < 1000; k++) {
                std::cout << meuh->a[i][j][k] << std::endl;
            }
        }
    }
}

Receiver::~Receiver() {}

}

int main(void) {


    const std::shared_ptr<mod1::Banane> banane = std::make_shared<mod1::Banane>();
    mod1::Receiver *test = new mod1::Receiver(banane);
    (void)test;
    return 0;
}
