/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 * 
 * TCP Client, TCP Server, UDP Client, UDP Server code common functions
*/

#include <iostream>
#include <random>
#include <time.h>
#include <unistd.h>

#include "common.hpp"

const char *getRandomQuote(void)
{
    const char *QUOTES[] = {
        /* 既存ハッカー風 */
        "Code is a poem in logical form.",
        "Trust the code, verify the data.",
        "Ship small, break nothing, learn fast.",
        "Curiosity compiles innovation.",
        "Silence the noise, read the packets.",
        "From entropy we craft order.",
        "Optimize later is a trap.",
        "Read > Write > Refactor > Repeat.",
        "Data wins every argument.",
        "Logs are the truth serum.",

        /* 著名 / 古典的 (短縮形) */
        "Talk is cheap. Show me the code.",
        "Premature optimization is the root of all evil.",
        "Simplicity is prerequisite for reliability.",
        "Programs must be written for people to read.",
        "Weeks of coding can save hours of planning.",
        "Fix the cause, not the symptom.",
        "If it hurts, do it more often.",
        "Make it work, then make it right, then fast.",
        "There is no silver bullet.",
        "Perfect is the enemy of shipped.",

        /* ネーミング / 設計 */
        "Great names explain themselves.",
        "Constraints drive creativity.",
        "Delete is the strongest refactor.",
        "APIs are long-term promises.",
        "Guardrails beat after-the-fact checks.",
        "Design for change, optimize for today.",
        "Own the failure, share the credit.",
        "State is the hardest bug surface.",
        "Every TODO is interest accruing.",
        "Latency is a feature users feel.",

        /* 運用 / 信頼性 */
        "Assume packet loss. Prove delivery.",
        "Alert fatigue hides real fires.",
        "Observability is accelerated learning.",
        "Retry with backoff, not with hope.",
        "Cache invalidation is naming's evil twin.",
        "Rollback is the fastest hotfix.",
        "Measure first. Guess never.",
        "Logs age; metrics trend; traces narrate.",
        "Incidents document your real architecture.",
        "If it's not automated, it's broken.",

        /* セキュリティ / ハッカー感 */
        "Input is hostile until proven otherwise.",
        "Least privilege or later regret.",
        "Entropy feeds security.",
        "Audit trails deter ghosts.",
        "Surface area is attack opportunity.",
        "Secrets demand lifecycle, not storage.",
        "Trust boundaries are code boundaries.",
        "Cryptography is easy; key handling isn't.",
        "Patching beats perimeter myths.",
        "Defense in depth, not depth in excuses.",

        /* 開発文化 / 成長 */
        "Small merges reduce big regrets.",
        "Read code like an archaeologist.",
        "Refactor is continuous rent payment.",
        "Technical debt compounds silently.",
        "Feedback loops define velocity.",
        "Curiosity scales teams.",
        "Learning is the perpetual feature.",
        "Prototype invites reality checks.",
        "Boring technology compounds reliability.",
        "Quality is a habit in diff size.",

        /* 興味/インスピレーション */
        "Latency budgets are moral choices.",
        "Simplicity survives on-call nights.",
        "Determinism is kindness to future you.",
        "Documentation is executable empathy.",
        "Your future self is another maintainer.",
        "Version control is a time machine.",
        "Instrumentation is storytelling.",
        "Edge cases are users too.",
        "The strongest abstraction leaks least.",
        "Delete code; retain knowledge."
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    static const size_t QUOTE_COUNT = sizeof(QUOTES) / sizeof(QUOTES[0]);
    std::uniform_int_distribution<> dis(0, QUOTE_COUNT - 1);

    return QUOTES[dis(gen)];
}

void rfc865Description(int isTcp)
{
    const char description[] = 
        "RFC865: Quote of the Day Protocol\n"
        "https://datatracker.ietf.org/doc/html/rfc865\n"
        "This RFC specifies a standard for the ARPA Internet community.  Hosts on "
        "the ARPA Internet that choose to implement a Quote of the Day Protocol "
        "are expected to adopt and implement this standard.\n\n"
        "A useful debugging and measurement tool is a quote of the day service. "
        "A quote of the day service simply sends a short message without regard "
        "to the input.\n\n";

    const char tcp_description[] =
        "TCP Based Character Generator Service\n"
        "   One quote of the day service is defined as a connection based "
        "   application on TCP.  A server listens for TCP connections on TCP port "
        "   17.  Once a connection is established a short message is sent out the "
        "   connection (and any data received is thrown away).  The service "
        "   closes the connection after sending the quote.\n\n";

    const char udp_description[] = 
        "UDP Based Character Generator Service\n"
        "   Another quote of the day service is defined as a datagram based "
        "   application on UDP.  A server listens for UDP datagrams on UDP port "
        "   17.  When a datagram is received, an answering datagram is sent "
        "   containing a quote (the data in the received datagram is ignored).\n\n";

    const char quote_description[] = 
        "Quote Syntax\n"
        "   The quote consists of arbitrary ASCII characters, and may be any "
        "   length up to 512 characters.  It should be short enough to fit in a "
        "   single UDP datagram (including IP and UDP headers) if possible.  If "
        "   it is longer than 512 characters, it may be truncated or split into "
        "   multiple messages.\n\n";

    std::cout << description;
    std::cout << (isTcp ? tcp_description : udp_description);
    std::cout << quote_description;
}

void printHelp(char *program)
{
    std::cout   << "Usage: " << program << " [options]\n"
                << "Options:\n"
                << "  -h, --help          Show this help message and exit\n"
                << "  -d, --description   Show RFC865 description and exit\n"
                << "  -a, --address IP    Server IP address (default: " << SERVER_IP << ")\n"
                << "  -p, --port PORT     Server port number (default: " << SERVER_PORT << ")\n"
                << std::endl;
}
