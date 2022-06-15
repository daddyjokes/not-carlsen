#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <stdint.h>
#include "util.h"


extern const uint64_t BB_KNIGHT_ATTACKS[64];
extern uint64_t BB_BISHOP_ATTACKS[64][512];
extern uint64_t BB_ROOK_ATTACKS[64][4096];
extern const uint64_t BB_KING_ATTACKS[64];


extern const uint64_t BISHOP_MAGICS[64];
extern const uint64_t ROOK_MAGICS[64];
extern uint64_t BB_BISHOP_ATTACK_MASKS[64];
extern uint64_t BB_ROOK_ATTACK_MASKS[64];
extern uint64_t ROOK_ATTACK_SHIFTS[64];
extern uint64_t BISHOP_ATTACK_SHIFTS[64];


void print_divided_perft(Board* board, Stack** stack, int depth);
uint64_t perft(Board* board, Stack** stack, int depth);

void gen_pseudolegal_moves(Move* moves, Board* board, bool color);
static int _get_flag(Board* board, bool color, char piece, int from, int to);

uint64_t get_pawn_moves(Board* board, bool color, int square);
uint64_t get_knight_moves(Board* board, bool color, int square);
uint64_t get_bishop_moves(Board* board, bool color, int square);
uint64_t get_rook_moves(Board* board, bool color, int square);
uint64_t get_queen_moves(Board* board, bool color, int square);
uint64_t get_king_moves(Board* board, bool color, int square);

void init_bishop_attacks(void);
void init_rook_attacks(void);
static uint64_t _init_bishop_attacks_helper(int square, uint64_t subset);
static uint64_t _init_rook_attacks_helper(int square, uint64_t subset);


#endif