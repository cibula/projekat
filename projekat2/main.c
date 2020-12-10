#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct login{
    char ime[100];
    char prezime[100];
    char email[100];
    char nickname[100];
    char password[100];
    char password2[100];
    };

struct video{
    char naziv;
    char kreator;
    char link;
    int pregledi;
    int lajkovi;
    int dislajkovi;
    int komentari;
};

char temp[100];
int ulogovan = 0;
int DaLiJeMail = 0;
struct login trenutnoUlogovan;

void registracija()
{
    char d, temp[100], temp2[100], djubre[100], c[100];
    int i, j, a = 0;
    FILE *f;
    f = fopen("login.txt", "r+");
    fseek(f, 0, SEEK_END);
    struct login log;
    printf("Uneti ime: ");
    scanf("%s", log.ime);
    fputs(log.ime,f);
    fprintf(f, "\n");
    printf("Uneti prezime: ");
    scanf("%s", log.prezime);
    fputs(log.prezime,f);
    fprintf(f, "\n");
    email:
    printf("Uneti email: ");
    scanf("%s", log.email);
    for(i = 0; log.email[i] != '\0'; i++){
        if(log.email[i] == '@'){
            a++;
            break;
        }
    }
    for(j = i; j < strlen(log.email) ; j++){
            if(log.email[j] == '.'){
                a++;
                break;
            }
    }
    if(a < 2){
        printf("Email mora imati barem jedan @ i jednu tacku posle. Uneti ponovo \n");
        goto email;
    }
    fseek(f, 0, SEEK_SET);
    for(i = 0; ; i++){
        if(i == 5)
            i = 0;
        fscanf(f, "%s", temp2);
        d = fgetc(f);
        if(d == EOF){
            fputs(log.email,f);
            break;
        }
        if(i == 2){
            if(strcmp(log.email, temp2) == 0){
                printf("Uneti email je vec iskoriscen. Uneti ponovo. \n");
                goto email;
            }
        }
    }
    fprintf(f, "\n");
    nickname:
    printf("Uneti nickname: ");
    scanf("%s", log.nickname);
    fseek(f, 0, SEEK_SET);
    for(i = 0; ; i++){
        if(i == 5)
            i = 0;
        fscanf(f, "%s", temp2);
        d = fgetc(f);
        if(d == EOF){
            fputs(log.nickname,f);
            break;
        }
        if(i == 3){
            if(strcmp(log.nickname, temp2) == 0){
                printf("Uneti nickname je vec iskoriscen. Uneti ponovo. \n");
                goto nickname;
            }
        }
    }
    fprintf(f, "\n");
    printf("Uneti password: ");
    scanf("%s", log.password);
    printf("Ponovo uneti password: ");
    scanf("%s", log.password2);
    while(strcmp(log.password, log.password2) != 0){
        printf("Passwordi se ne poklapaju. \n");
        printf("Uneti password: ");
        scanf("%s", log.password);
        printf("Ponovo uneti password: ");
        scanf("%s", log.password2);
    }
    fputs(log.password,f);
    fprintf(f, "\n");
    fclose(f);
    ulogovan = 1;
    meni();
}

void login()
{
    int i;
    struct login log;
    char temp2[100], password[100], password2[100], c[100], djubre[100], d;
    FILE *f;
    f = fopen("login.txt", "r+");
    LOGIN:
    printf("Unesite email ili nickname: \n");
    scanf("%s", temp);
    fseek(f, 0, SEEK_SET);
    for(i = 0; ; i++){
        fscanf(f, "%s", temp2);
        d = fgetc(f);
        if(d == EOF){
            printf("Uneti email ili nickname ne postoji.\n");
            goto LOGIN;
        }
        if(i == 2){
            fscanf(f, "%s", djubre);
            fseek(f, 1, SEEK_CUR);
            if(strcmp(temp, temp2) == 0){
                DaLiJeMail++;
                break;
            }
            if(strcmp(temp, djubre) == 0)
                break;
        }
        if(i == 4)
            i = 0;
    }
    fscanf(f, "%s", password2);
    SIFRA:
    printf("Unesite sifru: \n");
    scanf("%s", password);
    if(strcmp(password, password2) != 0){
        printf("Uneta sifra nije tacna. \n");
        goto SIFRA;
    }


    strcpy(trenutnoUlogovan.password, password);
    strcpy(trenutnoUlogovan.nickname, djubre);
    strcpy(trenutnoUlogovan.email, temp2);

    fclose(f);
    ulogovan = 1;
    meni();
}

void izmena()
{
    FILE *f = fopen("login.txt", "r");
    FILE *fp = fopen("privremeni.txt", "w+");
    int i, k, g, j = 1, a = 0;
    struct login log;
    char temp2[100], temp3[100], d;
    for(i = 0; ;i++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(strcmp(temp, temp2) == 0)
                break;
        }
    fseek(f, 0, SEEK_SET);
    if(DaLiJeMail == 0){
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j == i - 3){
                printf("Uneti ime: \n");
                scanf("%s", log.ime);
                fputs(log.ime, fp);
                fprintf(fp, "\n");
            }else if(j == i - 2){
                printf("Uneti prezime: \n");
                scanf("%s", log.prezime);
                fputs(log.prezime, fp);
                fprintf(fp, "\n");
            }else if(j == i - 1){
                printf("Uneti email: \n");
                scanf("%s", log.email);
                fputs(log.email, fp);
                fprintf(fp, "\n");
            }else if(j == i){
                printf("Uneti nickname: \n");
                scanf("%s", log.nickname);
                fputs(log.nickname, fp);
                fprintf(fp, "\n");
            }else if(j == i + 1){
                printf("Uneti password: \n");
                scanf("%s", log.password);
                fputs(log.password, fp);
                fprintf(fp, "\n");
            }else{
                fprintf(fp, "%s", temp2);
                fprintf(fp, "\n");
                }
            }
    }else{
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j == i - 2){
                printf("Uneti ime: \n");
                scanf("%s", log.ime);
                fputs(log.ime, fp);
                fprintf(fp, "\n");
            }else if(j == i - 1){
                printf("Uneti prezime: \n");
                scanf("%s", log.prezime);
                fputs(log.prezime, fp);
                fprintf(fp, "\n");
            }else if(j == i){
                printf("Uneti email: \n");
                scanf("%s", log.email);
                fputs(log.email, fp);
                fprintf(fp, "\n");
            }else if(j == i + 1){
                printf("Uneti nickname: \n");
                scanf("%s", log.nickname);
                fputs(log.nickname, fp);
                fprintf(fp, "\n");
            }else if(j == i + 2){
                printf("Uneti password: \n");
                scanf("%s", log.password);
                fputs(log.password, fp);
                fprintf(fp, "\n");
            }else{
                fprintf(fp, "%s", temp2);
                fprintf(fp, "\n");
                }
            }
        }
    fclose(f);
    fclose(fp);
    remove("login.txt");
    rename("privremeni.txt", "login.txt");
    meni();

}

void brisanje()
{
    FILE *f = fopen("login.txt", "r");
    FILE *fp = fopen("privremeni.txt", "w+");
    int i, k, j;
    char temp2[100], d;
    for(i = 0; ;i++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(strcmp(temp, temp2) == 0)
                break;
        }
    fseek(f, 0, SEEK_SET);
    if(DaLiJeMail == 0){
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j >= i - 3 && j <= i + 1)
                continue;
            fprintf(fp, "%s", temp2);
            fprintf(fp, "\n");
        }
    }else{
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j >= i - 2 && j <= i + 2)
                continue;
            fprintf(fp, "%s", temp2);
            fprintf(fp, "\n");
        }
    }
    fclose(f);
    fclose(fp);
    remove("login.txt");
    rename("privremeni.txt", "login.txt");
    ulogovan = 0;
    meni();

}

void logout()
{
    ulogovan = 0;
    printf("Izlogovali ste se.\n");
    meni();
}

void meni()
{
    int a;
    if(ulogovan == 0){
        printf("1.Register\n2.Login\n3.Gasenje programa\n");
        scanf("%d", &a);
        if(a == 1){
            registracija();
        }else if(a == 2){
            login();
        }else if(a == 3){
            return 0;
        }else{
            printf("Uneli ste neposotojecu komandu");
            return 0;
        }
    }else{
        printf("1.Izmena naloga\n2.Brisanje naloga\n3.Logout\n4.Meni 2\n5.Gasenje programa\n");
        scanf("%d", &a);
        if(a == 1)
            izmena();
        else if(a == 2)
            brisanje();
        else if(a == 3)
            logout();
        else if(a == 4)
            meni2();
        else if(a == 5)
            return 0;
        else{
            printf("Uneli ste neposotojecu komandu");
            return 0;
        }
    }
}

void dodavanjeVidea()
{
    time_t t;
    char naziv[100], link[6], random, d, temp2[100];
    int i;
    struct video video;
    video.pregledi = 0;
    video.lajkovi = 0;
    video.dislajkovi = 0;
    video.komentari = 0;
    FILE *f, *fp;
    f = fopen("video.txt", "a+");
    fp = fopen("login.txt", "r");
    printf("Uneti naziv videa: ");
    scanf("%s", naziv);
    fprintf(f, "%s", naziv);
    fflush(stdin);
    fprintf(f, "\n");
    fprintf(f, "%s", trenutnoUlogovan.nickname);
    fprintf(f, "\n");
    srand((char)time(&t));

    for(i = 0; i < 5; i++)
    {
        random = (rand() % 75) + 48;
        while((random > 90 && random < 97) || (random > 57 && random < 65))
        {
            random = (rand() % 75) + 48;
        }
        link[i] = random;
    }
        fprintf(f, "%s", link);
        fprintf(f, "\n");
        fprintf(f, "%d", video.pregledi);
        fprintf(f, "\n");
        fprintf(f, "%d", video.lajkovi);
        fprintf(f, "\n");
        fprintf(f, "%d", video.dislajkovi);
        fprintf(f, "\n");
        fprintf(f, "%d", video.komentari);
        fprintf(f, "\n");
    fclose(f);
    fclose(fp);

}
void izmenaVidea()
{
    FILE *f, *fp;
    f = fopen("video.txt", "r");
    fp = fopen("privremeni video.txt", "w+");
    char temp2[100];
    int i, j;
    for(i = 0; ;i++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(strcmp(temp, temp2) == 0)
                break;
        }
        fseek(f, 0, SEEK_SET);
    if(DaLiJeMail == 0){
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j >= i - 3 && j <= i + 1)
                continue;
            fprintf(fp, "%s", temp2);
            fprintf(fp, "\n");
        }
    }else{
        for(j = 0; ;j++){
            fscanf(f, "%s", temp2);
            if(feof(f))
                break;
            if(j >= i - 2 && j <= i + 2)
                continue;
            fprintf(fp, "%s", temp2);
            fprintf(fp, "\n");
        }
    }
}
void brisanjeVidea()
{
    FILE *f, *fp;
    f = fopen("video.txt", "r");
    fp = fopen("privremeni video.txt", "w+");
    int i, j;
    char temp2[100], temp3[100], naziv[100], d;
    printf("Uneti naziv videa: ");
    fflush(stdin);
    scanf("%s", naziv);
    for(i = 0; ; i ++){
        fscanf(f, "%s", temp2);
        d = fgetc(f);
        if(d == EOF)
            break;
        if(strcmp(naziv, temp2) == 0){
            break;
        }
    }
    printf("%d", i);
    for(j = 0; j <= i ; j ++){
        fscanf(f, "%s", temp3);
        d = fgetc(f);
        if(d == EOF)
            break;
        fprintf(fp, "%s", temp3);
        fprintf(fp, "\n");
    }
    printf("%d", j);
    for(j += 7; ; j++){
        fscanf(f, "%s", temp3);
        d = fgetc(f);
        if(d == EOF)
            break;
        fprintf(fp, "%s", temp3);
        fprintf(fp, "\n");
    }
    fclose(f);
    fclose(fp);
    remove("video.txt");
    rename("privremeni video.txt", "video.txt");
}
void homePage()
{
    int i, j, d, brojVidea;
    struct video niz[100];
    FILE *f;
    f = fopen("video.txt", "r");
    for(i = 0; ; i ++){
        if(d == EOF)
            break;
        fscanf(f, "%s", niz[i].naziv);
        fgetc(f);
        fscanf(f, "%s", niz[i].kreator);
        fgetc(f);
        fscanf(f, "%s", niz[i].link);
        fgetc(f);
        fscanf(f, "%s", niz[i].pregledi);
        fgetc(f);
        fscanf(f, "%s", niz[i].lajkovi);
        fgetc(f);
        fscanf(f, "%s", niz[i].dislajkovi);
        fgetc(f);
        fscanf(f, "%s", niz[i].komentari);
        d = fgetc(f);
    }
    brojVidea = i - 1;
    printf("Home Page: \n");
    for(i = 0; i < brojVidea; i++){
        printf("\t%d. %s\n", i + 1 , niz[i].naziv);
    }
    printf("Izaberite video: ");
    scanf("%d", j);
    j--;
    gledanjeVidea(j, f, niz);
}
void pretragaVidea()
{
    char naziv[100];
    printf("Uneti ime videa: ");
    scanf("%s", naziv);
}
void gledanjeVidea(int j, FILE *f, struct video *niz)
{
    f = fopen("video.txt", "w");
    int a, i;
    niz[j].pregledi++;
    printf("1.Lajk\n2.Dislajk\n3.Komentari");
    scanf("%d", a);
    if(a == 1){
        niz[j].lajkovi++;
    }else if(a == 2){
        niz[j].dislajkovi++;
    }else if(a == 3){
        niz[j].komentari++;
    }else{
        printf("Uneli ste nepostojecu komandu!");
    }
    for(i = 0; ; i++){
        fprintf(f, "%s", niz[i].naziv);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].kreator);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].link);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].pregledi);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].lajkovi);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].dislajkovi);
        fprintf(f, "\n");
        fprintf(f, "%s", niz[i].komentari);
        fprintf(f, "\n");
    }
}

void meni2()
{
        int j;
        FILE *f;
        struct video niz[100];
    int a;
    do
    {
        printf("1.Dodavanje videa\n2.Izmena videa\n3.Brisanje videa\n4.Home page\n5.Pretraga videa\n6.Gledanje videa\n7.Meni 1\n8.Gasenje programa\n");
        scanf("%d", &a);
        if(a == 1)
            dodavanjeVidea();
        else if(a == 2)
            izmenaVidea();
        else if(a == 3)
            brisanjeVidea();
        else if(a == 4)
            homePage();
        else if(a == 5)
            pretragaVidea();
        else if(a == 6)
            gledanjeVidea(j, f, niz);
        else if(a == 7)
            meni();
        else if(a == 8)
            return 0;
        else{
            printf("Uneli ste neposotojecu komandu");
            return 0;
        }
    }while(a != 7);
}

int main()
{
    meni();
    return 0;
}
