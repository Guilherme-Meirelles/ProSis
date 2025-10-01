int GetBitn(int num, int n){  
// recupera o valor (1 ou 0) do n-ésimo bit de num. 
//         0 =< n <= 31        
    return ((num & (1 << n)) >> n); 
} 

void main(){
int n;int bb; int kk;
unsigned  int ParImpar[91];

for (int i = 0; i <90; i++)
    ParImpar[i] =  0xAAAAAAAA;
    scanf("\n %d", &n);
  // atribuição de valor inteiro em hexadecimal.
    bb = n /32;
    kk = n%32;
 // é par ou ímpar???? 
  if (GetBitn(ParImpar[bb], kk)) { printf("\n %d (impar)", n); } 
  else { printf("\n %d (par)", n); }
  
}