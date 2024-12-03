#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int A[17][17]; //main array

const int maxv=10;

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void printMap(int x, int y) {//function for print game map
	int i, j;
	for(i=0; i<x; i++) {
		for(j=0; j<y; j++)
			printf("%c ", A[i][j]);
		printf("\n");
	}
}

int generate_number() {//randomize road difficulty
	const double probs [9] = {0.65, 0.25, 0.05, 0.05, 0, 0, 0, 0, 0};
	double cdf [9];
	cdf [0] = probs [0];
	for (int i=1; i < 9; ++i) {
		cdf [i] = cdf [i-1] + probs[i];
	}
	double rand_val = (double) rand() / RAND_MAX;
	for (int i=0; i<9; ++i) {
		if (rand_val < cdf[i]) return (char)(i + 1 + '0');
	}
	return -1;
}

int main() {
	int n, i, j;
	int x, y;
	printf("enter x and y for map:");//game map
	scanf("%d %d", &x, &y);
	for(i=0; i<x; i++) {
		for(j=0; j<y; j++) A[i][j] = generate_number();
	}

	int C[2];
	printf("enter number of teriories:");
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		int pi, qi;
		printf("enter location of teriory %d:", i+1);
		scanf("%d %d", &pi, &qi);
		C[0] = pi - 1;
		C[1] = qi - 1;
		A[pi-1][qi-1] = 'C';
	}

	int v;
	printf("enter number of villages:");
	scanf("%d", &v);
	int Vilfood[maxv], Vilgold[maxv], Villxy[maxv][2];
	for(i=0; i<v; i++) {
		int pi, qi;
		printf("enter location of village %d:", i+1);
		scanf("%d %d", &pi, &qi);
		Villxy[i][0] = pi - 1;
		Villxy[i][1] = qi - 1;
		printf("food and gold:");
		scanf("%d %d", &Vilfood[i], &Vilgold[i]);
		A[pi-1][qi-1] = 'V';
	}

	printf("enter number of blocked houses:");
	scanf("%d", &n);
	for(i=0; i<n; i++) {
		int pi, qi;
	    printf("enter location of blocked house %d:", i+1);
		scanf("%d %d", &pi, &qi);
		A[pi-1][qi-1] = 'X';
	}

	clearScreen();

	printMap(x,y);

	printf("do you want to continue To see the roads?\n0 for No\n1 for Yes\n");
	scanf("%d", &i);
	if(i==0) return 0;//finish

	int a, b, Sw = 0;
	for(i=0; i<v; i++) {
		a = C[0];//xR
		b = C[1];//yR
		if(C[0] < Villxy[i][0]) {
			for(a++; a<(Villxy[i][0]-1); a++) {
                if(A[a][b] == 'X'){
                    a--;
                    if(b < Villxy[i][1]) b++;
                    else b--;
                }
				A[a][b]='R';
			}
		}
			else {
				for(a--; a>(Villxy[i][0]+1); a--) {
                    if(A[a][b] == 'X'){
                    a++;
                    if(b<Villxy[i][1]) b++;
                    else b--;
                }
					A[a][b]='R';
				}
			}

        int count = 0;
		if(b < Villxy[i][1]) {
			for(; b<=Villxy[i][1]; b++) {
                if(A[a][b] == 'X'){
                    b--;
                    count++;
                    if(a < Villxy[i][0]) a++;
                    else a--;
                }
                if(A[a][b] == 'V') break;
				A[a][b]='R';
			}
		}
			else {
				for(; b>=Villxy[i][1]; b--) {
                    if(A[a][b] == 'X'){
                    b++;
                    count++;
                    if(a < Villxy[i][0]) a++;
                    else a--;
                    }
                    if(A[a][b] == 'V') break;
					A[a][b]='R';
				}
			}
			for(;count>0;count--){
            if(a < Villxy[i][0]) a++;
            else a--;
            A[a][b];
			}
		}

	printMap(x,y);

	return 0;
}
