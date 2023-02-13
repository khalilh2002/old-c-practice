#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int uservrai(FILE *f,char user[20]){//probleme recode
    int n,t;
    double pr;
    t=0;
    char user2[20],bin[10];
    rewind(f);
    while(feof(f)==NULL){
        fscanf(f,"%s %s %lf",&user2,&bin,&pr);
        n=strcmp(user2,user);
        if(n==0){
           t=1;
           break;
        }
    }//1 exit 0 n exit pas
    return t;
}
int main(){
    FILE *f ;
    char username[20],password[10];
    int x,v;
    double mony=0;
    printf("creat account (1) ou entrer accont (2) : ");
    scanf("%d",&x);
    f=fopen("user_info.txt","r+");
    if (f==NULL)
    {
        printf("error sur ficher");
        exit(0);
    }
    if(x==1){
       do{
            printf("username : ");
            scanf("%s",&username);
            printf("password : ");
            scanf("%s",&password);
            v=uservrai(f,username);
        }while(v==1);
        f=fopen("user_info.txt","a+");
        fprintf(f,"%s %s %lf\n",username,password,mony);
    }else{
        if(x==2){
       do{
            printf("username : ");
            scanf("%s",&username);
            printf("password : ");
            scanf("%s",&password);
            v=uservrai(f,username);
            if(v==0){
                printf("\n username n'exist pas,\n essayer a nouveau\n\n");
            }
        }while(v==0);

            printf("voir le montant (1) ou verser (2): ");
            scanf("%d",&v);
            char user2[20],pas2[10];
            if (v==1)
            {
                rewind(f);
                double money;

                while (feof(f)==NULL)
                {
                    fscanf(f,"%s %s %lf",user2,pas2,&money);
                    if (strcmp(user2,username)==0)
                    {
                        break;
                    }

                }
                printf("le montant est : %lf DH",money);


            }else if (v==2)
            {
                double ver,n; //recode versemnt efacer et remplire !!!!!!
                printf("donnre le montant pour verser : ");
                scanf("%lf",&ver);
                printf("donne le userame ");
                scanf("%s",username);
                while (feof(f)==NULL)
                {
                    fscanf(f,"%s %s %lf",user2,pas2,&n);
                    if (strcmp(user2,username)==0)
                    {
                        break;
                    }

                }
                fseek(f,-1L,SEEK_CUR);
                fprintf(f,"%s %s %lf",user2,pas2,ver);

            }




        }

    }
    return 0;
}
