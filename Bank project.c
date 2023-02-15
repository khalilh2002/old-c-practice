#include<stdio.h>
#include<string.h>      /*verse a mon accont o cree acnt */
#include<stdlib.h>
typedef struct mailon
{
    double val;
    char nom[20],pass[10];
    struct mailon *suivant;

}mailon;
typedef struct list
{
    mailon *tete;
    mailon *queue;
    int taille ;
}list;
mailon *cree_elemnt(){
    mailon *new;
    new=(mailon*)malloc(sizeof(mailon));
    if (new==NULL)
    {
        printf("error sur cree elment ");
        exit(0);
    }
    new->val=0;
    strcpy(new->nom,"");
    strcpy(new->pass,"");

    new->suivant=NULL;

    return new;
}
list *cree_list(){
    list *l;
    l=(list*)malloc(sizeof(list));
    if (l==NULL)
    {
        printf("error cree list");
        exit(0);
    }
    l->tete=NULL;
    l->queue=NULL;
    l->taille=0;

    return l;
}
mailon *remplire_elment(double n , char name[20] ,char password[10]){
    mailon *new;
    new=cree_elemnt();
    if (new==NULL)
    {
        printf("error sur remplire elment");
        exit(0);
    }
    new->val=n;
    strcpy(new->nom,name);
    strcpy(new->pass,password);

    return new;
}
list *remplire_list(list *l , double n ,char name[20],char password[10] ){
    mailon *new;
    new=remplire_elment(n,name,password);
    if (l->taille==0)
    {
        l->tete=new;
        l->queue=new;
    }else
    {
        l->queue->suivant=new;
        l->queue=new;
    }

    l->taille++;

    return l;
}
void afficher(list *l){
    mailon *courant;
    courant=l->tete;
    if (courant==NULL)
    {
        printf("error list vide / aficcher ");

    }else
    {
        while (courant!=NULL)
        {
            printf("%s %s %lf\n",courant->nom,courant->pass,courant->val);
            courant=courant->suivant;
        }

    }
    free(courant);

}
void copy_list(list *l , FILE *f){
    rewind(f);
    mailon *courant ;
    courant=l->tete;
    if (courant==NULL )
    {
        printf("list vide error");
    }
    while (feof(f)==NULL && (courant != NULL))
    {
        fprintf(f,"%s %s %lf\n",courant->nom,courant->pass,courant->val);
        courant=courant->suivant;
    }
}

int uservrai(FILE *f,char user[20]){
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
double montant(FILE *f ,char name[20]){
    double n;
    char us[20],ps[10];
    rewind(f);
    while (feof(f)==NULL)
    {
        fscanf(f,"%s %s %lf",us,ps,&n);
        if (strcmp(name,us)==0)
        {
            break;
        }
        
    }
    
    return n;
}

int main(){
    FILE *f ;
    char username[20],password[10];
    int x,v;
    double mony=0;
    f=fopen("user_info.txt","r+");
    if (f==NULL)
    {
        printf("error sur ficher");
        exit(0);
    }
    list *l;
    l=cree_list();
    /*new code strat here */
        
        /*while (feof(f)==NULL)
        {
            fscanf(f,"%s %s %lf",username,password,&mony);
            l=remplire_list(l,mony,username,password);
        }
        afficher(l);
        getchar();
        exit(0);
    /*NEW CODE END HERE*/
    printf("creat account (1) ou entrer accont (2) : ");
    scanf("%d",&x);
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

            printf("voir le montant (1) ou transformer (2): ");
            scanf("%d",&v);
            char user2[20],pas2[10];
            if (v==1)
            {
               /* rewind(f);
                double money;
                while (feof(f)==NULL)
                {
                    fscanf(f,"%s %s %lf",user2,pas2,&money);
                    if (strcmp(user2,username)==0)
                    {
                        break;
                    }
                }*/
                printf("le montant est : %lf DH",montant(f,username));

            }else if (v==2)
            {
                double ver,n; //recode versemnt efacer et remplire !!!!!!
                char usr[20];
                int t=0;                
                do/*verfier si username exit*/
                {
                    printf("donne le userame d arrive ");
                    scanf("%s",usr);
                    t=uservrai(f,usr); 
                    if (t==1)
                    {
                        break;
                    }
                    printf("username n'exit pas recrie :********\n ");

                } while (t!=1);
                
                do/*verier le montant exixt dans l'accont*/
                {
                    printf("donnre le montant pour trnsformer : ");
                    scanf("%lf",&ver);
                    if (montant(f,username) >= ver && ver > 0 )
                    {
                        break;
                    }else if (ver > montant(f,username))
                    {
                        printf("le montant de trasnforeme est plus grand \n ton montant:%lf dh\n",montant(f,username));
                    }else
                    {
                        printf("error le nombre est negative , recrire le montat \n");
                    }
                    
                } while ( (ver > montant(f,username)) || (0 > ver) );
                
                rewind(f);
                while (feof(f)==NULL)
                {
                   fscanf(f,"%s %s %lf",user2,pas2,&n);
                   if (strcmp(user2,usr)==0)
                   {
                        l=remplire_list(l,n+ver,user2,pas2);
                   }
                   else if (strcmp(user2,username)==0)
                   {
                        l=remplire_list(l,n-ver,user2,pas2);
                   }
                   else
                   {
                        l=remplire_list(l,n,user2,pas2);
                   }

                }
                //afficher(l);
                copy_list(l,f);
                printf("transformer est complete : \n le montant qui rest  est : %lf DH",montant(f,username));

            }

        }

    }
    return 0;
}
