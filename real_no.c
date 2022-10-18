#include<omp.h>
#include<stdio.h>
#include<stdbool.h>
#include <math.h>


bool isPerfect(int n){
    int sum = 1;
  
    // Find all divisors and add them
    for (long int i=2; i*i<=n; i++)
    {
        if (n%i==0)
        {
            if(i*i!=n)
                sum = sum + i + n/i;
            else
                sum=sum+i;
        }
    }
     // If sum of divisors is equal to
     // n, then n is a perfect number
     if (sum == n && n != 1){
       return true;
     }
     return false;
}

bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;
 
    // Check from 2 to square root of n
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
 
    return true;
}

int main(){
  int val;
  bool is_rational,is_perfect,is_prime;
  printf("\nEnter a value ");
  scanf("%d",&val);
  #pragma omp parallel sections num_threads(3) private(is_rational) firstprivate(is_prime) lastprivate(is_perfect)
  {
    #pragma omp section 
    {
        is_rational = true;
        printf("\nThe number is rational ");
    }
     #pragma omp section 
    {
        is_prime = isPrime(val);
        if(is_prime){
            printf("\nThe number is prime");
        } else{
            printf("\nThe number is not prime");
        }
    }
     #pragma omp section 
    {
        is_perfect = isPerfect(val);
        if(is_perfect){
            printf("\nThe number is perfect");
        } else {
            printf("\nThe number is not perfect");
        }
    }
  }
}
