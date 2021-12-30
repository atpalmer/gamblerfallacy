#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int ITERATIONS = 1000000000;
static const int INITIAL_BET = 10;

#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

struct session {
    int winnings;
    int bet;
    int low;
    int high;
    int streak;
    int best_streak;
    int worst_streak;
};

static struct session session_init(int bet)
{
    struct session new = {
        .winnings = 0,
        .bet = bet,
        .high = 0,
        .low = 0,
        .streak = 0,
        .best_streak = 0,
        .worst_streak = 0,
    };
    return new;
}

static void session_update(struct session *s, int win)
{
    s->winnings += win ? s->bet : -s->bet;
    s->bet = s->winnings < 0 ? -s->winnings : INITIAL_BET;
    s->low = MIN(s->winnings, s->low);
    s->high = MAX(s->winnings, s->high);
    s->streak = ((s->streak >= 0) == win)
        ? (s->streak + ((s->streak >= 0) - (s->streak < 0)))
        : (win ? 1 : -1);
    s->best_streak = MAX(s->streak, s->best_streak);
    s->worst_streak = MIN(s->streak, s->worst_streak);
}

int main(void)
{
    srand(time(NULL));

    struct session s = session_init(INITIAL_BET);

    printf("Running %d iterations with inital bet of %d\n", ITERATIONS, INITIAL_BET);
    for (int i = 0; i < ITERATIONS; ++i) {
        int win = rand() % 2;
        session_update(&s, win);
    }

    printf("      Winnings: %d\n", s.winnings);
    printf("  Session High: %d\n", s.high);
    printf("   Session Low: %d\n", s.low);
    printf("   Best Streak: %d\n", s.best_streak);
    printf("  Worst Streak: %d\n", s.worst_streak);
}
