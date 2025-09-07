/*
 * RFC865: Quote of the Day Protocol
 * https://datatracker.ietf.org/doc/html/rfc865
 *
 * Common declarations for TCP / UDP client & server
 */

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>   /* for size_t */

/* Return codes */
#define SUCCESS 0
#define ERROR   -1

/* Server defaults */
#define SERVER_IPv4 "127.0.0.1"
#define SERVER_IPv6 "::1"
#define SERVER_PORT 17

/* Buffers */
#define BUFFER_SIZE 512

/* Prototypes */
void rfc865Discription(int isTcp);
void printHelp(char *program);

/* Random quote helper (実装は common.c 例を参照) */
void initQuoteRandom(void);
const char *getRandomQuote(void);

static const char *QUOTES[] = {
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

static const size_t QUOTE_COUNT = sizeof(QUOTES) / sizeof(QUOTES[0]);

#endif /* COMMON_H */
