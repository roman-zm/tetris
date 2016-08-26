#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <vector>

const int max = 18;

char table[max][max];

const int cpos[4][2] = {
    {0,max/2},
    {1,max/2-1},
    {1,max/2},
    {1,max/2+1}
};

const int opos[4][2] = {
    {0,max/2-1},
    {0,max/2},
    {1,max/2-1},
    {1,max/2}
};

const int upos[4][2] = {
    {0,max/2},
    {1,max/2},
    {2,max/2},
    {3,max/2}
};

int pos[4][2], prev_pos[4][2];
std::vector<int> right_blocks, left_blocks, down_blocks;
time_t secnds = time(NULL);


void add_figure(){
    int choice = rand()%3;

    switch (choice) {
    case 0:
        for(int i =0; i<4; i++)
            for(int j = 0; j<2; j++){
                pos[i][j]=cpos[i][j];
                prev_pos[i][j]=cpos[i][j];
            }
        break;
    case 1:
        for(int i =0; i<4; i++)
            for(int j = 0; j<2; j++){
                pos[i][j]=opos[i][j];
                prev_pos[i][j]=opos[i][j];
            }
        break;
    case 2:
        for(int i =0; i<4; i++)
            for(int j = 0; j<2; j++){
                pos[i][j]=upos[i][j];
                prev_pos[i][j]=upos[i][j];
            }
    }


}

void write_figure(){
    for(int i = 0; i<4; i++){
        table[pos[i][0]][pos[i][1]] = '#';
    }
}

void erase_figure(){
    for(int i = 0; i<4; i++){       //очистка от старого положения
        table[prev_pos[i][0]][prev_pos[i][1]] = ' ';
    }
}

void erase_line(){
    for(int i = 0; i<max-1; i++){
        bool de = true;
        for(int j = 0; j<max; j++){
            if(table[i][j] != '#') de = false;
        }
        if(de){
            for(int j = i; j>0; j--){
                for(int l = 0; l<max; l++){
                    table[j][l] = table[j-1][l];
                }
            }
            for(int j = 0; j<max; j++){
                table[0][j] = ' ';
            }
        }
    }
}

void init_table(){
    for(int i = 0; i<max-1; i++){      //Инициализация таблицы
        for(int j = 0; j<max; j++){              //max
            table[i][j] = ' ';
        }
    }
    for(int i = 0; i<max; i++){
        table[max-1][i] ='*';
    }
}

void print_table(){
    for(int i = 0; i<max; i++){      //печать стола
        for(int j = 0; j<max; j++){              //max
            printw("%c", table[i][j]);
        }
        printw("\n");
    }
    refresh();
}

bool is_free_right(){
    bool free = true;
    for(size_t i=0; i<right_blocks.size(); i++){
        if(table[pos[right_blocks[i]][0]][pos[right_blocks[i]][1]+1] != ' ') free = false;
        if(pos[right_blocks[i]][1] >= max-1) free = false;
    }
    return free;
}

bool is_free_left(){
    bool free = true;
    for(size_t i=0; i<left_blocks.size(); i++){
        if(table[pos[left_blocks[i]][0]][pos[left_blocks[i]][1]-1] != ' ') free = false;
        if(pos[left_blocks[i]][1] <= 0) free = false;
    }
    return free;
}


void move_right(){
    //if(table[pos[1][0]][pos[1][1]+1] == ' ' && table[pos[3][0]][pos[3][1]+1] == ' ' && pos[1][1] < max-1 && pos[3][1] < max - 1)
    if(is_free_right())
    {
        for(int i =0; i<4; i++){
            for(int j =0; j<2; j++){
                prev_pos[i][j] = pos[i][j];
            }
        }
        for(int i = 0; i<4; i++){
            pos[i][1]+=1;
        }
    } else {
        for(int i =0; i<4; i++){
            for(int j =0; j<2; j++){
                prev_pos[i][j] = pos[i][j];
            }
        }
    }
}

void move_left(){
    if(is_free_left())
    {
        for(int i =0; i<4; i++){
            for(int j =0; j<2; j++){
                prev_pos[i][j] = pos[i][j];
            }
        }
        for(int i = 0; i<4; i++){
            pos[i][1]-=1;
        }
    } else {
        for(int i =0; i<4; i++){
            for(int j =0; j<2; j++){
                prev_pos[i][j] = pos[i][j];
            }
        }
    }
}

bool is_free_down(){
    bool free = true;
    for(size_t i=0; i<down_blocks.size(); i++){
        if(table[pos[down_blocks[i]][0]+1][pos[down_blocks[i]][1]] !=' ') free = false;
    }
    return free;
}

void fall_down(){
    //if(table[pos[2][0]+1][pos[2][1]] ==' ' && table[pos[3][0]+1][pos[3][1]]==' ' )
    if(is_free_down()){
        for(int i =0; i<4; i++){
            for(int j =0; j<2; j++){
                prev_pos[i][j] = pos[i][j];
            }
        }
        //while(table[pos[2][0]+1][pos[2][1]] ==' ' && table[pos[3][0]+1][pos[3][1]]==' ' )
        while(is_free_down()){
            for(int i = 0; i<4; i++){
                pos[i][0]+=1;
            }
        }
    }
}

void move_error(){
    for(int i =0; i<4; i++){
        for(int j =0; j<2; j++){
            prev_pos[i][j] = pos[i][j];
        }
    }
}

void move_down(){
    if(secnds < time(NULL)){
        secnds = time(NULL);
        if(is_free_down()){
            for(int i =0; i<4; i++){
                for(int j =0; j<2; j++){
                    prev_pos[i][j] = pos[i][j];
                }
            }
            for(int i = 0; i<4; i++){
                pos[i][0]+=1;
            }
        } else {
            write_figure();
            add_figure();
        }
    }
}

void analyze_figure(){
    left_blocks.clear();
    right_blocks.clear();
    down_blocks.clear();

    int lmin, rmin, dmin;
    for(int i=0; i<4; i++){         //Левые и правые блоки
        int lminint = max;
        int rminint = 0;
        for(int j=0; j<4; j++){
            if(pos[i][0] == pos[j][0]){
                if(pos[i][1] < pos[j][1] && pos[j][1] > rminint){
                    rmin = j;
                    rminint=pos[j][1];
                }
                if(pos[i][1] > pos[j][1] && pos[j][1] < lminint){
                    lmin = j;
                    lminint=pos[j][1];
                }
                if(pos[i][1] == pos[j][1]){
                    if(pos[j][1] > rminint){
                        rmin = j;
                        rminint=pos[j][1];
                    }
                    if(pos[j][1] <lminint){
                        lmin = j;
                        lminint=pos[j][1];
                    }
                }
            }
        }
        bool insrts = false;
        for(size_t i=0; i<right_blocks.size(); i++)
            if(right_blocks[i]==rmin) insrts = true;
        if(!insrts) right_blocks.push_back(rmin);

        insrts = false;
        for(size_t i=0; i<left_blocks.size(); i++)
            if(left_blocks[i]==lmin) insrts = true;
        if(!insrts) left_blocks.push_back(lmin);


    }

    for(int i=0; i<4; i++){
        int dminint = 0;
        for(int j=0; j<4; j++){
            if(pos[i][1] == pos[j][1]){
                if(pos[i][0] < pos[j][0] && pos[j][0] > dminint){
                    dmin = j;
                    dminint=pos[j][0];
                }
                if(pos[i][0] == pos[j][0]){
                    if(pos[j][0] > dminint){
                        dmin = j;
                        dminint=pos[j][0];
                    }
                }
            }
        }
        bool insrts = false;
        for(size_t i=0; i<down_blocks.size(); i++)
            if(down_blocks[i]==dmin) insrts = true;
        if(!insrts) down_blocks.push_back(dmin);
    }
}

int main(){
    init_table();
    add_figure();
    analyze_figure();
    write_figure();

    initscr();
    curs_set(0);
    keypad(stdscr, true);
    halfdelay(4);

    while ( true )
    {
        clear();
        print_table();

        switch ( getch() )
        {
            case KEY_RIGHT:
                move_right();
                break;
            case KEY_LEFT:
                move_left();
                break;
            case KEY_DOWN:
                fall_down();
                break;
            case ERR:
                move_error();
                break;
        }

        erase_figure();
        move_down();
        erase_line();
        analyze_figure();
        write_figure();

    }//конец while(true)

    endwin();
    return 0;
}
