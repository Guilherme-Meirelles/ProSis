
int main()
{
    int n;
    int r;
    int i;
    printf("Digite o número inteiro (positivo ou negativo): ")
    scanf("%d", &n);

    for (i = 31; i >= 0; i--)
    {
        r = n >> 1;

        if (r & 1)
        {
            printf("1")
        }
        else
        {
            printf("0")
        }
    }
    printf("\n")
}