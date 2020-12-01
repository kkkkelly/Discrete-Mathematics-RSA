
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define BASE 1000
#define N 50
void make_int (int*, long long);
void absv(int*, int*); 
void reverse(int*, int );
long long divide(int*, long long, int*);
void multiply(int*, long long, int*);
long long encode(long long,long long,int);


void make_int (int A[], long long n) {
	int	i;
	i = 0;
	while (n) {
		A[i++] = n % 10;
    	n /= 10;
	}

	while (i < N) A[i++] = 0;
	reverse(A, N);
}
void reverse(int arr[], int n){
    int aux[n];
    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}
void multiply(int* a, long long b, int* c) { // b 為乘數
    int op1[N] = {0}; absv(a, op1);


    long long i, tmp, carry = 0; 
    for(i = N - 1; i >= 0; i--) { 
        tmp = op1[i] * b + carry; 
        c[i] = tmp % 10;    
        carry = tmp / 10; 
    }

} 
long long divide(int* a, long long b, int *c) {  // b 為除數 
    int op1[N] = {0}; 
    absv(a, op1);

    
    long long i, tmp, remain = 0; 
    for(i = 1; i < N; i++) { 
        tmp = op1[i] + remain;
        
        c[i] = tmp / b;
        if(i==N-1) return (tmp % b);
        remain = (tmp % b) * 10; 
        
    }

}
void absv(int* src, int* op) {
    if(src[0] == 9999) {
        //toComp(src, op);
    } else {
        int i;
        for(i = 0; i < N; i++) {
            op[i] = src[i];
        }
    }
}




long long encode(long long n,long long e,int m){
    long long result = 0;
    int mr[N];
    int resultr[N];

    make_int(mr,m);//long long int to int[]
    make_int(resultr,0);

    result=(long long )m;
    long long count =e;
    long long temp;
    int sum[N];
    make_int(sum,1);
    
    while(1){
        
        if(count%(long long)2!=0) {
            
            multiply (sum,result, sum);
            temp = divide(sum, n, resultr);
            make_int(sum,temp);
            
            
        }
        count = count/(long long)2;
        multiply (mr,result, mr);//mr = mr*result
        result = divide(mr, n, resultr); // mr/n  resultr(商) result(回傳的餘)
        make_int(mr,result);
        /*
        for(int i = 0;i<N;i++){
            printf("%d,",mr[i]); 
        }*/
    
        
        if(count==1){
            multiply (mr,temp, sum);
            result = divide(sum, n, resultr);
            break;
        }
    }

    return result;
}

int main(void) {
	long long n, e;
	int i;
	char input[20];
	scanf("%lld%lld%19s", &n, &e,input);

	for(i=0;i<20;i++){
	    if(input[i]=='\0') break;
	    long long result = encode(n,e,input[i]);
	    
	    if(i==0) printf("%lld",result);
	    else printf(",%lld",result);
	}

	return 0;
}