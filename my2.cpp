#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>
using namespace std;

int player;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

int getUpX(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(board[i][j] !=EMPTY){
                return max(i - 1, 0);
            }
        }
    }
    return 7;
}

int getDownX(){
    for(int i = 14; i >= 0; i--){
        for(int j = 0; j < 15; j++){
            if(board[i][j] != EMPTY){
                return min(i + 1, 14);
            }
        }
    }
    return 7;
}

int getLeftY(){
    for(int j = 0; j <= 14; j++){
        for(int i = 0; i <= 14; i++){
            if(board[i][j] != EMPTY){
                return max(j - 1, 0);
            }
        }
    }
    return 7;
}

int getRightY(){
    for(int j = 14; j >= 0; j--){
        for(int i = 0; i <= 14; i++){
            if(board[i][j] != EMPTY){
                return min(j + 1, 14);
            }
        }
    }
    return 7;
}

bool isfringe( int x, int y){
    int up = max(0, x - 1), down = min(14, x + 1);
    int left = max(0, y - 1), right = min(14, y + 1);
    for(int i = up; i <= down; i++){
        for(int j = left; j <= right; j++){
            if(board[i][j] != EMPTY){
                return false;
            }
        }
    }
    return true;
}

// bool NineBlocksEmpty () {
//     for (int i=6; i<=8; i++) {
//         for (int j=6; j<=8; j++) {
//             if ( board[i][j] != EMPTY ) return false;  
//         }
//     }
//     return true;
// }

// bool CentralEmpty () {
//     return ( board[7][7] == EMPTY )  ?  true : false;
// }

int shapescore ( int  consecutive, int openEnds, int targetplayer ) {
    if ( openEnds == 0 && consecutive < 5 ) return 0;
    switch ( consecutive ) {
        case 4:
            switch ( openEnds ) {
                case 1:
                    if (targetplayer == player) return 100000000;
					return 1000000000;
				case 2:
					if (targetplayer == player) return 100000000;
					return 1000000000;
			}
		case 3:
			switch ( openEnds ) {
				case 1:
					if (targetplayer == player) return 7;
					return 1000;
				case 2:
					if (targetplayer == player) return 10000;
					return 20000;
			}
		case 2:
			switch ( openEnds ) {
				case 1:
					return 2;
				case 2:
					return 5;
			}
		case 1:
			switch ( openEnds ) {
				case 1:
					return 0.5;
				case 2:
					return 1;
			}
		default:
			return 9999999999;
	}
}

//增加棋子算，算完再移除
int HorizontalAnalyzeSets ( int targetplayer ) {
    int score = 0;
    int countConsecutive = 0;
    int openEnds = 0;
    for ( int i=0; i < SIZE ; i++ ) {
        for ( int j=0; j < SIZE ; j++ ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }		
	}
	return score;
}

int VerticalAnalyzeSets ( int targetplayer ) {
    int score = 0;
    int countConsecutive = 0;
    int openEnds = 0;
    for ( int j=0; j < SIZE ; j++ ) {
        for ( int i=0; i < SIZE ; i++ ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }		
	}
	return score;
}

int RightDiagonalAnalyzeSets ( int targetplayer ) {
    int score = 0;
    int countConsecutive = 0;
    int openEnds = 0;
    for ( int m = SIZE-1; m>=0; m-- ) {
        for ( int i = 0, j = m; i<=SIZE-1-m && j<=SIZE-1; i++, j++ ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }		
	}
    for ( int m = 1; m<=SIZE-1; m++ ) {
        for ( int i = m, j = 0; i<=SIZE-1 && j<=SIZE-1-m; i++, j++ ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }
        		
	}
	return score;
}

int LeftDiagonalAnalyzeSets ( int targetplayer ) {
    int score = 0;
    int countConsecutive = 0;
    int openEnds = 0;
    for ( int m = 0; m<=SIZE-1; m++ ) {
        for ( int i = 0, j = m; i<=m && j>=0; i++,j-- ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }		
	}
    for ( int m = 1; m<=SIZE-1; m++ ) {
        for ( int i = m, j = SIZE-1; i<=SIZE-1 && j>=m; i++,j-- ) {
            if ( board[i][j] == targetplayer ) {
                countConsecutive++;
            }
            else if ( board[i][j] == EMPTY && countConsecutive >0)  {
                openEnds++;
                score += shapescore( countConsecutive, openEnds, targetplayer);
                countConsecutive = 0;
                openEnds = 1;
            }
            else if (board[i][j] == EMPTY )
				openEnds = 1;
			else if (countConsecutive > 0) {
				score += shapescore( countConsecutive, openEnds, targetplayer );
				countConsecutive = 0;
				openEnds = 0;
			}
			else openEnds = 0;
		}
		if (countConsecutive > 0) {
            score += shapescore( countConsecutive, openEnds, targetplayer );
		    countConsecutive = 0;
		    openEnds = 0;
        }
        		
	}
	return score;
}

// int minimax ( NewPoint node, int depth, int maximizingPlayer ) {
//     if ( depth = 0 ) {
//         return ;
//     }
//     if ( maximizingPlayer ) {

//     }
//     else {

//     }
// }



//這裡要改寫，策略
void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    // Keep updating the output until getting killed.
    int upX = getUpX();
    int downX = getDownX();
    int leftY = getLeftY();
    int rightY = getRightY();
    int max_value = 0;
    int cur_value = 0;
    int final_x = 7, final_y = 7;
    
    for(int i = upX; i <= downX; i++){
        for(int j = leftY; j <= rightY; j++){
            if(board[i][j] == EMPTY){
                // NewPoint next(i, j, player);
                // next.value = state_value(next);
                if(!isfringe( i, j)){
                    board[i][j] = player;
                    cur_value = HorizontalAnalyzeSets (player) +
                                VerticalAnalyzeSets (player) +
                                RightDiagonalAnalyzeSets (player) +
                                LeftDiagonalAnalyzeSets (player) -
                                HorizontalAnalyzeSets (3-player) -
                                VerticalAnalyzeSets (3-player) -
                                RightDiagonalAnalyzeSets (3-player) -
                                LeftDiagonalAnalyzeSets (3-player);
                    if( cur_value > max_value ){
                        max_value = cur_value;
                        final_x = i;
                        final_y = j;
                    }
                    board[i][j] = EMPTY;
                }
            }
        }
    }
    cout << " max value : " <<max_value << '\n';

    while(true) {
        int x = final_x;
        int y = final_y;
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
        
    }
 }

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
