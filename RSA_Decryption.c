#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define N 50

void make_int (int*, long long);
void absv(int*, int*); 
void reverse(int*, int );
long long divide(int*, long long, int*);
void multiply(int*, long long, int*);

long long encode(long long,long long,int);
long long privateKey(long long,long long,int*);



void make_int (int A[], long long n) {
    int i;
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
  
    int i;
    for(i = 0; i < N; i++) {
        op[i] = src[i];
    }
    
}

long long findPrime(long long n){
    long long result= -1;
    long long i;
    for(i=3;i<n;i+=2){
        if((n%i)==0){
            result = n/i;
            break;
        }
    }
    return result;
}

long long  privateKey(long long phi,long long e,int* dr){
    int phi_r[N];
    int qt_r[N];
    make_int(phi_r,phi);
    make_int(qt_r,0);
    long long e_temp = e,remain;
    //make_int(dr,0);
    
    long long x1=1,y1,x2,y2,x3,y3,q,t1, t2, t3;
    x1 = y2 = 1;  
    x2 = y1 = 0;  
    x3 = phi;  
    y3 = e; 
    
    while(1){
        //printf("e:%lld,",e);
        //remain = divide(phi_r,e,qt_r);
        //q = arraytoint(qt_r);
        q = x3 / y3;
        t1 = x1 - q * y1;  
        t2 = x2 - q * y2;  
        t3 = x3 - q * y3;  
        x1 = y1;  
        x2 = y2;  
        x3 = y3;  
        y1 = t1;  
        y2 = t2;  
        y3 = t3;
        //printf("remain: %lld\n",remain);
        if(y3==1){break;}
        //make_int(phi_r,e);
        //e=remain;
        
    }
    long long a=y1,b=y2;
    if(b<0){
        b=b+phi;
    }
    
    return b;
    
}

long long decode(long long n,long long e,long long m){
    long long result = 0;
    int mr[N];
    int resultr[N];

    make_int(mr,m);
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
        multiply (mr,result, mr);
        result = divide(mr, n, resultr);
        make_int(mr,result);

        if(count==1){
            multiply (mr,temp, sum);
            result = divide(sum, n, resultr);
            break;
        }
    }

    return result;

}


int main(void) {
    long long n, e,d;
    int i,result,first = 0;
    char input[5000];

    scanf("%lld%lld%4999s", &n, &e,input);
 
    long long p,q,sum;
 
    p = findPrime(n);
    q = n/p;
    //printf("prime:%lld&%lld sum:%lld\n",p,q,(p-1)*(q-1));
    sum = (p-1)*(q-1);
    
    int dr[N];
    d = privateKey(sum,e,dr);
    
    
    char *temp = strtok(input, ",");
    long long num;
    while( temp != NULL ) {

        sscanf(temp, "%lld", &num);
        
        result = decode(n,d,num);
        printf("%c",result);
        
        temp = strtok(NULL, ",");
    }

 return 0;
}
