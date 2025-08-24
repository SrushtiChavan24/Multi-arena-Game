
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

void guess_the_number();

//human calculator
void Human_calculator();

typedef struct {
    int first;
    int second;
} TwoNum;

double divide(double a, double b);
TwoNum random_num(); 
int calculate(int a, int b, char op); 



//tic tac toe game function and defined variables
#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct {
    int player;
    int computer;
    int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

void tic_tac_toe();


int main(){
    int game_choice;
    while (1)
    {
        printf("\n<<--------------------------------------------------------------->>\n");
        printf("\nWel-Come to the Multi-level Game arena!!\nWe have Games from Basic to Advance. \n");
        printf("1. Guess The Number..\n");
        printf("2. Are you a Human Calculator?? \n");
        printf("3. Tic Tac Toe  \n");
        printf("4. Exist \n");
        printf("You are Choosing (1 to 4): ");
        scanf("%d",&game_choice);
        
        if (game_choice>4||game_choice<0)
        {
            printf("\nError! Invalid Input!! \n");
            continue;
        }
        else if (game_choice==4)
        {
            printf("You are existing the Game\n");
            return 0;
        }
        
        switch (game_choice)
        {
            case 1:
            guess_the_number();
            break;
            case 2:
            Human_calculator();
            break;
            case 3:
            tic_tac_toe();
            break;
            default:
            printf("\nError! Invalid Input!! \n");
            break;
        }
    }
    
    return 0;
}

//guess the number game
void guess_the_number(){
    int randNum,userNum,NO_of_guesses=0;
    
    srand(time(NULL));
    
    printf("\n\nHELLO!! WELCOME TO THE GUESS NUMBER GAME!!\n");
    randNum = rand()%100 + 1; // Random number between 1 and 100
    
    // If rand() returns 57, then 57 % 100 = 57, and 57 + 1 = 58.
    // If rand() returns 129, then 129 % 100 = 29, and 29 + 1 = 30.
    do
    {
        printf("Please Enter your Guess(1 to 100): \n");
        scanf("%d",&userNum);
        
        if (userNum<randNum){
            printf("Guess a greater Number\n");
        }
        else if (userNum>randNum){
            printf("Guess a smaller Number\n");
        }
        else{
            printf("Congratulations!! You guessed the number in %d attempts\n",NO_of_guesses);
        }
        NO_of_guesses++;
        
    } while (userNum != randNum);
    
    printf("Thank you for playing the game\n");
    
};


//human calculator
void Human_calculator(){
    int choice, lives = 3, score = 0;
    char operands[] = {'+', '-', '*', '/'};
    srand(time(NULL)); 

    while(lives > 0) {
        TwoNum num = random_num();
        char op = operands[rand() % 4]; // Random operator
        int answer, user_answer;
        time_t start, end;
        double elapsed;

        printf("\n--------------------------------\n");
        printf("Score: %d | Lives: %d\n", score, lives);
        printf("Calculate: %d %c %d\n", num.first, op, num.second);
        
        answer = calculate(num.first, num.second, op);
        
        printf("You have 10 seconds!\n");
        time(&start);
        printf("Your answer: ");
        scanf("%d", &user_answer);
        time(&end);
        
        elapsed = difftime(end, start);
        
        if(elapsed > 10) {
            printf("Time's up! Correct answer was %d\n", answer);
            lives--;
        } else if(user_answer == answer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! Correct answer was %d\n", answer);
            lives--;
        }
      if(lives == 0) {
        printf("\nGame over! Final score: %d\n", score);
         printf("\nContinue? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        if(choice == 0) {
            printf("Final score: %d\n", score);
            break;
        }
    }  
       
    }
};

double divide(double a, double b) {
    if(b == 0) {
        printf("Division by zero error!\n");
        return NAN;
    }
    return a / b;
}

TwoNum random_num() {
    TwoNum nums;
    nums.first = rand() % 50 + 1;
    nums.second = rand() % 50 + 1;
    return nums;
}

int calculate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b; // Integer division for simplicity
        default: return 0;
    }
}

//tic tac toe
void tic_tac_toe(){
    srand(time(NULL));
  int choice;
  
  do {
    play_game();
    printf("\nPlay again? (1 for yes, 0 for no): ");
    scanf("%d", &choice);
  } while (choice == 1);
  printf("\nBye Bye, thanks for playing.");
};

void play_game() {
  char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };


  char current_player = rand() % 2 == 0 ? X : O;

  print_board(board);
  while (1) {
    if (current_player == X) {
      player_move(board);
      print_board(board);
      if (check_win(board, X)) {
        score.player++;
        print_board(board);
        printf("Congratulation You have won.!!!");
        break;
      }
      current_player = O;
    } else {
      computer_move(board);
      print_board(board);
      if (check_win(board, O)) {
        score.computer++;
        print_board(board);
        printf("I won !!! But you played well...");
        break;
      }
      current_player = X;
    }

    if (check_draw(board)) {
      score.draw++;
      print_board(board);
      printf("\nIt's a draw!");
      break;
    }
  }
}

int is_invalid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
  return (row < 0 || col < 0 ||
           row > 2 || col > 2 ||
           board[row][col] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  int count = 0, x, y;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        count++;
        x = i;
        y = j;
      }
    }
  }

  if (count == 1) {
    board[x][y] = X;
    return;
  }
  
  int row, col;
  do {
    printf("\nPlayer X's turn.");
    printf("\nEnter row and column (1-3) for X: ");
    scanf("%d", &row);
    scanf("%d", &col);
    row--; col--; // converting to zero based
  } while (is_invalid_move(board, row, col));
  board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
  //  Play for Immediate win
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        if (check_win(board, O)) {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  //  Play for Immediate Block
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = X;
        if (check_win(board, X)) {
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }  

  //  Play first available move
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = O;
        return;
      }
    }
  }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return 1;
    }

    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return 1;
    }
  }

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
    return 1;
  }
  return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == ' ') {
        return 0;
      }
    }
  }
  return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
  clear_screen();
  printf("Score - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
  printf("\nTic-Tac-Toe\n");

  for (int i = 0 ; i < BOARD_SIZE; i++) {
    printf("\n");
    for (int j = 0; j < BOARD_SIZE; j++) {
      printf(" %c ", board[i][j]);
      if (j < BOARD_SIZE - 1) {
        printf("|");
      }
    }
    if (i < BOARD_SIZE - 1) {
      printf("\n---+---+---");
    }
  }
  printf("\n\n");
}


void clear_screen() {
  #ifdef _Win32
    system("cls");
  #else
    system("clear");
  #endif    
}