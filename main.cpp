#include "telegram_bot.h"

int main() {
    const std::string token = "7581559329:AAE25Vemc8ahl3diku1yxGVLWhgxwV9vwPk";

    TelegramBot bot;
    bot.run(token);

    return 0;
}
