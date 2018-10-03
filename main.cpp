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


    bool validate_move(int colom){} // проверяет что можно совершить ход в  colom, т.е. столбец не переполнен
    int calculate_heuristics(){} // высчитывает эвристику для текущего располжения доски
    signed char do_move(bool our_move,char colom){} // применяет ход(меняет доску) для нас(our_move == true) или для пртивника, возвращает AI(выграли мы),HUMAN(выграл Пучкин),NONE(не выигрщный ход)
    void undo_move(bool our_move,char colom){}   //  отменят ход(меняет доску в обртное от хода положение) по сути просто убирает верхнюю фишку в строке
    void print_board(){} // КРАСИВО печатает доску на консоль

    game(){
        board.resize(board_size,NONE);

    }

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
