#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BALANCE_START 1000

typedef struct card
{
    int nr;// numar 1 as, 2-10 self named, 11 J, 12 Q, 13 K
    char culoare;// i inima rosie, n inima neagra, r romb, t trefla 
}card;

void create_new_deck(card pachet [52])
{
    card deck[52];
    for (int i=0; i<52; i++)
    {
        deck[i].nr=(i%13)+1;//de la 1 as la 13 k
        if(i<13) deck[i].culoare='i';
        else if (i<(13*2)) deck[i].culoare='n';
        else if (i<(13*3)) deck[i].culoare='r';
        else deck[i].culoare='t';
    }
    for(int i=0; i<52; i++)
    {
        pachet[i]=deck[i];
    }
}

card generate_random_card()
{
    card carterandom;
    int culoarerandom = rand() % (4 - 1 + 1) + 1;
    int numarrandom = rand() % (13 - 1 + 1) + 1;
    carterandom.nr=numarrandom;
    switch (culoarerandom)
    {
        case 1:
        carterandom.culoare='i';
        break;
        case 2:
        carterandom.culoare='n';
        break;
        case 3:
        carterandom.culoare='r';
        break;
        case 4:
        carterandom.culoare='t';
        break;
    }
    return carterandom;
}

card random_card_from_deck (card pachet[52])
{
    int indexrand=rand()%52;
    return pachet[indexrand];
}

void switch_cards(card deck[52], int p1, int p2)
{
    card aux;
    aux=deck[p1];
    deck[p1]=deck[p2];
    deck[p2]=aux;
}

void shuffle_deck(card pachet[52], int efficiency) //eficienta inseamna de cate sute de ori schimba carti random
{
    card deck[52];
    for(int i=0; i<52; i++)
    {
        deck[i]=pachet[i];
    }
    for(int i=0;i<efficiency;i++)
    {
        for(int j=0; j<100; j++)
        {
            int posrandom1 = rand() % 52;//de la 0 la 51
            int posrandom2;
            do{
            posrandom2 = rand() % 52;
            }while(posrandom1==posrandom2);//sa fiu sigur ca sunt 2 diferite
            //if(posrandom1<0||posrandom1>52||posrandom2<0||posrandom2>52) printf("error message");
            switch_cards(deck, posrandom1, posrandom2);
        }
    }
    for(int i=0; i<52; i++)
    {
        pachet[i]=deck[i];
    }
}

void print_card(card carte)
{
    if(carte.nr<=10&&carte.nr>=2)
    {
        printf("%d",carte.nr);
    }
    switch (carte.nr)
    {
        case 1:
        printf("As");
        break;
        case 11:
        printf("Juve");
        break;
        case 12:
        printf("Dama");
        break;
        case 13:
        printf("Rege");
        break;
        default://2-9 e mai sus in if
        break;
    }
    printf(" de ");
    switch(carte.culoare)
    {
        case 'i':
        printf("inima rosie");
        break;
        case 'n':
        printf("inima neagra");
        break;
        case 'r':
        printf("romb");
        break;
        case 't':
        printf("trefla");
        break;
    }
}

void print_deck(card pachet[52])
{
    for(int i=0; i<52; i++)
    {
        print_card(pachet[i]);
        printf("\n");
    }
}

void print_menu()
{
    printf("Alege un joc:\n");
    printf("0.Cashout");
    printf("1.Higher/lower (hi-lo)\n");
    printf("2.BlackJack (21)\n");
    printf("Optiune: ");
}

int bj_value(card c)
{
    if(c.nr<=10) return c.nr;//fara cazul de as=11
    else return 10;
}

int check_blackjack(card c1, card c2)
{
    if((c1.nr==1&&(bj_value(c2)==10))||(c2.nr==1&&(bj_value(c1)==10))) return 1;
    return 0;// no need for else
}

int posprimas(int n, card player[n])
{
    for(int i=0; i<n; i++)
    {
        if(player[i].nr==1) return i;
    }
    return -1;
}

double chance_higher_or_same(card c, card d[52], int k)//k indexul cartii trase
{
    int nrfav=0,nrpos=52-(k+1);
    for(int i=k+1; i<52; i++)
    {
        if(d[i].nr>=c.nr) nrfav++;
    }
    return (double)nrfav/nrpos;
}

double chance_higher(card c, card d[52], int k)//k indexul cartii trase
{
    int nrfav=0,nrpos=52-(k+1);
    for(int i=k+1; i<52; i++)
    {
        if(d[i].nr>c.nr) nrfav++;
    }
    return (double)nrfav/nrpos;
}

double chance_lower_or_same(card c, card d[52], int k)
{
    int nrfav=0,nrpos=52-(k+1);
    for(int i=k+1; i<52; i++)
    {
        if(d[i].nr<=c.nr) nrfav++;
    }
    return (double)nrfav/nrpos;
}

double chance_lower(card c, card d[52], int k)
{
    int nrfav=0,nrpos=52-(k+1);
    for(int i=k+1; i<52; i++)
    {
        if(d[i].nr<c.nr) nrfav++;
    }
    return (double)nrfav/nrpos;
}

int main()
{
    srand(time(NULL));
    card pachet[52];
    create_new_deck(pachet);
    // printf("Pachet neamestecat: \n\n");
    // print_deck(pachet);
    // shuffle_deck(pachet,100);
    // printf("\n\nPachet amestecat: \n\n");
    // print_deck(pachet);
    int bani= BALANCE_START,pariu=0;
    int opt=1;
    while(opt&&bani>0)
    {
        printf("Balance: %d\n",bani);
        print_menu();
        scanf("%d", &opt);
        switch (opt)
        {
            case 0:
            break;
            case 1:
            double multiplier=1;
            shuffle_deck(pachet,100+(rand()%900));// mai mult de 1000 de sute de schimbari nu e necesar
            do{
                if(pariu>bani) printf("Nu poti paria mai mult decat ai!\n");
                if(pariu<1) printf("Pariul trebuie sa fie o suma intreaga pozitiva si nenula!\n");
                printf("Balance: %d\n",bani);
                printf("Pariu: ");
                scanf("%d",&pariu);}while(pariu>bani||pariu<1);
                bani-=pariu;
            printf("Prima carte: ");
            print_card(pachet[0]);
            char optiune[2];
            int i=0;
            while(strcmp("co",optiune)){
                if(i>0)
                {
                    printf("Cartile de pana acum: \n");
                    for(int j=0; j<i;j++)
                    {
                        print_card(pachet[j]);
                        printf("\t");
                    }
                    printf("\nCartea curenta: ");
                    print_card(pachet[i]);
                }
            printf("\nMultiplicator pana acum: %f\nAlege o optiune: hs-higher or same, ls-lower or same, hi-higher, lo-lower, sk-skip card, co-cash out.\n", multiplier);
            printf("SANSE:\nhs-%f, multiplicator %f X\nls-%f, multiplicator %f X\nhi-%f, multiplicator %f X\nlo-%f, multiplicator %f X\n",chance_higher_or_same(pachet[i],pachet,i),1/chance_higher_or_same(pachet[i],pachet,i),chance_lower_or_same(pachet[i],pachet,i),1/chance_lower_or_same(pachet[i],pachet,i),chance_higher(pachet[i],pachet,i),1/chance_higher(pachet[i],pachet,i),chance_lower(pachet[i],pachet,i),1/chance_lower(pachet[i],pachet,i));
            printf("optiune: ");
            do{
            scanf("%s",&optiune[0]);
            }while(strcmp("hs",optiune)&&strcmp("ls",optiune)&&strcmp("hi",optiune)&&strcmp("lo",optiune)&&strcmp("sk",optiune)&&strcmp("co",optiune));

            printf("Next card: ");
            print_card(pachet[i+1]);
            printf("\n");

            if(strcmp("hs",optiune)==0)
            {
                if(pachet[i+1].nr>=pachet[i].nr) {
                    printf("Felicitari, ati castigat!\n");
                    multiplier*=(double)1/chance_higher_or_same(pachet[i],pachet,i);
                }
                else{
                    printf("O nu! Ati pierdut!\n");
                    break;
                }
            }
            else if(strcmp("ls",optiune)==0)
            {
                if(pachet[i+1].nr<=pachet[i].nr) {
                    printf("Felicitari, ati castigat!\n");
                    multiplier*=(double)1/chance_lower_or_same(pachet[i],pachet,i);
                }
                else{
                    printf("O nu! Ati pierdut!\n");
                    break;
                }
            }
            else if(strcmp("hi",optiune)==0)
            {
                if(pachet[i+1].nr>pachet[i].nr) {
                    printf("Felicitari, ati castigat!\n");
                    multiplier*=(double)1/chance_higher(pachet[i],pachet,i);
                }
                else{
                    printf("O nu! Ati pierdut!\n");
                    break;
                }
            }
            else if(strcmp("lo",optiune)==0)
            {
                if(pachet[i+1].nr<pachet[i].nr) {
                    printf("Felicitari, ati castigat!\n");
                    multiplier*=(double)1/chance_lower(pachet[i],pachet,i);
                }
                else{
                    printf("O nu! Ati pierdut!\n");
                    break;
                }
            }
            else if(strcmp("sk",optiune)==0)
            {
                i++; continue;
            }
            else if(strcmp("co",optiune)==0)//va iesi din while singur si fara break
            {
                bani=(int)(bani+(pariu*multiplier));//o mica rotunjire
            }
            i++;
            }
            break;
            case 2:
            int playersum1=0, playersum2=0, dealersum1=0, dealersum2=0;
            shuffle_deck(pachet,100+(rand()%900));// mai mult de 1000 de sute de schimbari nu e necesar
            do{
            if(pariu>bani) printf("Nu poti paria mai mult decat ai!\n");
            if(pariu<1) printf("Pariul trebuie sa fie o suma intreaga pozitiva si nenula!\n");
            printf("Balance: %d\n",bani);
            printf("Pariu: ");
            scanf("%d",&pariu);}while(pariu>bani||pariu<1);
            bani-=pariu;
            printf("Dealer: ");
            print_card(pachet[0]);
            printf(" + ???\n");//a doua carte a dealerului e misterioasa (pachet[1])
            printf("Player: ");
            print_card(pachet[2]);
            printf(" ");
            print_card(pachet[3]);
            if(pachet[2].nr!=1&&pachet[3].nr!=1) {
                playersum1=bj_value(pachet[2])+bj_value(pachet[3]);
                playersum2=playersum1;
            }
            else if(pachet[2].nr==1)
            {
                playersum1=1+bj_value(pachet[3]);
                playersum2=11+bj_value(pachet[3]);
            }
            else if(pachet[3].nr==1)
            {
                playersum1=1+bj_value(pachet[2]);
                playersum2=11+bj_value(pachet[2]);
            }
            else if(pachet[2].nr==1&&pachet[3].nr==1)
            {
                playersum1=2;
                playersum2=12;
            }
            if(check_blackjack(pachet[2],pachet[3]))
            {
                if(!check_blackjack(pachet[0],pachet[1]))
                {
                printf("Castigator! Blackjack!\n");
                bani+=pariu*2;
                break;
                }
                else{
                    printf("Egalitate de blackjack! dealerul avea cartea secreta: ");
                    print_card(pachet[1]);
                    bani+=pariu;
                }
            }
            if(playersum1==playersum2) printf("\nSuma carti player: %d",playersum1);
            else printf("\nSuma carti player: %d/%d", playersum1, playersum2);
            if(pariu<bani)
            {
                printf("\nDublezi pariul? y/n: ");
                char y='y';
                do{
                    if(y!='y'&&y!='n') printf("Optiune invaida! apasa y pt yes sau n pt no: ");
                    scanf("%c",&y);
                }while(y!='y'&&y!='n');
            }
            printf("\nPentru stand apasa tasta 's', pentru hit apasa tasta'h': ");
            char hitorstand='h';
            do{
                if(hitorstand!='s'&&hitorstand!='h') printf("Nu e o optiune valida! h sau s, hit sau stand!\n mai incearca: ");
                scanf("%c",&hitorstand);
            }while(hitorstand!='s'&&hitorstand!='h');
            int crt=4;
            while(hitorstand=='h')//hit
            {
                card carti_player[crt-1];
                carti_player[0]=pachet[2];
                carti_player[1]=pachet[3];
                printf("Player: ");
                print_card(pachet[2]);
                printf(" ");
                print_card(pachet[3]);
                for(int i=4;i<=crt;i++){
                    printf(" ");
                    print_card(pachet[i]);
                    carti_player[i-2]=pachet[i];
                }
                // if(posprimas(crt-1,carti_player)>=0)//exista un as
                // {
                    int ppa=posprimas(crt-1,carti_player);//-1 daca nu exista asi
                    playersum1=0;
                    playersum2=0;
                    for(int i=0; i<crt-1; i++)
                    {
                        if(i!=ppa){ playersum1+=bj_value(carti_player[i]);playersum2+=bj_value(carti_player[i]);}
                        else {playersum1+=1;playersum2+=11;}
                    }
                // }
                // else{//inca nu am extras niciun as
                //     for(int i=4;i<=crt;i++)
                //     {
                //         playersum1+=bj_value(pachet[i]);
                //         playersum2=playersum1;
                //     }
                // }

                if(playersum1==playersum2||(playersum2>21&&playersum1<=21)) printf("\nSuma carti player: %d",playersum1);
                else if(playersum1<=21&&playersum2<=21)printf("\nSuma carti player: %d/%d", playersum1, playersum2);
                else if(playersum1>21&&playersum2<=21)printf("\nSuma carti player: %d",playersum2);
                else if(playersum1>21&&playersum2>21)
                {
                    printf("Depasire! Suma carti player: %d > 21! Ati pierdut!",playersum1);
                    break;break;
                }
                else if(playersum1==21||playersum2==21)
                {
                    printf("Ati ajuns la 21! Time to stand!");
                    hitorstand='s';//stand
                    break;
                }
                printf("\nPentru stand apasa tasta 's', pentru hit apasa tasta'h': ");
                do{
                    if(hitorstand!='s'&&hitorstand!='h') printf("Nu e o optiune valida! h sau s, hit sau stand!\n mai incearca: ");
                    scanf("%c",&hitorstand);
                }while(hitorstand!='s'&&hitorstand!='h');
                crt++;
            }
            if(hitorstand=='s'){//stand
                int playersum,dealersum;
                if(playersum1==playersum2||(playersum2>21&&playersum1<=21)) playersum=playersum1;
                else if(playersum1<=21&&playersum2<=21)
                {
                    if(playersum1>playersum2) playersum=playersum1;//mai aproape de 21
                    else playersum=playersum2;
                }
                else if(playersum1>21&&playersum2<=21)playersum=playersum2;
                //else if(playersum1>21&&playersum2>21)
                //imposibil, am verificat
                if(check_blackjack(pachet[0],pachet[1]))
                {
                    printf("Dealer: ");
                    print_card(pachet[0]);
                    printf(" ");
                    print_card(pachet[1]);
                    printf("\nAti pierdut! dealer-ul are blackjack\n");
                    break;
                }

                if(pachet[0].nr!=1&&pachet[1].nr!=1) {
                    dealersum1=bj_value(pachet[0])+bj_value(pachet[1]);
                    dealersum2=dealersum1;
                }
                else if(pachet[0].nr==1)
                {
                    dealersum1=1+bj_value(pachet[1]);
                    dealersum2=11+bj_value(pachet[1]);
                }
                else if(pachet[1].nr==1)
                {
                    dealersum1=1+bj_value(pachet[0]);
                    dealersum2=11+bj_value(pachet[0]);
                }
                else if(pachet[0].nr==1&&pachet[1].nr==1)
                {
                    dealersum1=2;
                    dealersum2=12;
                }
                if(dealersum1==dealersum2||(dealersum2>21&&dealersum1<=21)) dealersum=dealersum1;
                else if(dealersum1<=21&&dealersum2<=21)
                {
                    if(dealersum1>dealersum2) dealersum=dealersum1; //mai aproape de 21
                    else dealersum=dealersum2;
                }
                else if(dealersum1>21&&dealersum2<=21) dealersum=dealersum2;

                if(dealersum1==dealersum2) printf("\nSuma carti dealer: %d",dealersum1);
                else printf("\nSuma carti dealer: %d/%d", dealersum1, dealersum2);
                //printf("\nPentru stand apasa tasta 's', pentru hit apasa tasta'h': ");
                //char hitorstand='h';
                while(21-playersum<21-dealersum)//dealerul de hit pana se apropie mai tare de 21
                {
                    
                    // Recalculăm dealersum înainte de următoarea trasă, ca să știm condiția la început:
                    if (dealersum1 == dealersum2 || (dealersum2 > 21 && dealersum1 <= 21))
                        dealersum = dealersum1;
                    else if (dealersum1 <= 21 && dealersum2 <= 21)
                        dealersum = (dealersum1 > dealersum2 ? dealersum1 : dealersum2);
                    else if (dealersum1 > 21 && dealersum2 <= 21)
                        dealersum = dealersum2;

                    // copiem toate cărțile dealer-ului într-un array ca să calculăm As-ul etc.
                    card carti_dealer[crt - 1];
                    carti_dealer[0] = pachet[0];
                    carti_dealer[1] = pachet[1];
                    printf("Dealer: ");
                    print_card(pachet[0]);
                    printf(" ");
                    print_card(pachet[1]);
                    for (int i = 2; i <= crt; i++) {
                        printf(" ");
                        print_card(pachet[i]);
                        carti_dealer[i] = pachet[i];
                    }

                    int ppa = posprimas(crt - 1, carti_dealer); // index of As, sau -1
                    dealersum1 = 0;
                    dealersum2 = 0;
                    for (int i = 0; i < crt - 1; i++) {
                        if (i != ppa) {
                            dealersum1 += bj_value(carti_dealer[i]);
                            dealersum2 += bj_value(carti_dealer[i]);
                        } else {
                            dealersum1 += 1;
                            dealersum2 += 11;
                        }
                    }

                    // afișăm suma curentă a dealer-ului
                    if (dealersum1 == dealersum2 || (dealersum2 > 21 && dealersum1 <= 21))
                        printf("\nSuma carti dealer: %d", dealersum1);
                    else if (dealersum1 <= 21 && dealersum2 <= 21)
                        printf("\nSuma carti dealer: %d/%d", dealersum1, dealersum2);
                    else if (dealersum1 > 21 && dealersum2 <= 21)
                        printf("\nSuma carti dealer: %d", dealersum2);
                    else if (dealersum1 > 21 && dealersum2 > 21) {
                        printf("Depasire! Suma carti dealer: %d > 21! Ati castigat!", dealersum1);
                        break;
                        break;
                    }

                    crt++;  // dealer trage o carte în plus
                    // Recalculăm dealersum după trasă, ca să se actualizeze în condiția while:
                    if (dealersum1 == dealersum2 || (dealersum2 > 21 && dealersum1 <= 21))
                        dealersum = dealersum1;
                    else if (dealersum1 <= 21 && dealersum2 <= 21)
                        dealersum = (dealersum1 > dealersum2 ? dealersum1 : dealersum2);
                    else if (dealersum1 > 21 && dealersum2 <= 21)
                        dealersum = dealersum2;
                }
                if(dealersum>playersum)
                {}
                else if(dealersum==playersum)//no need for if
                {
                    printf("Egalitate!");
                    bani+=pariu;
                }




            }
            break;
            default:
            printf("Optiune invalida!\n");
            break;
        }
    }
    if(bani==0) printf("Ati pierdut toti banii! jucati mai responsabil!");
    else if(bani>BALANCE_START) printf("Ati scos %d bani, facand un profit de %d", bani, bani-BALANCE_START);
    else if(bani<BALANCE_START) printf("Ati scos %d bani, pierzand un total de %d", bani, BALANCE_START-bani);
    return 0;
}
