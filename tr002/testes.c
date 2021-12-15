int main()
{
    int altura = 8;
    int maximo, aux, altura, vezes,flag;
    // ZERAFLAG
    do
    {
        maximo = altura - vezes;
        for(aux = maximo; aux > 0; aux --)
        {
            if(flag)
                return;
        }
        for(aux = 0; aux < maximo; aux++)
        {
            if(flag)
                return;
        }
        vezes++;
    }while(maximo);

}