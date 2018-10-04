#include <iostream>
#include <vector>
#include <stack>

#define ROWS 6
#define COLOMS 7
#define AI 1
#define HUMAN -1
#define NONE 0

const int board_size = ROWS * COLOMS;

class game{
public:

    std::vector<signed char> board;


	game() {
		board.resize(board_size, NONE);
	}

    bool validate_move(int colom){    // проверяет что можно совершить ход в  colom, т.е. столбец не переполнен
		return (board[board_size - COLOMS + colom] == NONE);
	} 

    int calculate_heuristics(){} // высчитывает эвристику для текущего располжения доски
    signed char do_move(bool our_move,char colom){   // применяет ход(меняет доску) для нас(our_move == true) или для противника, возвращает AI(выграли мы),HUMAN(выграл Пучкин),NONE(не выигрышный ход)
		int i;
		for (i = ROWS - 1; i >= 0; --i) {
			if (board[i * COLOMS + colom] != NONE)
				break;
		}
		++i;
		board[i * COLOMS + colom] = our_move ? AI : HUMAN;

		if (is_won(i * COLOMS + colom))
			return our_move ? AI : HUMAN;
		else
			return NONE;
	}

private:
	bool is_won(int ind) {
		signed char type_pl = board[ind];
		int cnt = 0;

		for (int i = ind + 1; i%COLOMS != 0; ++i) {           // right horizontal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		for (int i = ind - 1; i%COLOMS != COLOMS - 1; --i) {   // left horizontal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		if (cnt >= 3)
			return true;
		cnt = 0;

		for (int i = ind + COLOMS; i < board_size; i += COLOMS) {   // up
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		for (int i = ind - COLOMS; i >= 0; i -= COLOMS) {     // down
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		if (cnt >= 3)
			return true;
		cnt = 0;

		for (int i = ind + COLOMS + 1; i < board_size && i%COLOMS != 0; i += COLOMS + 1) {   // up right diagonal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}

		for (int i = ind - COLOMS - 1; i >= 0 && i%COLOMS != COLOMS - 1; i -= COLOMS + 1) {    // down left diagonal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		if (cnt >= 3)
			return true;
		cnt = 0;

		for (int i = ind - COLOMS + 1; i >= 0 && i%COLOMS != 0; i -= COLOMS - 1) {     // down right diagonal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}

		for (int i = ind + COLOMS - 1; i < board_size && i%COLOMS != COLOMS - 1; i += COLOMS - 1) {   // up left diagonal
			if (board[i] == type_pl)
				++cnt;
			else
				break;
		}
		if (cnt >= 3)
			return true;
		cnt = 0;
	}


public:

    void undo_move(bool our_move,char colom){  //  отменяет ход(меняет доску в обратное от хода положение) по сути просто убирает верхнюю фишку в строке
		int i;
		for (i = ROWS - 1; i >= 0; --i) {
			if (board[i * COLOMS + colom] != NONE)
				break;
		}
		board[i * COLOMS + colom] = NONE;
	}   
    void print_board(){} // КРАСИВО печатает доску на консоль


};

class state{
public:
    int depth;
    int alpha;
    bool alpha_set;
    int beta;
    bool beta_set;
    bool player_type;

    state(){
        depth = 0;
        alpha_set = false;
        beta_set = false;
        player_type = false;
    }
    state(int d,bool p,bool as,bool bs){
        depth = d;
        player_type = p;
        alpha_set =as;
        beta_set = bs;
    }


};



int main()
{

    return 0;
}
