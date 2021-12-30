#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int ITERATIONS = 1000000000;
static const int INITIAL_BET = 10;

#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))

typedef struct {
    int wallet;
    int bet;
    int low;
    int high;
    int streak;
    int best_streak;
    int worst_streak;
} Player;

Player Player_init(int bet)
{
    Player new = {
        .wallet = 0,
        .bet = bet,
        .high = 0,
        .low = 0,
        .streak = 0,
        .best_streak = 0,
        .worst_streak = 0,
    };
    return new;
}

void Player_update(Player *p, int win)
{
    p->wallet += win ? p->bet : -p->bet;
    p->bet = p->wallet < 0 ? -p->wallet : INITIAL_BET;
    p->low = MIN(p->wallet, p->low);
    p->high = MAX(p->wallet, p->high);
    p->streak = ((p->streak >= 0) == win)
        ? (p->streak + ((p->streak >= 0) - (p->streak < 0)))
        : (win ? 1 : -1);
    p->best_streak = MAX(p->streak, p->best_streak);
    p->worst_streak = MIN(p->streak, p->worst_streak);
}

int main(void)
{
    srand(time(NULL));

    Player player = Player_init(INITIAL_BET);

    printf("Running %d iterations with inital bet of %d\n", ITERATIONS, INITIAL_BET);
    for (int i = 0; i < ITERATIONS; ++i) {
        int win = rand() % 2;
        Player_update(&player, win);
    }

    printf("      Winnings: %d\n", player.wallet);
    printf("  Session High: %d\n", player.high);
    printf("   Session Low: %d\n", player.low);
    printf("   Best Streak: %d\n", player.best_streak);
    printf("  Worst Streak: %d\n", player.worst_streak);
}
