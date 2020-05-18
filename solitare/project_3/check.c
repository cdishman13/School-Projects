#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Want to ignore all white space and comments until we see RULES:
//Headers are "RULES:", "FOUNDATIONS:", "TABLEAU:", "STOCK:", "MOVES:"

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
			p[0] = convert(p[0]);
			c[0] = convert(c[0]);
			int k = p[0] - c[0];
			if(k == 1)
				return 1;
			else
				return 0;
		}
	else{
		return 0;
	}
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
		fprintf(stderr, "Error near line %d: expecting 'FOUNDATIONS'\n", line);
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
		fprintf(stderr, "Error near line %d: expecting 'TABLEAU'\n", line);
		return 0;
	}
	consumeWS(inf);
	
	for(int i = 0; i < 7; i++){
		consumeWS(inf);
		char prev[3] = {' ', ' ', 0};
		char curr[3] = {' ', ' ', 0};
		//For loop for covered cards
		for(;;){
			c = fgetc(inf);
			if(c == '|') break;
			if(c == ' ') continue;
			if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
				c = fgetc(inf);
				if(c == 'c' || c == 'd' || c == 'h' || c == 's')
					covered++;
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
				c = fgetc(inf);
				if(c == 'c' || c == 'd' || c == 'h' || c == 's'){
					curr[1] = c;
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
	char sch[7];
	strcpy(sch, "STOCK:");
	if(compareword(7, sch, inf) == 0){
		fprintf(stderr, "Error near line %d: expecting 'STOCK'.\n", line);
		return 0;
	}
	
	consumeWS(inf);	
	//Waste cards
	for(;;){
		c = fgetc(inf);
		if(c == '|') break;
		if(c == ' ') continue;
		if((c >= 50 && c <= 57) || c == 'A' || c == 'T' || c == 'J' || c == 'Q' || c == 'K'){
			c = fgetc(inf);
			if(c == 'c' || c == 'd' || c == 'h' || c == 's')
				waste++;
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
			c = fgetc(inf);
			if(c == 'c' || c == 'd' || c == 'h' || c == 's')
				stock++;
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
void movecheck(FILE* inf){
	//TODO part 2
	return;
}



int main(int argc, char **argv){
	int c, covered, stock, waste;
	
	//File name should be the first and only argument
	FILE* f;
	if(argc == 2){
		f = fopen(argv[1], "r");
	}
	else
		f = stdin;
	
	
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
	if(c == 'M'){
		ungetc(c, f);
		movecheck(f);
	}
	//End the program
	printf("Input file is valid\n");
	printf("%d covered cards\n", covered);
	printf("%d stock cards\n", stock);
	printf("%d waste cards\n", waste);
		
	return 0;
}
