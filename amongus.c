#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
char *list[11] = {"Red", "Blue", "Yellow", "Green", "Purple", "Pink", "White", "Black", "Brown", "Orange"}, copy[100];
int total = 0, crew = 0, imp = 0;

struct object{
	char color[10];
	int role, life;
}character[11];

void play(int yes);
void createObject(int yes);
void meet(int crew, int imp, int total, struct object *character);

int main(){
	srand(time(0));
	int yes = 1;
	play(yes);
	printf("                  Thanks for playing\n");
    return 0;
}

void play(int yes){
	while(yes){
		int i;
		printf("	                    Among Us\n");
		createObject(yes);
		int cont = 1, round = 0;
		while(cont){
			if(imp == 0){
				Sleep(500);
				printf("\nCREWMATE WINS\n\n");
				cont = 0;
			}
			else if(crew <= imp){
				Sleep(500);
				printf("\nIMPOSTOR WINS\n\n");
				cont = 0;
			}
			else{
				printf("\n                          ROUND %d\n", ++round);
				Sleep(500);
				int emer = rand() % 5;
				if(emer == 1 || emer == 3){
					int clicked;
					do{
						clicked = rand() % total;
					}while(character[clicked].life == 2);
					printf("EMERGENCY MEETING!\n");
					Sleep(500);
					meet(crew, imp, total, character);
				}
				else{
					int killed;
					do{
						killed = rand() % total;
					}while(character[killed].role == 1 && character[killed].life == 2);
					printf("%s was killed by the impostor.\n\n", character[killed].color);
					Sleep(500);
					crew--;
					character[killed].life = 2;
					if(imp == 0 || imp >= crew){
						continue;
					}
					printf("VOTING TIME!\n");
					Sleep(500);
					meet(crew, imp, total, character);
				}
			}
		}
		printf("Would you like to play once more? (1 = Yes ### 0 = No): ");
		scanf("%d", &yes);
		if(yes){
			printf("\n\n");
		}
	}
	return;
}

void createObject(int yes){
	total = 0, crew = 0, imp = 0;
	int g;
	while(total < 4 || total > 10){
		printf("How many players? (between 4 and 10): ");
		scanf("%d", &total);
		if(total < 4){
			strcpy(copy, "Invite more players\n");
			for(g = 0; copy[g] != '\0'; g++){
				printf("%c", copy[g]);
				Sleep(30);
			}
			Sleep(500);
		}
		else if(total > 10){
			strcpy(copy, "Too many players\n");
			for(g = 0; copy[g] != '\0'; g++){
				printf("%c", copy[g]);
				Sleep(30);
			}
			Sleep(500);
		}
	}
	while(imp < 1 || imp > 3){
	    printf("How many impostors? (between 1 and 3): ");
	    scanf("%d", &imp);
	   	if(imp < 1){
	    	strcpy(copy, "Add more impostors\n");
			for(g = 0; copy[g] != '\0'; g++){
			printf("%c", copy[g]);
				Sleep(30);
			}
			Sleep(500);
		}
		else if(imp > 3){
			strcpy(copy, "Too many impostors\n");
			for(g = 0; copy[g] != '\0'; g++){
				printf("%c", copy[g]);
				Sleep(30);
			}
			Sleep(500);
		}
	}
	int j;
	crew = total - imp;
	int i = 0, z;
	while(i < imp){
		z = rand() % total;
		if(character[z].role == 0){
			character[z].role = 1;
			i++;
		}
	}
	for(i = 0; i < total; i++){
		strcpy(character[i].color, list[i]);
		character[i].life = 1;
	}
	return;
}

void meet(int crew, int imp, int total, struct object *character){
	int i;
	char copy[200];
	int a = rand() % 3;
	if(a == 1 || a == 2){
		int voted;
		do{
			voted = rand() % total;
		}while(character[voted].life == 2);
		printf("%s was the most voted.\n", character[voted].color);
		if(character[voted].role == 0){
			strcpy(copy, "He is not an impostor.");
			for(i = 0; copy[i] != '\0'; i++){
				printf("%c", copy[i]);
				Sleep(50);
			}
			Sleep(500);
			crew--;
			printf("\n%d impostor(s) and %d crewmate(s) remain.\n", imp, crew);
			character[voted].life = 2;
			return;
		}
		else{
			strcpy(copy, "He is an impostor.");
			for(i = 0; copy[i] != '\0'; i++){
				printf("%c", copy[i]);
				Sleep(50);
			}
			Sleep (500);
			imp--;
			printf("\n%d impostor(s) and %d crewmate(s) remain.\n", imp, crew);
			character[voted].life = 2;
			return;
		}
	}
	else{
		printf("No one was ejected\n");
		printf("%d impostor(s) and %d crewmate(s) remain.\n", imp, crew);
		return;
	}
}
