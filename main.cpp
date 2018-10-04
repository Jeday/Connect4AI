#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <stdexcept>


#define ROWS 6
#define COLOMS 7
#define AI 1
#define HUMAN -1
#define NONE 0
#define DEPTH 6

#define UPRIGHT 1
#define UPLEFT 2
#define UP 3
#define RIGHT 4

const int board_size = ROWS * COLOMS;

class game{
private:
    int count_win_lines_AI =0;
    int count_win_lines_HUMAN = 0;
    void work_line(int i,int j,signed char TYPE){
        int coords = i*COLOMS+j;
        int HUM = 0;
        int CPU = 0;

            for(i = 0; i<4;i++){
               if(board[coords] == HUMAN)
                   HUM++;
               else if(board[coords] == AI)
                   CPU++;


               switch (TYPE) {
               case UPRIGHT:
                    coords+=COLOMS+1;
                   break;
               case UPLEFT:
                   coords+=COLOMS-1;
                   break;
               case UP:
                   coords+=COLOMS;
                   break;
               default:
               case RIGHT:
                   coords+=1;
                   break;
               }
            }
            if(HUM != 0 && CPU == 0)
                    count_win_lines_HUMAN++;
            else if(HUM == 0 && CPU != 0)
                count_win_lines_AI++;

    }
public:

    std::vector<signed char> board;



	game() {
		board.resize(board_size, NONE);
	}

    bool validate_move(signed char colom){    // проверяет что можно совершить ход в  colom, т.е. столбец не переполнен
		return (board[board_size - COLOMS + colom] == NONE);
	} 

    int calculate_heuristics(){// высчитывает эвристику для текущего располжения доски
         count_win_lines_AI =0;
         count_win_lines_HUMAN = 0;

        for(int i=0;i<=ROWS-4;i++)
            for(int j=0;j<=COLOMS -4;j++)
                work_line(i,j,UPRIGHT);


        for(int i=0;i<=ROWS-4;i++)
            for(int j=COLOMS-4;j<=COLOMS-1;j++)
                work_line(i,j,UPLEFT);

        for(int i=0;i<=ROWS-4;i++)
            for(int j=0;j<=COLOMS-1;j++)
                work_line(i,j,UP);

        for(int i=0;i<=ROWS-1;i++)
            for(int j=0;j<=COLOMS-4;j++)
                work_line(i,j,RIGHT);

        return  count_win_lines_AI- count_win_lines_HUMAN;

    }

    signed char do_move(bool our_move,signed char colom){   // применяет ход(меняет доску) для нас(our_move == true) или для противника, возвращает AI(выграли мы),HUMAN(выграл Пучкин),NONE(не выигрышный ход)
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

        return false;
	}


public:

    void undo_move(signed char colom){  //  отменяет ход(меняет доску в обратное от хода положение) по сути просто убирает верхнюю фишку в строке
		int i;
		for (i = ROWS - 1; i >= 0; --i) {
			if (board[i * COLOMS + colom] != NONE)
				break;
		}
		board[i * COLOMS + colom] = NONE;
	}   
    void print_board(){
        for(int i = ROWS-1; i>=0;--i){
            for(int j = 0; j<COLOMS; ++j){
                char c;
                switch ( board[i*COLOMS+j]) {
                default:
                case NONE:
                     c = ' ';
                    break;
                case HUMAN:
                     c = 'X';
                    break;
                case AI:
                     c = 'O';
                    break;
                }
                std::cout<<"|"<<c<<"|";
            }
           std::cout<<std::endl;

        }
        for(int j = 0; j<COLOMS; ++j)
            std::cout<<"|"<<j+1<<"|";
        std::cout<<std::endl;
    } // КРАСИВО печатает доску на консоль
};

game * Connect4;



int alphabeta(int depth, int alpha, int beta, bool our_move) {
	if (depth == 0)
		return Connect4->calculate_heuristics();

	int value;
	if (our_move)
	{
		value = INT_MIN;

        for (signed char  i = 0; i < COLOMS ; ++i) {
			if (!Connect4->validate_move(i))
				continue;

			if (Connect4->do_move(true, i) == AI)
                value = std::max(value,Connect4->calculate_heuristics());
			else 
				value = std::max(value, alphabeta(depth - 1, alpha, beta, false));

				Connect4->undo_move(i);
				alpha = std::max(alpha, value);
                if (alpha >= beta)
                    break;
		}
			return value;
	}
	else {
		value = INT_MAX;

        for (signed char i = 0; i < COLOMS; ++i) {
			if (!Connect4->validate_move(i))
				continue;

			if (Connect4->do_move(false, i) == HUMAN)
                value = std::min(value, Connect4->calculate_heuristics());
			else
                value = std::min(value, alphabeta(depth - 1, alpha, beta, true));

			Connect4->undo_move(i);
			beta = std::min(beta, value);
            if (alpha >= beta)
                break;
		}
		return value;
	}
}

signed char calculate_move() {
	int value = INT_MIN;
	int alpha = INT_MIN;
	int beta = INT_MAX;
    signed char  move = -1;

    for (signed char i = 0; i < COLOMS; ++i) {
		if (!Connect4->validate_move(i))
			continue;

		if (Connect4->do_move(true, i) == AI) {
			Connect4->undo_move(i);
			return i;
		}
		else {
			int r = alphabeta(DEPTH, alpha, beta, false);
			if (r  >= value) {
				value = r;
				move = i;
			}
		}

		Connect4->undo_move(i);
		alpha = std::max(alpha, value);
        if (alpha >= beta)
			break;
	}
	return move;
}

void game_cycle(){

  while(true){
    bool is_valid = false;
    for(signed char i = 0; i<COLOMS; i++)
        is_valid = is_valid || Connect4->validate_move(i);
    if(!is_valid){
        std::cout<<"IT'S A DRAW"<<std::endl;
        break;
    }

    int move;
    while(true){
        Connect4->print_board();
        std::cout<<"Enter your move:"<<std::endl;
        std::string s;
        std::cin >> s;
        try{
            move = std::stoi(s);
            if(move < 1 || move >COLOMS || !Connect4->validate_move((signed char)(move-1)))
                throw std::invalid_argument("invalid move");
             break;
        }
        catch(std::logic_error){
            std::cout<<"invalid input"<<std::endl;
            continue;
        }
    }
    signed char colom = (signed char)move -1 ;
    if( Connect4->do_move(false,colom) == HUMAN){
        Connect4->print_board();
        std::cout<<"HUMAN WON"<<std::endl;
        break;
    }
    Connect4->print_board();

    colom = calculate_move();
    if(colom == -1){
        std::cout<<"IT'S A DRAW"<<std::endl;
        break;
    }
    if( Connect4->do_move(true,colom) == AI){
        Connect4->print_board();
        std::cout<<"AI WON HAHAHAH"<<std::endl;
        break;
    }


  }
}

int main()
{
    Connect4 = new game();
    game_cycle();
    return 0;
}
