#include <ncurses.h>
#include <ctime>
#include <cstdlib>

const int max = 6;

char table[max][max];

const int cpos[4][2] = {
    {0,5},
    {0,6},
    {1,5},
    {1,6}
};

int pos[4][2] = {
    {0,5},
    {0,6},
    {1,5},
    {1,6}
};

int prev_pos[4][2] = {
    {0,7},
    {0,8},
    {1,7},
    {1,8}
};

void add_figure(){

    for(int i =0; i<4; i++)
        for(int j = 0; j<2; j++){
            pos[i][j]=cpos[i][j];
            prev_pos[i][j]=cpos[i][j];
        }


    //for(int i = 0; i<4; i++){       //Добавление фигуры
    //    table[pos[i][0]][pos[i][1]] = '#';
    //}
}

void write_figure(){
    for(int i = 0; i<4; i++){
        table[pos[i][0]][pos[i][1]] = '#';
    }
}

int main()
{
    for(int i = 0; i<max-1; i++){      //Инициализация таблицы
        for(int j = 0; j<max; j++){              //max
            table[i][j] = ' ';
        }
    }
    for(int i = 0; i<max; i++){
        table[max-1][i] ='*';
    }

    for(int i = 0; i<4; i++){       //Добавление фигуры
        table[pos[i][0]][pos[i][1]] = '#';
    }

    initscr();
    curs_set(0);
    keypad(stdscr, true);
    halfdelay(4);

    time_t secnds = time(NULL);

    while ( true )
    {
        clear();
        for(int i = 0; i<max; i++){      //печать стола
            for(int j = 0; j<max; j++){              //max
                printw("%c", table[i][j]);
            }
            printw("\n");
        }
        refresh();

        //Получаем нажатие пользователя
        switch ( getch() )
        {
            case KEY_RIGHT:
                if (pos[0][1] < max-1 && pos[1][1] < max-1){
                    for(int i =0; i<4; i++){
                        for(int j =0; j<2; j++){
                            prev_pos[i][j] = pos[i][j];
                        }
                    }
                    for(int i = 0; i<4; i++){
                        pos[i][1]+=1;
                    }
                }
                break;
            case KEY_LEFT:
                if (pos[0][1] > 0 && pos[1][1] > 0){
                    for(int i =0; i<4; i++){
                        for(int j =0; j<2; j++){
                            prev_pos[i][j] = pos[i][j];
                        }
                    }
                    for(int i = 0; i<4; i++){
                        pos[i][1]-=1;
                    }
                }
                break;
            case ERR:
                for(int i =0; i<4; i++){
                    for(int j =0; j<2; j++){
                        prev_pos[i][j] = pos[i][j];
                    }
                }
                break;
        }


        for(int i = 0; i<4; i++){       //очистка от старого положения
            table[prev_pos[i][0]][prev_pos[i][1]] = ' ';
        }

        if(secnds < time(NULL)){
            secnds = time(NULL);
            if(table[pos[2][0]+1][pos[2][1]] ==' ' && table[pos[3][0]+1][pos[3][1]]==' ' ){
                for(int i = 0; i<4; i++){
                    pos[i][0]+=1;
                }
            } else {
                write_figure();
                add_figure();
            }
        }

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

        write_figure();


    }//конец while(true)

    endwin();
    return 0;
}
