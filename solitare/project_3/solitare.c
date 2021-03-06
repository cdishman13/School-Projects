#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers are "RULES:", "FOUNDATIONS:", "TABLEAU:", "STOCK:", "MOVES:"

//Global Vars

struct table{
	char c7[40];
	char c6[39];
	char c5[36];
	char c4[34];
	char c3[32];
	char c2[30];
	char c1[29];
};

struct stockcards{
	char cards[49];
	int len;
};

struct wastecards{
	char cards[49];
	int len;
};

char fclub = '_';
char fdiamond = '_';
char fheart = '_';
char fspade = '_';
struct table T;
struct stockcards s;
struct wastecards w;

int turns;
char limit;
int moves = 9999;
int line = 1;

char convert(char c);

int compareword(int size, char* str, FILE* inf){
	char check[size];
	fgets(check, size, inf);
	if(strcmp(check, str) == 0)
		return 1;
	else 
		return 0;
}

int validcard(int c){
	if((c >=2 && c <= 9) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K' || '_')
		return 1;
	else 
		return 0;
}

int validatecolumn(char *p, char *c){
	//Check suit 
	if(((p[1] == 'd' || p[1] == 'h') && (c[1] == 's' || c[1] == 'c')) || 
		((p[1] == 's' || p[1] == 'c') && (c[1] == 'd' || c[1] == 'h'))){
			//Good card
			int k = convert(p[0]) - convert(c[0]);
			if(k == 1)
				return 1;
			else
				return 0;
		}
	else if(p[0] == '|' && c[0] == 'K'){
		return 1;
	}
	else
		return 0;
}

char convert(char c){
	switch(c){
		case 'A':
			c = '1';
			break;
		case 'T':
			c = ':';
			break;
		case 'J':
			c = ';';
			break;
		case 'Q':
			c = '<';
			break;
		case 'K':
			c = '=';
			break;
		case '_':
			c = '0';
			break;
		default:
			break;
	}
	return c;
}

void consumeWS(FILE* inf){
  int c;
  
  for (;;) {
    c = fgetc(inf);
    if (' ' == c) continue;
    else if ('\t' == c) continue;
    else if ('\n' == c){ 
		line++;
		continue;
	}
    else if ('\r' == c) continue;
	else if ('#' == c){
		int k=1;
		while(k){
			c = fgetc(inf);
			if('\n' == c){
				k=0;
				line++;
			}
			else continue;
		}
	}
    else if (EOF == c) return;
    else break;
  }
  ungetc(c, inf);
  return;
}

void initTableCol(int i, int c, int index){
	switch(i){
		case 0:
			T.c7[index] = c;
			break;
		case 1:
			T.c6[index] = c;
			break;
		case 2:
			T.c5[index] = c;
			break;
		case 3:
			T.c4[index] = c;
			break;
		case 4:
			T.c3[index] = c;
			break;
		case 5:
			T.c2[index] = c;
			break;
		case 6:
			T.c1[index] = c;
			break;
		default:
			fprintf(stderr, "Error near line %d.\n", line);
			break;
	}
}

void getSrcCards(int k, char cards[], char move[]){
	int index = 0, i;
	switch(k){
		case '7':
			for(i = 0; i < strlen(T.c7); i++){
				if(T.c7[i] == '|')
					index = i;
			}
			strcpy(move, &T.c7[index+1]);
			cards[0] = T.c7[index + 1];
			cards[1] = T.c7[index + 2];
			break;
		case '6':
			for(i = 0; i < strlen(T.c6); i++){
				if(T.c6[i] == '|')
					index = i;
			}
			strcpy(move, &T.c6[index+1]);
			cards[0] = T.c6[index + 1];
			cards[1] = T.c6[index + 2];
			break;
		case '5':
			for(i = 0; i < strlen(T.c5); i++){
				if(T.c5[i] == '|')
					index = i;
			}
			strcpy(move, &T.c5[index+1]);
			cards[0] = T.c5[index + 1];
			cards[1] = T.c5[index + 2];
			break;
		case '4':
			for(i = 0; i < strlen(T.c4); i++){
				if(T.c4[i] == '|')
					index = i;
			}
			strcpy(move, &T.c4[index+1]);
			cards[0] = T.c4[index + 1];
			cards[1] = T.c4[index + 2];
			break;
		case '3':
			for(i = 0; i < strlen(T.c3); i++){
				if(T.c3[i] == '|')
					index = i;
			}
			strcpy(move, &T.c3[index+1]);
			cards[0] = T.c3[index + 1];
			cards[1] = T.c3[index + 2];
			break;
		case '2':
			for(i = 0; i < strlen(T.c2); i++){
				if(T.c2[i] == '|')
					index = i;
			}
			strcpy(move, &T.c2[index+1]);
			cards[0] = T.c2[index + 1];
			cards[1] = T.c2[index + 2];
			break;
		case '1':
			for(i = 0; i < strlen(T.c1); i++){
				if(T.c1[i] == '|')
					index = i;
			}
			strcpy(move, &T.c1[index+1]);
			cards[0] = T.c1[index + 1];
			cards[1] = T.c1[index + 2];
			break;
		default:
			fprintf(stderr, "Error near line %d.\n", line);
			break;
	}
	return;
}

void getCards(int i, char cards[]){
	switch(i){
		case '7':
			if(strlen(T.c7) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c7[strlen(T.c7) - 2];
			cards[1] = T.c7[strlen(T.c7) - 1];
			break;
		case '6':
			if(strlen(T.c6) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c6[strlen(T.c6) - 2];
			cards[1] = T.c6[strlen(T.c6) - 1];
			break;
		case '5':
			if(strlen(T.c5) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c5[strlen(T.c5) - 2];
			cards[1] = T.c5[strlen(T.c5) - 1];
			break;
		case '4':
			if(strlen(T.c4) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c4[strlen(T.c4) - 2];
			cards[1] = T.c4[strlen(T.c4) - 1];
			break;
		case '3':
			if(strlen(T.c3) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c3[strlen(T.c3) - 2];
			cards[1] = T.c3[strlen(T.c3) - 1];
			break;
		case '2':
			if(strlen(T.c2) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c2[strlen(T.c2) - 2];
			cards[1] = T.c2[strlen(T.c2) - 1];
			break;
		case '1':
			if(strlen(T.c1) == 1){
				strcpy(cards, "|");
				break;
			}
			cards[0] = T.c1[strlen(T.c1) - 2];
			cards[1] = T.c1[strlen(T.c1) - 1];
			break;
		default:
			fprintf(stderr, "Error near line %d.\n", line);
			break;
	}
}

void addToCol(int i, char cards[]){
	switch(i){
		case '7':
			strcat(T.c7, cards);
			break;
		case '6':
			strcat(T.c6, cards);
			break;
		case '5':
			strcat(T.c5, cards);
			break;
		case '4':
			strcat(T.c4, cards);
			break;
		case '3':
			strcat(T.c3, cards);
			break;
		case '2':
			strcat(T.c2, cards);
			break;
		case '1':
			strcat(T.c1, cards);
			break;
		default:
			fprintf(stderr, "Error near line %d.\n", line);
			break;
	}
}

void movepipe(char cards[]){
	int len = strlen(cards);
	if(len == 1)
		return;
	else{
		cards[len - 1] = cards[len - 2];
		cards[len - 2] = cards[len - 3];
		cards[len - 3] = '|';
	}
	return;
}

void deleteFromCol(int k, int len){
	int i;
	switch(k){
		case '7':
			for(i = 0; i < len; i++)
				T.c7[strlen(T.c7)-1] = 0;
			if(T.c7[strlen(T.c7)-1] == '|')
				movepipe(T.c7);
			break;
		case '6':
			for(i = 0; i < len; i++)
				T.c6[strlen(T.c6)-1] = 0;
			if(T.c6[strlen(T.c6)-1] == '|')
				movepipe(T.c6);
			break;
		case '5':
			for(i = 0; i < len; i++)
				T.c5[strlen(T.c5)-1] = 0;
			if(T.c5[strlen(T.c5)-1] == '|')
				movepipe(T.c5);
			break;
		case '4':
			for(i = 0; i < len; i++)
				T.c4[strlen(T.c4)-1] = 0;
			if(T.c4[strlen(T.c4)-1] == '|')
				movepipe(T.c4);
			break;
		case '3':
			for(i = 0; i < len; i++)
				T.c3[strlen(T.c3)-1] = 0;
			if(T.c3[strlen(T.c3)-1] == '|')
				movepipe(T.c3);
			break;
		case '2':
			for(i = 0; i < len; i++)
				T.c2[strlen(T.c2)-1] = 0;
			if(T.c2[strlen(T.c2)-1] == '|')
				movepipe(T.c2);
			break;
		case '1':
			for(i = 0; i < len; i++)
				T.c1[strlen(T.c1)-1] = 0;
			if(T.c1[strlen(T.c1)-1] == '|')
				movepipe(T.c1);
			break;
		default:
			fprintf(stderr, "Error near line %d.\n", line);
			break;
	}
}

void printBoardDebug(){
	printf("Foundations\n");
	printf("%cc %cd %ch %cs\n", fclub, fdiamond, fheart, fspade);
	printf("Tableau\n");
	printf("Column 1: %s\n", T.c1);
	printf("Column 2: %s\n", T.c2);
	printf("Column 3: %s\n", T.c3);
	printf("Column 4: %s\n", T.c4);
	printf("Column 5: %s\n", T.c5);
	printf("Column 6: %s\n", T.c6);
	printf("Column 7: %s\n", T.c7);
	printf("Stock: %s\n", s.cards);
	printf("Waste: %s\n", w.cards);
	return;
}

char* printHelp(int index, char col[], int c[], int k){
	char *r = malloc(sizeof(char) * 4);
	char p[4] = ".. ";
	if(c[k] == 1 && col[index] != '|'){
		strcpy(r, "## ");
	}
	else if(col[index] == '|'){
		c[k] = 0;
		if(index+1 > strlen(col)-1){
			r[0] = '.';
			r[1] = '.';
			r[2] = ' ';
		}
		else{
			r[0] = col[index+1];
			r[1] = col[index+2];
			r[2] = ' ';
		}
	}
	else{
		if(index+1 > strlen(col)-1){
			r[0] = '.';
			r[1] = '.';
			r[2] = ' ';
		}
		else{
			r[0] = col[index+1];
			r[1] = col[index+2];
			r[2] = ' ';
		}
	}
	//printf("r: %s\n", r);
	return r;
}

void printBoard(){
	int c[7] = {1,1,1,1,1,1,1}; //Is 1 until you see a '|'
	int i, index = 0;
	char p[21];
	*p = '\0';
	char none[21] = ".. .. .. .. .. .. .. ";
	printf("Foundations\n");
	printf("%cc %cd %ch %cs\n", fclub, fdiamond, fheart, fspade);
	printf("Tableau\n");
	
	//Loop to print the columns. Print column 1 first
	while(1){
		strcat(p, printHelp(index, T.c1, c, 0));
		strcat(p, printHelp(index, T.c2, c, 1));
		strcat(p, printHelp(index, T.c3, c, 2));
		strcat(p, printHelp(index, T.c4, c, 3));
		strcat(p, printHelp(index, T.c5, c, 4));
		strcat(p, printHelp(index, T.c6, c, 5));
		strcat(p, printHelp(index, T.c7, c, 6));
		
		if(strcmp(none, p) == 0)
			break;
		else
			printf("%s\n", p);
		//printf("Index: %d\n", index);
		index += 2;
		strcpy(p, "");
	}
	printf("Waste top\n");
	if(w.len == 0)
		printf("(empty)\n");
	else{
		if(turns == '1'){
			printf("%c%c\n", w.cards[w.len-2], w.cards[w.len-1]);
		}
		else{
			int j;
			for(i = 3; i > 0; i--){
				j = w.len - (2*i);
				if(j >= 0)
					printf("%c%c ", w.cards[j], w.cards[j+1]);
			}
			printf("\n");
		}
	}
}

//RULES
//Appears in this order
//"turn 1" or "turn 3"
//"unlimited" or "limit N" where N is the number of times the waste can be reset into the stock
int rulecheck(FILE* inf){
	int c, q, t = -1;
	//Checks to make sure the word RULES: is there 
	char rule[7];
	fgets(rule, 7, inf);
	char rch[7];
	strcpy(rch, "RULES:");
	if(strcmp(rule, rch) != 0){
		fprintf(stderr, "Error near line %d: expecting 'RULES:'\n", line);
		return 0;
	}
	//Check turn
	consumeWS(inf);
	char turn[6];
	char tch[6];
	fgets(turn, 6, inf);
	strcpy(tch, "turn ");
	if(strcmp(turn, tch) == 0){
		c = fgetc(inf);
		if(c == '1' || c == '3'){
			//Means it is good
			turns = c;
		}
		else{
			fprintf(stderr, "Error near line %d: Invalid turn number\n", line);
			return 0;
		}
	}
	else{
		fprintf(stderr, "Error near line %d: expecting 'turn'\n", line);
		return 0;
	}
	//Checks for unlimited or limit N
	consumeWS(inf);
	c = fgetc(inf);
	if(c == 'u'){
		char uch[9];
		strcpy(uch, "nlimited");
		q = compareword(9, uch, inf);
		if(q == 0){
			fprintf(stderr, "Error near line %d: expecting 'unlimited'\n", line);
			return 0;
		}
		limit = 'u';
	}
	else if(c == 'l'){
		char lch[6];
		strcpy(lch, "imit ");
		q = compareword(6, lch, inf);
		if(q == 0){
			fprintf(stderr, "Error near line %d: expecting 'limit'\n", line);
			return 0;
		}
		t = fgetc(inf);
		limit = t;
	}
	else{
		fprintf(stderr, "Error near line %d: Invalid amount of waste turns.\n", line);
		return 0;
	}
	return 1;
}

//FOUNDATIONS
//This is where you want to put all the cards to win
//Indicates the top card in the foundation
//Order is {A,2,3,4,5,6,7,8,9,J,Q,K}
//Suit is {'c','d','h','s'} for club, diamond, heart, spade
//Could have '_' meaning that the formation is empty
//Examples: _c = clubs is empty, 4d = Diamond formation has cards A,2,3,4
int foundationcheck(FILE* inf){
	int c, q;
	char fch[13];
	stpcpy(fch, "FOUNDATIONS:");
	q = compareword(13, fch, inf);
	if(q == 0){
		fprintf(stderr, "Error near line %d: expecting 'FOUNDATIONS:'\n", line);
		return 0;
	}
	
	consumeWS(inf);
	
	//Clubs
	c = fgetc(inf);
	if(validcard(c) == 0){
		fprintf(stderr, "Error near line %d: Not a valid card.\n", line);
		return 0;
	}
	//Valid number for a card, check if it is clubs
	else{
		fclub = c;
		c = fgetc(inf);
		if(c != 'c'){
			fprintf(stderr, "Error near line %d: expecting clubs.\n", line);
			return 0;
		}
	}

	consumeWS(inf);	
	//Diamonds
	c = fgetc(inf);
	if(validcard(c) == 0){
		fprintf(stderr, "Error near line %d: Not a valid card.\n", line);
		return 0;
	}
	//Valid number for a card, check if it is diamond
	else{
		fdiamond = c;
		c = fgetc(inf);
		if(c != 'd'){
			fprintf(stderr, "Error near line %d: expecting diamond.\n", line);
			return 0;
		}
	}
	
	consumeWS(inf);
	//Hearts
	c = fgetc(inf);
	if(validcard(c) == 0){
		fprintf(stderr, "Error near line %d: Not a valid card.\n", line);
		return 0;
	}
	//Valid number for a card, check if it is heart
	else{
		fheart = c;
		c = fgetc(inf);
		if(c != 'h'){
			fprintf(stderr, "Error near line %d: expecting heart.\n", line);
			return 0;
		}
	}
	
	consumeWS(inf);
	//Spades
	c = fgetc(inf);
	if(validcard(c) == 0){
		fprintf(stderr, "Error near line %d: Not a valid card.\n", line);
		return 0;
	}
	//Valid number for a card, check if it is spade
	else{
		fspade = c;
		c = fgetc(inf);
		if(c != 's'){
			fprintf(stderr, "Error near line %d: expecting spade.\n", line);
			return 0;
		}
	}
	return 1;
}

//TABLEAU
//Has seven columns
//Columns are on one line with spaces between cards and | between covered and uncovered cards 
//Example: 4c 5d | 8s 7h 6c --> has two uncovered cards and three covered cards
//Columns are in reverse order with column 7 first then 6 and down to 1
//Blank lines and comment lines may appear between columns
int tablecheck(FILE* inf, int *cov){
	int c, covered = 0, uncovered = 0, t;
	char tch[9];
	stpcpy(tch, "TABLEAU:");
	if(compareword(9, tch, inf) == 0){
		fprintf(stderr, "Error near line %d: expecting 'TABLEAU:'\n", line);
		return 0;
	}
	consumeWS(inf);
	
	for(int i = 0; i < 7; i++){
		consumeWS(inf);
		int index = 0;
		char prev[3] = {' ', ' ', 0};
		char curr[3] = {' ', ' ', 0};
		//For loop for covered cards
		for(;;){
			c = fgetc(inf);
			if(c == '|') break;
			if(c == ' ') continue;
			if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
				initTableCol(i, c, index++);
				c = fgetc(inf);
				if(c == 'c' || c == 'd' || c == 'h' || c == 's'){
					initTableCol(i, c, index++);
					covered++;
				}
				else{
					fprintf(stderr, "Error near line %d: Invalid card.\n", line);
					return 0;
				}
			}
			else{
				fprintf(stderr, "Error near line %d: Invalid column.\n", line);
				return 0;
			}
			
		}
		
		initTableCol(i, c, index++);
		
		//For loop for uncovered cards
		for(;;){			
			c = fgetc(inf);
			//If there is a comment go to next line
			if(c == '#'){
				for(;;){
					c = fgetc(inf);
					if(c == '\n'){
						line++;
						break;
					}
				}
				break;
			}
			if(c == '\n'){
				line++;
				break;
			}
			if(c == ' ') continue;
			if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
				curr[0] = c;
				initTableCol(i, c, index++);
				c = fgetc(inf);
				if(c == 'c' || c == 'd' || c == 'h' || c == 's'){
					curr[1] = c;
					initTableCol(i, c, index++);
					uncovered++;
					if(prev[0] != ' '){
						if(!validatecolumn(prev, curr)){
							fprintf(stderr, "Error near line %d: Invalid column.\n", line);
							return 0;
						}
					}
				}
				else{
					fprintf(stderr, "Error near line %d: Invalid card.\n", line);
					return 0;
				}
			}
			else{
				fprintf(stderr, "Error near line %d: Invalid column.\n", line);
				return 0;
			}
			strcpy(prev, curr);
		}
	}
	
	*cov = covered;
	return 1;
}

//STOCK
//Indicates both the stock and the waste
//Stock cards are the ones covered
//Waste cards are the ones uncovered(Can play the top one of this)
//Waste | Stock
//Last card in waste is the top card
//First card in stock is the top card
//Playing the next card in the stock can be simulated by moving the '|' char to the right
//Blank lines and comment lines may appear between elements
int stockcheck(FILE* inf, int *st, int *wa){
	//NEED TO RETURN BOTH WASTE AND STOCK AMOUNT
	int c, stock = 0, waste = 0;
	s.len = 0;
	w.len = 0;
	char sch[7];
	strcpy(sch, "STOCK:");
	if(compareword(7, sch, inf) == 0){
		fprintf(stderr, "Error near line %d: expecting 'STOCK:'.\n", line);
		return 0;
	}
	
	consumeWS(inf);	
	//Waste cards
	for(;;){
		c = fgetc(inf);
		if(c == '|') break;
		if(c == ' ') continue;
		if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
			w.cards[w.len++] = c;
			c = fgetc(inf);
			if(c == 'c' || c == 'd' || c == 'h' || c == 's'){
				w.cards[w.len++] = c;
				waste++;
			}
			else{
				fprintf(stderr, "Error near line %d: Invalid card.\n", line);
				return 0;
			}
		}
		if(c == '#'){
			for(;;){
				c = fgetc(inf);
				if(c == '\n'){
					line++;
					break;
				}
			}
		}
	}
	
	//Stock cards
	for(;;){
		c = fgetc(inf);
		if(c == 'M') break;
		if(c == ' ') continue;
		if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
			s.cards[s.len++] = c;
			c = fgetc(inf);
			if(c == 'c' || c == 'd' || c == 'h' || c == 's'){
				s.cards[s.len++] = c;
				stock++;
			}
			else{
				fprintf(stderr, "Error near line %d: Invalid card.\n", line);
				return 0;
			}
		}
		if(c == '#'){
			for(;;){
				c = fgetc(inf);
				if(c == '\n'){
					line++;
					break;
				}
			}
		}
	}
	*wa = waste;
	*st = stock;
	return 1;
}

//MOVES
//This will be implemented in part 2
//For now just ignore everything after this
int movecheck(FILE* inf){
	char mch[6] = "OVES:";
	char arrow[3] = "->";
	char src[3] = "0";
	char dest[3] = "0";
	char move[27] = "0";
	int c, q, i, m = 0;
	//Checks for the word MOVE:
	if(compareword(6, mch, inf) == 0){
		fprintf(stderr, "Error near line %d: expecting 'MOVES:'.\n", line);
		return -1;
	}
	
	//Loop until end of file
	//while(m < moves){
	for(m = 0; m < moves; m++){
		consumeWS(inf);
		c = fgetc(inf);
		//If we have reached the end of file break out of loop
		if(c == EOF)
			break;
		//If '.' then cause T cards to be turned over from stock to the waste
		if(c == '.'){
			//Need to check if there are cards in the stock
			if(s.len == 0){
				fprintf(stderr, "Move %d is illegal: %c\n", m, c);
				return -1;
			}
			//If T = 1
			if(turns == '1'){
				for(i = 0; i < 2; i++){
					w.cards[w.len++] = s.cards[0];
					//strcpy(s.cards, &s.cards[1]);
					memmove(s.cards, s.cards+1, s.len);
					s.len--;
				}
			}
			//If T = 3
			else{
				//If there is 2 or 1 cards left in stock
				if(s.len < 3){
					strcat(w.cards, s.cards);
					w.len += s.len;
					s.len = 0;
				}
				else{
					for(i = 0; i < 6; i++){
						w.cards[w.len++] = s.cards[0];
						//strcpy(s.cards, &s.cards[1]);
						memmove(s.cards, s.cards+1, s.len);
						s.len--;
					}
				}				
			}
		}
		//If 'r' then waste pile gets reset to the stock
		else if(c == 'r'){
			if(w.len == 0 || limit == '0'){
				fprintf(stderr, "Move %d is illegal: %c\n", m, c);
				return -1;
			}
			//Implements Limit N
			printf("Limit: %c\n", limit);
			if(limit != 'u')
				limit--;
			strcpy(s.cards, w.cards);
			stpcpy(w.cards, "0");
			s.len = w.len;
			w.len = 0;
		}
		//If 'w' or '1', '2', ..., '7'
		//Look for '->' next
		//Then look for the place to move card
		else if(c == 'w' || (c > '0' && c < '8')){
			q = c;
			if(compareword(3, arrow, inf) == 0){
				fprintf(stderr, "Move %d is illegal: %c->%c\n", m, c,fgetc(inf));
				return -1;
			}
			c = fgetc(inf);
			//Will need to check if valid move 
			//q will be the source and c will be the destination
			//Have three cases
			//1. c = 'f'
			if(c == 'f'){
				//Move the card to foundation. Need to get the suit of the card and check that it can go
				//If src is waste
				if(q == 'w'){
					src[0] = w.cards[w.len - 2];
					src[1] = w.cards[w.len - 1];
					w.cards[w.len - 1]  = 0;
					w.cards[w.len - 2] = 0;
					w.len -= 2;
				}
				//If src is a column
				else{
					getCards(q, src);
					deleteFromCol(q, 2);
				}
				dest[1] = src[1];
				switch(src[1]){
					case 'c':
						dest[0] = fclub;
						break;
					case 'd':
						dest[0] = fdiamond;
						break;
					case 'h':
						dest[0] = fheart;
						break;
					case 's':
						dest[0] = fspade;
						break;
					default:
						break;
				}
				//Checks is the move is valid
				if(convert(src[0]) - convert(dest[0]) == 1){
					//Add card to foundation
					switch(src[1]){
						case 'c':
							fclub = src[0];
							break;
						case 'd':
							fdiamond = src[0];
							break;
						case 'h':
							fheart = src[0];
							break;
						case 's':
							fspade = src[0];
							break;
						default:
							break;
					}
				}
				else{
					fprintf(stderr, "Move %d is illegal: %c->%c\n", m, q, c);
					return -1;
				}
			}
			//2. q = 'w'
			else if(q == 'w'){
				//Take card from top of the waste then need to validate that it can go to column
				getCards(c, dest);
				src[0] = w.cards[w.len - 2];
				src[1] = w.cards[w.len - 1];
				//Checks if the move is valid
				if(validatecolumn(dest, src)){
					//Remove cards from waste pile
					w.cards[w.len - 1]  = 0;
					w.cards[w.len - 2] = 0;
					w.len -= 2;
					//Add cards to column
					addToCol(c, src);
				}
				else{
					fprintf(stderr, "Move %d is illegal: %c->%c\n", m, q, c);
					return -1;
				}
			}
			//3.If both values are columns
			else{
				//Need to put cards in char arrays then use validatecolumn to check if they are valid
				getSrcCards(q, src, move);
				getCards(c, dest);
				//Check if the move is valid
				if(validatecolumn(dest, src)){
					//Add card to column and delete from prev column
					addToCol(c, move);
					deleteFromCol(q, strlen(move));
				}
				else{
					fprintf(stderr, "Move %d is illegal: %c->%c\n", m, q, c);
					return -1;
				}
			}
		}
		//printBoard();
	//	m++;
	}
	
	return m;
}



int main(int argc, char **argv){
	int c, covered, stock, waste, m;
	int i;
	//File name should be the first and only argument
	FILE* f;
	for(i = 0; i < argc; i++){
		if(strcmp("-m", argv[i]) == 0){
			moves = atoi(argv[i+1]);
			break;
		}
	}
	//If there is no -m switch
	if(moves == 9999){
		if(argc == 2)
			f = fopen(argv[1], "r");
		else
			f = stdin;
	}
	//If the is a -m switch
	else{
		if(argc == 3)
			f = stdin;
		else{
			//If ./advance -m N input.txt
			if(i == 1)
				f = fopen(argv[3], "r");
			else
				f = fopen(argv[1], "r");
		}	
	}	
	
	//check for whitespace until the word RULES
	consumeWS(f);
	//Run a function that parses through the RULES section
	c = fgetc(f);
	if(c == 'R'){
		ungetc(c, f);
		if(!rulecheck(f))
			return 0;
	}
	//Check for whitespace until the word Foundations
	consumeWS(f);
	//Run a function that parses through the FOUNDATIONS section
	c = fgetc(f);
	if(c == 'F'){
		ungetc(c, f);
		if(!foundationcheck(f))
			return 0;
	}
	//Check for whitespace until the word TABLEAU
	consumeWS(f);
	//Run a function that parses the TABLEAU section
	c = fgetc(f);
	if(c == 'T'){
		ungetc(c,f);
		if(!tablecheck(f, &covered))
			return 0;
	}
	//Check for whitespace until the word STOCK
	consumeWS(f);
	//Run a function that parses through the Stock section
	c = fgetc(f);
	if(c == 'S'){
		ungetc(c,f);
		if(!stockcheck(f, &stock, &waste))
			return 0;
	}
	//Check for whitespace until the word MOVES
	consumeWS(f);
	c = fgetc(f);
	if(c == 'O'){
		ungetc(c, f);
		m = movecheck(f);
		if(m >= 0)
			printf("Processed %d moves, all valid\n", m);
	}
	printBoard();	
	return 0;
}
