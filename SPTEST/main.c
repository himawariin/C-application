#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *p=0;
void print();// printeaza toate ofertele
void antet();   // pagina de pornire
void rezervare();// genereaza chestionarul de nume,nr de telefon, sejur dorit
void rezervare1();// face rezervarea  vizibila in fisiere
void anulare(); //extrage datekle ce trebuie pt  anulare din fisierul de rezervari
void anularef(); //sterge din fisierul de rezervari
void anularef1(); //modifica fisierul de oferte
void cautare(); // posibilitati: a cauta dupa locatie, nr de notpi al sejurului sau pret
void confirmare();  // sa afiseze cod unic al rezervarii pentru  client
int codunic();  // returneaza cod unic al fiecarei rezervari facute
void oferta();  // sa se afiseze ofertele toate sau   dupa criteriu specific
void creoferta(); // pun ofertele intr-un struct
void revedere();    // de cautat dupa cod client sau dupa numarul de telefon
void corect(); //ajuta in cazul in care  persoana pune grecia sau Grecia sau gRECIA
void printrev();
typedef struct sejure
{
    int nr,dis,pret,nopti;
    char hotel[50],tara[50];
} sejure;

sejure sejur[500];
int main()
{
    creoferta(sejur);
    antet();
    return 0;
}

void creoferta(sejure sejur[])
{
    FILE *oferte;
    oferte=fopen("Oferte.txt","r");
    char s[500],sep[2]="/",t[500],*p;
    int j=0,i;
    while(fgets(s,500,oferte))
    {
        j++;
        strcpy(t,s);
        p=strtok(t,sep);
        for(i=0; i<=strlen(p)-1; i++)
            sejur[j].nr=sejur[j].nr*10+(p[i]-'0');
        p=strtok(NULL,sep);
        strcpy(sejur[j].tara,p);
        p=strtok(NULL,sep);
        strcpy(sejur[j].hotel,p);
        p=strtok(NULL,sep);
        for(i=0; i<=strlen(p)-1; i++)
            sejur[j].pret=sejur[j].pret*10+(p[i]-'0');
        p=strtok(NULL,sep);
        for(i=0; i<=strlen(p)-1; i++)
            sejur[j].nopti=sejur[j].nopti*10+(p[i]-'0');
        p=strtok(NULL,sep);
        sejur[j].dis=0;
        for(i=0; i<strlen(p)-1; i++)
            sejur[j].dis=sejur[j].dis*10+(p[i]-'0');
    }
    fclose(oferte);

}

void antet()
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   Buna ziua! ^-^   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~   Bine ati venit la Agentia de turism Himawari ^-^   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    printf("Sunteti nou aici? APASATI 1 daca da, respectiv 0 daca nu:\n");
    int a;
    scanf("%d",&a);
    if(a==1)
    {
        printf("Bine ati venit! Suntem incantati sa va prezentam ofertele noastre de vacante!\n");
        printf("Doriti sa cautati un sejur in functie de anumite criterii? APASATI 1 daca da, sau daca nu, APASATI 0.\n");
        scanf("%d",&a);
        if(a==1)
            cautare(sejur);
        else
        {
            printf("Acestea sunt ofertele noastre!\n");
            oferta(sejur);
        }
    }
    else
    {
        printf("Daca ati rezervat un sejur disponibil pe site-ul nostru si doriti sa vedeti si alte oferte APASATI 0.\n");
        printf("Daca ati rezervat un sejur disponibil pe site-ul nostru si doriti sa revedeti  oferta sejurului APASATI 1.\n");
        printf("Daca ati rezervat un sejur disponibil pe site-ul nostru si doriti sa anulati rezervarea APASATI 2.\n");
        printf("Daca ati fost pe site-ul nostru dar nu ati rezervat nimic si doriti sa rezervati, APASATI 3.\n");
        printf("Daca doriti sa iesiti de pe site-ul nostru, APASATI 4.\n");
        int b;
        scanf("%d",&b);
        if(b==0)
        {
            printf("Doriti sa cautati un sejur in functie de anumite criterii? APASATI 1 daca da, sau daca nu, APASATI 0.\n");
            scanf("%d",&a);
            if(a==1)
                cautare(sejur);
            else
            {
                printf("Acestea sunt ofertele noastre!\n");
                oferta(sejur);
            }
        }
        if(b==2)
            anulare();
        if(b==1)
            revedere();
        if(b==3)
        {
            printf("Doriti sa cautati un sejur in functie de anumite criterii? APASATI 1 daca da, sau daca nu, APASATI 0.\n");
            scanf("%d",&a);
            if(a==1)
                cautare(sejur);
            else
            {
                printf("Acestea sunt ofertele noastre!\n");
                oferta(sejur);
            }
        }
        if(b==4)
            return 0;
    }
}


void revedere()
{
    int j,r=0;
    printf("Va mai amintiti codul unic primit cand ati facut rezervarea? APASATI 1 daca da, 0 daca nu\n");
    int a;
    scanf("%d",&a);
    if(a==0)
    {
        int ok=0,r,numar=0,in;
        printf("E ok. Ne puteti spune numarul de telefon pentru a accesa rezervarea. Scrieti cele 10 cifre\n");
        char te[20];
        scanf("%s",te);
        FILE *rez;
        rez=fopen("Rezervari.txt","r");
        char s[100];
        while(fgets(s,500,rez))
        {
            numar++;
            char t[100]="";
            j=-1;
            int i=0;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
            {
                j++;
                t[j]=s[i];
                i++;
            }
            i++;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
            {
                r=r*10+(s[i]-'0');
                i++;
            }
            if(strcmp(te,t)==0)
            {
                ok=1;
                int i=0,k=0;
                while(i<strlen(s))
                {
                    if(s[i]=='/')
                        k=i;
                    i++;
                }
                k++;
                int in=0;
                while(k<strlen(s)&& s[k]<='9' && s[k]>='0')
                {
                    in=in*10+(s[k]-'0');
                    k++;
                }
                printrev(in,r,sejur);
                break;
            }

        }
        fclose(rez);
        if(ok==0)
        {
            printf("Numarul de telefon introdus de dvs. nu este valid. Va rugam sa incercati iar ^-^\n");
            printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doriti sa mai incercati APASATI 2.\n");
                int b;
                scanf("%d",&b);
                if(b==1)
                    antet();
                    else
                    revedere();
        }
        else
        {
            printf("Speram ca v-am fost de ajutor! O zi placuta ^-^\n");
            printf("Daca doriti sa anulati rezervarea APASATI 3\n");
            printf("Doriti sa va intoarceti la pagina de pornire? APASATI 2 daca da\n");
            printf("Daca doriti sa iesiti de pe site-ul nostru, APASATI 4.\n");
            scanf("%d",&a);
            if(a==2)
                antet();
            if(a==3)
                anulare();///// in este  sejurul, r este nr de persoane, numar este a cata linie este in rzervari
                if(a==4)
                    return 0;
        }
    }
    else
    {
        int ok=0,cod,n=0,r=0,numar=0,in;
        printf("Va rugam sa ne spuneti codul unic primit cand ati facut rezervarea.\n");
        scanf("%d",&cod);

        FILE *rez;
        rez=fopen("Rezervari.txt","r");
        char s[100],t[100],*z,sep[2]="/";
        while(fgets(s,500,rez))
        {
            numar++;
            n=0;
            int i=0;
            while(s[i]!='/')
            {
                n=n*10+(s[i]-'0');
                i++;
            }
            i++;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
            {
                r=r*10+(s[i]-'0');
                i++;
            }
            if(n==cod)
            {
                ok=1;
                int i=0,k=0;
                while(i<strlen(s))
                {
                    if(s[i]=='/')
                        k=i;
                    i++;
                }
                k++;
                int in=0;
                while(k<strlen(s)&& s[k]<='9' && s[k]>='0')
                {
                    in=in*10+(s[k]-'0');
                    k++;
                }
                printrev(in,r,sejur);
                break;
            }
        }
        fclose(rez);

        if(ok==0)
        {
            printf("Codul introdus de dvs. nu este valid. Va rugam sa incercati iar ^-^\n");
            printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doriti sa mai incercati APASATI 2.\n");
                int b;
                scanf("%d",&b);
                if(b==1)
                    antet();
                    else
                    revedere();
        }
        else
        {
            printf("Speram ca v-am fost de ajutor! O zi placuta ^-^\n");
            printf("Daca doriti sa anulati rezervarea APASATI 3\n");
            printf("Doriti sa va intoarceti la pagina de pornire? APASATI 2 daca da\n");
            scanf("%d",&a);
            if(a==2)
                antet();
            else
                anulare();///// in este  sejurul, r este nr de persoane, numar este a cata linie este in rzervari
        }
    }

}


void rezervare(int n,sejure sejur [])
{
    printf("\nPagina de rezervare...\n");
    FILE *rez;
    rez=fopen("Rezervari.txt","a");
    char t[200]="/";
    p=codunic();
    printf("Scrieti numarul dvs. de telefon:");
    char tel[20],nume[40];
    scanf("%s",&tel);
    while(((int)strlen(tel))>10 || (int)(strlen(tel))<10)
    {
        printf("Numarul de telefon este invalid, va rugam sa tastati un numar valid ^-^\n");
        printf("Scrieti numarul dvs. de telefon:");
        scanf("%s",tel);
    }
    fprintf(rez,"%d",p);
    strcat(t,tel);
    strcat(t,"/");
    printf("Scrieti numele dvs.:");
    scanf("%s",nume);
    strcat(t,nume);
    strcat(t," ");
    printf("Scrieti preumele dvs.:");
    scanf("%s",&nume);
    printf("Cate locuri doriti sa rezervati?In momentul acesta sunt %d locuri disponibile.\n",sejur[n].dis);
    int q;
    scanf("%d",&q);
    if(q>sejur[n].dis || q<=0)
    {
        printf("Acest numar de locuri nu este disponibil. \n");
        printf("Daca doriti sa introduceti un numar de locuri care este desiponibil  va rugam sa alegeti alt sejur.\n");
        cautare(sejur);
    }
    {
        rezervare1(sejur,n,q);
        strcat(t,nume);
        strcat(t,"/");
        fprintf(rez,"%s",t);
        fprintf(rez,"%d/",q);
        fprintf(rez,"%d\n",n);
        confirmare(p);
    }
    fclose(rez);
}

void rezervare1(sejure sejur[],int n,int x)// n este nr sejurului si x este nr de locuri rezervate
{
    FILE *rez;
    rez=fopen("Oferte.txt","r");
    int k=0;
    char s[500];
    FILE *b;
    b=fopen("bau.txt","a");
    while(fgets(s,500,rez))
    {
        k++;
        if(k==n)
            break;
        fprintf(b,"%s",s);
    }
    int i=0;
    while(i<strlen(s))
    {
        if(s[i]=='/')
            k=i;
        i++;
    }
    char t[100]="";
    int j=-1;
    for(i=0; i<=k; i++)
    {
        j++;
        t[j]=s[i];
    }
    k++;
    int r;
    r=(int)sejur[n].dis-x;
    char a[100];
    j=0;
    while(r)
    {
        j++;
        a[j]=(r%10)+'0';
        r=r/10;
    }
    strrev(a);
    strcat(t,a);
    fprintf(b,"%s",t);

    while(fgets(s,500,rez))
    {
        fprintf(b,"%s",s);
    }
    fclose(b);
    fclose(rez);
    remove("Oferte.txt");
    rename("bau.txt","Oferte.txt");
}

void anulare()
{

    int j,r=0,in;
    printf("Va mai amintiti codul unic primit cand ati facut rezervarea? APASATI 1 daca da, 0 daca nu\n");
    int a;
    scanf("%d",&a);
    if(a==0)
    {
        int ok=0,r,numar=0,in;
        printf("E ok. Ne puteti spune numarul de telefon pentru a accesa rezervarea. Scrieti cele 10 cifre\n");
        char te[20];
        scanf("%s",te);
        FILE *rez;
        rez=fopen("Rezervari.txt","r");
        char s[100];
        while(fgets(s,500,rez))
        {
            numar++;
            char t[100]="";
            j=-1;
            int i=0;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
            {
                j++;
                t[j]=s[i];
                i++;
            }
            i++;
            while(s[i]!='/')
                i++;
            i++;
            r=0;
            while(s[i]!='/')
            {
                r=r*10+(s[i]-'0');
                i++;
            }
            if(strcmp(te,t)==0)
            {
                ok=1;
                int i=0,k=0;
                while(i<strlen(s))
                {
                    if(s[i]=='/')
                        k=i;
                    i++;
                }
                k++;
                int in=0;
                while(s[k]<='9' && s[k]>='0')
                {
                    in=in*10+(s[k]-'0');
                    k++;
                }
                anularef(in,r,sejur,numar);// numar de linii, in nr sejurului si r nr pers
                break;
            }
        }
        fclose(rez);
        if(ok==0)
        {
            printf("Numarul de telefon introdus de dvs. nu este valid. Va rugam sa incercati iar ^-^\n");
            printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doriti sa mai incercati APASATI 2.\n");
                int b;
                scanf("%d",&b);
                if(b==1)
                    antet();
                    else
                    anulare();
        }
    }
    else
    {
        int ok=0,cod,n=0,r=0,numar=0,in;
        printf("Va rugam sa ne spuneti codul unic primit cand ati facut rezervarea.\n");
        scanf("%d",&cod);
        FILE *rez;
        rez=fopen("Rezervari.txt","r");
        char s[500];
        while(fgets(s,500,rez))
        {
            numar++;
            n=0;
            r=0;
            int i=0;
            while(s[i]!='/')
            {
                n=n*10+(s[i]-'0');
                i++;
            }
            i++;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
                i++;
            i++;
            while(s[i]!='/')
            {
                r=r*10+(s[i]-'0');
                i++;
            }

            if(n==cod)
            {
                ok=1;
                int k=0;
                i++;
                k=i;
                int in=0;
                while(s[k]<='9' && s[k]>='0')
                {
                    in=in*10+(s[k]-'0');
                    k++;
                }
                anularef(in,r,sejur,numar);// numar de linii, in nr sejurului si r nr pers
                break;
            }
        }
        fclose(rez);

        if(ok==0)
        {
            printf("Numarul de telefon introdus de dvs. nu este valid. Va rugam sa incercati iar ^-^\n");
            printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doriti sa mai incercati APASATI 2.\n");
                int b;
                scanf("%d",&b);
                if(b==1)
                    antet();
                    else
                    anulare();
        }
    }
}

void anularef(int se,int p,sejure sejur[],int numar)// p este nr de locuri// se este nr sejurului, numar numar de  linii
{
    //ASTA STERGE  LINIA DIN REZERVARI
    FILE *rez;
    rez=fopen("Rezervari.txt","r");
    FILE *b;
    fclose(fopen("bau.txt", "w"));
    b=fopen("bau.txt","a");
    int i=0;
    char s[100];
    while(fgets(s,100,rez))
    {
        i++;
        if(i!=numar)
            fprintf(b,"%s",s);
    }
    fclose(rez);
    fclose(b);
    fclose(fopen("Rezervari.txt", "w"));
    rez=fopen("Rezervari.txt","a");
    b=fopen("bau.txt","r");
    while(fgets(s,100,b))
        fprintf(rez,"%s",s);
    fclose(rez);
    fclose(b);
    anularef1(se,p,sejur);
}


void anularef1(int se,int p,sejure sejur[])
{
    //ASTA MODIFICA FISIERUL OFERTE

    FILE *rez;
    rez=fopen("Oferte.txt","r");
    FILE *b;
    fclose(fopen("au.txt", "w"));
      b=fopen("au.txt","a");
    int i=0,k;
    char s[100];
    while(fgets(s,100,rez))
    {
        i++;
        if(i!=se)
            fprintf(b,"%s",s);
        else
        {
            int z=0;
            while(z<strlen(s))
            {
                if(s[z]=='/')
                    k=z;
                z++;
            }
            char t[100]="";
            int j=-1;
            for(z=0; z<=k; z++)
            {
                j++;
                t[j]=s[z];
            }
            k++;
            int r=0;
            while(k<strlen(s))
            {if(s[k]>='0' && s[k])
                r=r*10+(s[k]-'0');
                k++;
            }
            r=r+p;
            char a[100]="";
            j=-1;
            while(r)
            {
                j++;
                a[j]=(r%10)+'0';
                r=r/10;
            }
            strrev(a);
            strcat(t,a);
            fprintf(b,"%s\n",t);

        }
    }
    fclose(rez);
    fclose(b);
    fclose(fopen("Oferte.txt", "w"));
    rez=fopen("Oferte.txt","a");
    b=fopen("au.txt","r");
    while(fgets(s,100,b))
        fprintf(rez,"%s",s);
    fclose(rez);
    fclose(b);

    printf("Rezervarea dvs. a fost anulata!");
}


void corect(char s[])
{
    if(s[0]>='a' && s[0]<='z')
        s[0]=s[0]-'a'+'A';
    for(int i=1; i<strlen(s); i++)
        if(s[i]>='A' && s[i]<='Z')
            s[i]=s[i]+'a'-'A';
}
void print(int j,sejure sejur[])
{
    printf("Numar sejur : %d\n",sejur[j].nr);
    printf("Tara sejur: %s\n",sejur[j].tara);
    printf("Cazare la : %s\n",sejur[j].hotel);
    printf("Pret per persoana : %d euro\n",sejur[j].pret);
    printf("Durata sejur : %d nopti\n",sejur[j].nopti);
    printf("Locuri disponibile: %d\n",sejur[j].dis);
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
}
void printtara(int j,sejure sejur[])
{
    printf("Numar sejur : %d\n",sejur[j].nr);
    printf("Cazare la : %s\n",sejur[j].hotel);
    printf("Pret per persoana : %d euro\n",sejur[j].pret);
    printf("Durata sejur : %d nopti\n",sejur[j].nopti);
    printf("Locuri disponibile: %d\n",sejur[j].dis);
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
}

void printrev(int j,int n,sejure sejur[])// n este nr de pers
{
    printf("Numar sejur : %d\n",sejur[j].nr);
    printf("Tara sejur: %s\n",sejur[j].tara);
    printf("Cazare la : %s\n",sejur[j].hotel);
    printf("Pret per persoana : %d euro\n",sejur[j].pret);
    printf("Pret total : %d euro\n",(sejur[j].pret)*n);
    printf("Durata sejur : %d nopti\n",sejur[j].nopti);
    printf("Locuri rezervate: %d\n",n);
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
}

void cautare(sejure sejur[])
{
    int ok1=0,ok2=0,ok3=0;
    printf("Doriti sa va intoarceti la pagina de pornire? APASATI 2 daca da, APASATI 3 daca nu\n");
    int a;
    scanf("%d",&a);
    if(a==2)
        antet();
        else
        {

    printf("Daca doresti sa filtrezi ofertele in functie de locatie, APASATI 1, altfel APASATI 0.\n");
    int x;
    scanf("%d",&x);
    if(x==1)
        ok1=1;

    printf("Daca doresti sa filtrezi ofertele vazute in functie de pret, APASATI 1, altfel APASATI 0.\n");
    scanf("%d",&x);
    if(x==1)
        ok2=1;
    printf("Daca doresti sa filtrezi ofertele vazute in functie de numarul de nopti, APASATI 1, altfel APASATI 0.\n");
    scanf("%d",&x);
    if(x==1)
        ok3=1;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int z=0;
    if(ok1==0 && ok2==0 && ok3==0)
    {
        for(int j=1; j<200; j++)
        {
            if(sejur[j].nr==0)
                break;
            print(j,sejur);
        }
    }
    else
    {
        if(ok1==1 && ok2==0 && ok3==0)
        {
            printf("Alegeti tara in care doriti sejurul.\n");
            printf("Tara cautata: ");

            char s[20];
            scanf("%s",s);
            corect(s);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("%s\n",s);

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(strcmp(sejur[j].tara,s)==0)
                {
                    printtara(j,sejur);
                    z=1;
                }
            }

        }
        if(ok1==1 && ok2==0 && ok3==1)
        {
            printf("Alegeti tara in care doriti sejurul.\n");
            printf("Tara cautata: ");
            char s[20];
            scanf("%s",s);
            int x1,x2;
            printf("Alegeti un numarul de nopti minim si maxim.\n");
            printf("Nr. nopti minim: ");
            scanf("%d",&x1);
            printf("\nNr. nopti maxim : ");
            scanf("%d",&x2);
            corect(s);

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("%s\n",s);

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(strcmp(sejur[j].tara,s)==0 && sejur[j].nopti>=x1 && sejur[j].nopti<=x2)
                {
                    printtara(j,sejur);
                    z=1;
                }
            }

        }
        if(ok1==0 && ok2==0 && ok3==1)
        {
            int x1,x2;
            printf("Alegeti un numarul de nopti minim si maxim.\n");
            printf("Nr. nopti minim: ");
            scanf("%d",&x1);
            printf("\nNr. nopti maxim : ");
            scanf("%d",&x2);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(sejur[j].nopti>=x1 && sejur[j].nopti<=x2)
                {
                    print(j,sejur);
                    z=1;
                }
            }

        }
        if(ok1==0 && ok2==1 && ok3==0)
        {
            printf("Alegeti un pret minim si un pret maxim.\n");
            printf("Pret minim: ");
            int x1,x2;
            scanf("%d",&x1);
            printf("\nPret maxim : ");
            scanf("%d",&x2);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(sejur[j].pret>=x1 && sejur[j].pret<=x2)
                {
                    print(j,sejur);
                    z=1;
                }
            }

        }
        if(ok1==0 && ok2==1 && ok3==1)
        {

            int x1,x2;
            printf("Alegeti un numarul de nopti minim si maxim.\n");
            printf("Nr. nopti minim: ");
            scanf("%d",&x1);
            printf("\nNr. nopti maxim : ");
            scanf("%d",&x2);
            int y1,y2;
            printf("Alegeti un pret minim si maxim.\n");
            printf("Pret minim: ");
            scanf("%d",&y1);
            printf("\nPret maxim : ");
            scanf("%d",&y2);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if( sejur[j].nopti>=x1 && sejur[j].nopti<=x2 && sejur[j].pret>=y1 && sejur[j].pret<=y2)
                {
                    print(j,sejur);
                    z=1;
                }
            }

        }
        if(ok1==1 && ok2==1 && ok3==1)
        {
            printf("Alegeti tara in care doriti sejurul.\n");
            printf("Tara cautata: ");
            char s[20];
            scanf("%s",s);
            int x1,x2;
            printf("Alegeti un numarul de nopti minim si maxim.\n");
            printf("Nr. nopti minim: ");
            scanf("%d",&x1);
            printf("\nNr. nopti maxim : ");
            scanf("%d",&x2);
            int y1,y2;
            printf("Alegeti un pret minim si maxim.\n");
            printf("Pret minim: ");
            scanf("%d",&y1);
            printf("\nPret maxim : ");
            scanf("%d",&y2);
            corect(s);

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("%s\n",s);

            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(strcmp(sejur[j].tara,s)==0 &&  sejur[j].nopti>=x1 && sejur[j].nopti<=x2 && sejur[j].pret>=y1 && sejur[j].pret<=y2)
                {
                    z=1;
                    printtara(j,sejur);
                }
            }

        }

        if(ok1==1 && ok2==1 && ok3==0)
        {
            printf("Alegeti tara in care doriti sejurul.\n");
            printf("Tara cautata: ");
            char s[20];
            scanf("%s",s);
            int y1,y2;
            printf("Alegeti un pret minim si maxim.\n");
            printf("Pret minim: ");
            scanf("%d",&y1);
            printf("\nPret maxim : ");
            scanf("%d",&y2);
            corect(s);

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("%s\n",s);
            for(int j=1; j<200; j++)
            {
                if(sejur[j].nr==0)
                    break;
                if(strcmp(sejur[j].tara,s)==0 && sejur[j].pret>=y1 && sejur[j].pret<=y2)
                {
                    z=1;
                    printtara(j,sejur);
                }
            }

        }
    }
    if(z==0)
            {
                printf("Ne pare rau ca nu ati gasit nicio oferta. Puteti cauta iar APASAND 1, sau va puteti intoarce la pagina de pornire APASAND 2.\n");
                int q;
                scanf("%d",q);
                if(q==1)
                    cautare(sejur);
                else
                    antet();
            }
    printf("Doresti sa rezervi una dintre ofertele vazute? APASATI 1 daca da, APASATI 0 daca nu\n");
    scanf("%d",&a);
    if(a==1)
    {
        printf("Care este numarul sejurului ales?\n");
        int b;
        scanf("%d",&b);
        rezervare(b,sejur);
    }
    else
    {
        printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doresti sa cauti alta oferta APASATI 2.\n");
        int b;
        scanf("%d",&b);
        if(b==1)
            antet();
        else
            cautare(sejur);
    }}
}

void confirmare(int p)
{
    printf("Va multumim ca ati rezervat unul din ofertele de sejur de pe site-ul nostru! Codul unic al rezervarii este %d ^-^\n",p);
    printf("Doriti sa va intoarceti la pagina de pornire? APASATI 2 daca da, APASATI 3 daca nu\n");
    int a;
    scanf("%d",&a);
    if(a==2)
        antet();
}

int codunic(p)// nu stiu cum sa fac sa fie codunic mereu
{
    FILE *rez;
    rez=fopen("Rezervari.txt","r");
    char s[100],t[100],*z,sep[2]="/";
    int n=0;
    while(fgets(s,500,rez))
    {}
    if(s[0]>='1' && s[0]<='9')
    {
        n=0;
        strcpy(t,s);
        z=strtok(t,sep);
        for(int i=0; i<strlen(z); i++)
            n=n*10+(z[i]-'0');
    }
    return n+1;
    fclose(rez);
}



void oferta(sejure sejur[])
{
    for(int j=1; j<200; j++)
    {
        if(sejur[j].nr==0)
            break;
        printf("Numar sejur : %d\n",sejur[j].nr);
        printf("Tara sejur: %s\n",sejur[j].tara);
        printf("Cazare la : %s\n",sejur[j].hotel);
        printf("Pret per persoana : %d euro\n",sejur[j].pret);
        printf("Durata sejur : %d nopti\n",sejur[j].nopti);
        printf("Locuri disponibile: %d\n",sejur[j].dis);
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n");
    }
    printf("Doresti sa rezervi una dintre ofertele vazute? APASATI 1 daca da, APASATI 0 daca nu.\n");
    int a;
    scanf("%d",&a);
    if(a==1)
    {
        printf("Care este numarul sejurului ales?\n");
        int b;
        scanf("%d",&b);
        rezervare(b,sejur);
    }
    else
    {
        printf("Daca doresti sa fii trimis la pagina de pornire APASATI 1.\n Daca doresti sa cauti alta oferta APASATI 2.\n");
        int b;
        scanf("%d",&b);
        if(b==1)
            antet();
        else
            cautare(sejur);
    }
}
