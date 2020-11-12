#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct login{
    char ime[100];
    char prezime[100];
    char email[100];
    char nickname[100];
    char password[100];
    char password2[100];
    };

int ulogovan = 0;

void registracija()
{
    char c[100];
    int i = 0;
    FILE *f;
    f = fopen("login.txt", "r+");
    for(i = 0; ;i++){
        c[i] = fgetc(f);
        if(c[i] == EOF)
            break;
    }
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
    if(strstr(c, log.email) != NULL){
        printf("Email je vec iskoriscen. \n");
        goto email;
    }


    fputs(log.email,f);
    fprintf(f, "\n");
    nickname:
    printf("Uneti nickname: ");
    scanf("%s", log.nickname);
    if(strstr(c, log.nickname) != NULL){
        printf("Nickname je vec iskoriscen. \n");
        goto nickname;
    }
    fputs(log.nickname,f);
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
    char temp[100], temp2[100], password[100], password2[100], c[100], djubre[100], d;
    FILE *f;
    f = fopen("login.txt", "r+");
    LOGIN:
    printf("Unesite email ili nickname: \n");
    scanf("%s", temp);
    for(i = 0; ; i++){
        fscanf(f, "%s", temp2);
        d=fgetc(f);
        if(d == EOF){
            printf("Uneti email ili nickname ne postoji.\n");
            goto LOGIN;
        }
        if(i == 3){
            fscanf(f, "%s", djubre);
            fseek(f, 1, SEEK_CUR);
            if(strcmp(temp, temp2) == 0)
                break;
            if(strcmp(temp, djubre) == 0)
                break;
        }
        if(i == 5)
            i = 0;
    }
    fscanf(f, "%s", password2);
    printf("%s", password2);
    SIFRA:
    printf("Unesite sifru: \n");
    scanf("%s", password);
    if(strcmp(password, temp2) != 0){
        printf("Uneta sifra nije tacna. \n");
        goto SIFRA;
    }

    fclose(f);
    ulogovan = 1;
    meni();
}

void izmena(){}
void brisanje(){}
void logout()
{
    ulogovan = 0;
    printf("Izlogovali ste se.");
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
        printf("1.Izmena naloga\n2.Brisanje naloga\n3.Logout\n4.Gasenje programa");
        scanf("%d", &a);
        if(a == 1)
            izmena();
        else if(a == 2)
            brisanje();
        else if(a == 3)
            logout();
        else if(a == 4)
            return 0;
        else{
            printf("Uneli ste neposotojecu komandu");
            return 0;
        }
    }
}

int main()
{
    meni();
    return 0;
}
