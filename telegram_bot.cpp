#include "telegram_bot.h"
#include "bot_logic.h"
#include <iostream>

void TelegramBot::run(const std::string& token) {
    TgBot::Bot bot(token);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id,
        "Welcome to the University Travel Guide Bot! 🎓\n\n"
        "Here’s how you can use this bot:\n"
        "✅ Type your query in the format `start-end` (e.g., `Library-11thblock`).\n"
        "✅ Use /help to see more information.\n"
        "Let’s find the best route for you! 😊");
});

bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id,
        "Commands you can use:\n\n"
        "🔹 `/start` - Start the bot and see instructions.\n"
        "🔹 `/help` - Get usage information.\n"
        "🔹 Type `start-end` (e.g., library-boysHostel) to get directions.\n\n"
        "Enjoy exploring the campus! 🚶");
});



    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (!message->text.empty()) {
            BotLogic logic;

            // Process user input
            std::string response = logic.handleUserMessage(message->text);

            bot.getApi().sendMessage(message->chat->id, response);
        }
    });

    try {
        std::cout << "Bot is running..." << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
