/*A Pranav Srinivasa PROJECT*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
/*7746*/
int MAXSIZE=100;
int MAXSIZE2=100;
double *amount_trans;
double *date_trans;
int top1=-1,top2=-1;
int j=0;
struct details
{
   char name[100];
   double phno;
   char email[200];
};

void push(double *s,int *top,double item)
{
    if(top1==(MAXSIZE-1))
    {
        s=(double *)realloc(s,(MAXSIZE*10)*sizeof(double));
        MAXSIZE=MAXSIZE*10;
    }
    *top=*top+1;
    s[*top]=item;    
}
int trans_history()
{
    // we need to take input of transactions input from client and store and display it
    
    int flag=0,i=0,choice;
    double sum=0.0;
    double date_trans_val=0.0;
    double amount_trans_val=0.0;
    while (flag!=1)
    {   
    trans_label :
        printf("Enter Your Choice :\t 1.Input data ,2.Display,3.EXIT Transaction history\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 3:
                flag=1;
                break;
            case 1:
                printf("Enter the amount transfered:\n");
                scanf("%lf",&amount_trans_val);
                push(amount_trans,&top1,amount_trans_val);
                sum+=amount_trans[top1];
                printf("Enter the date of transaction in DDMMYYYY form:\n");
                scanf("%lf",&date_trans_val);
                push(date_trans,&top2,date_trans_val);
                break;

            case 2:
                for(i=0;i<=top1;i++)
                {   
                    if(amount_trans[i]>0){
                        printf("%lf was debited and sent on %lf\n",amount_trans[i],date_trans[i]);
                    }
                    if(amount_trans[i]<0){
                        printf("%lf was credited and on %lf\n",amount_trans[i],date_trans[i]);
                    }
                }
                printf("The NET of the transaction is : %lf\n",sum);
                break;

            default:printf("invalid input, please enter valid input\n");
                goto trans_label;
                break;
        }
    
    }
    return sum;
}

int stock_predict()
{   
    int n,i,j;
    char Yes_No;
    double amt_invested;
    double *data_X;
    double *data_Y;
    double smoothing_constant=0.20,beta=0.30;
    double *f;
    double af;
    double *t;
    data_X=(double *)malloc(MAXSIZE*sizeof(double));
    data_Y=(double *)malloc(MAXSIZE*sizeof(double));
    f=(double *)malloc(MAXSIZE*sizeof(double));
    t=(double *)malloc(MAXSIZE*sizeof(double));
    printf("Enter the number of data points\n");
    scanf("%d",&n);
    if(n>MAXSIZE)
    {
        data_X=(double *)realloc(data_X,(MAXSIZE+n)*sizeof(double));
        data_Y=(double *)realloc(data_Y,(MAXSIZE+n)*sizeof(double));
        MAXSIZE=MAXSIZE+n;
    }
    for(i=0;i<n;i++)
    {
        printf("Enter the %d x data points\n",i);
        scanf("%lf",&data_X[i]);
        printf("Enter the %d Y data points\n",i);
        scanf("%lf",&data_Y[i]);
    }
    f[0]=data_Y[0];
    t[0]=((data_Y[1]-data_Y[0])+(data_Y[3]-data_Y[2]))/2;
    for(i=1;i<=n;i++)
    {   
        
        f[i]=f[i-1]+(smoothing_constant*(data_Y[i-1]-f[i-1]));
        t[i]=beta*(f[i]-f[i-1])+(1-beta)*t[i-1];
    }
    af=f[n]+t[n]*(n+1);
    printf("The Y value for %d X value is %lf\n",n,af);
    if (af>data_Y[n])
    {
        printf("The market currently is in a good place to invest\n");
        
    }
    else if(af=data_Y[n])
    {
        printf("The market currently is in a volatile state it is better to wait\n");
        
    }
    else
    {
    printf("It is not adviced to invest looking at the current data\n");
    }
yesnolabel :
    printf("Please Enter if you have decided to Invest Y/N ; Y for yes , N for no\n");
    scanf("%c",&Yes_No);
    switch(Yes_No)
    {
        case 'Y': printf("Enter the amount invested\n");
            scanf("%lf",&amt_invested);
            return amt_invested;
            break ;
        case 'N':printf("Thanks for your input\n");
            return -1;
            break ;
        default:printf("Enter Valid input (Y/N)\n");
            goto yesnolabel;
            break;

    }
}
int loan(double *sum)
{   system("cls");
    double p,r,CI=0,temp,amtpaid,dt_amtpaid,goal_dt,dt_diff,amt_div;
    int t,n;
    char tperiod[50];
    char opt;
    printf("\nEnter the Principal Loan amount : \n");
    scanf("%lf",&p);
    printf("\nEnter the interest rate:\n");
    scanf("%lf",&r);
    printf("\nEnter the type of time period (Eg: Years,Months,Weeks,etc.,) :\n");
    scanf("%s",tperiod);
    printf("\nEnter the number of time periods elapsed:\n");
    scanf("%d",&t);
    printf("\nEnter the number of times interest applied per %s\n",tperiod);
    scanf("%d",&n);
    CI=p*pow((1+(r/n)),(n*t));
Cmpdintrst :
    printf("\nThe the final amount payable at the end of %d %s is :\n%lf",t,tperiod,CI);
    printf("\nThe Interest Money is : %lf\n",(CI-p));
    printf("\nHas the interest rate changed Y/N :\n");
    scanf(" %c",&opt);
    switch(opt)
    {
        case 'Y':   printf("\nEnter the NEW interest rate:\n");
            scanf("%lf",&r);
            printf("\nEnter the number of time periods elapsed:\n");
            scanf("%d",&t);
            printf("\nEnter the number of times interest applied per %s\n",tperiod);
            scanf("%d",&n);
            CI=CI+p*pow((1+(r/n)),(n*t));
            goto Cmpdintrst;
        case 'N':   break ;

    }
    printf("\nInput the amount paid\n");
    scanf("%lf",&amtpaid);
    temp=amtpaid*(-1);
    push(amount_trans,&top1,temp);
    printf("\nEnter the %s when the last payment was done :\n",tperiod);
    scanf("%lf",&dt_amtpaid);
    push(date_trans,&top2,dt_amtpaid);
    printf("Enter the goal %s to finish payments\n",tperiod);
    scanf("%lf",&goal_dt);
    dt_diff=goal_dt-dt_amtpaid;
    amt_div=(CI-amtpaid)/dt_diff;
    printf("\n%lf amount needs to be paid every %s to end the loan in %lf %s\n",amt_div,tperiod,dt_diff,tperiod);
    *sum=*sum-amtpaid;
    getch();
}
void main()
{   
    amount_trans=(double *)malloc(MAXSIZE*sizeof(double));
    if(amount_trans==NULL)
    {
        printf("stack creation failed\n");
        exit(0);
    }
    date_trans=(double *)malloc(MAXSIZE2*sizeof(double));
    if(date_trans==NULL)
    {
        printf("stack creation failed\n");
        exit(0);
    }
    int user_type,i,choice2,flag1=0,comp_res,comp_res2; 
    double sum,amt_invest;
    char name[100],name2[100],new_username[100],new_password[100],comp_password[100],username[200],new_username2[100],txt[5],comp_username[200],increment[10]; 
    char username_dup[100];
    struct details d;
    strcpy(txt,".txt");
    strcpy(increment,"_file.txt");
label:
    system("cls");
    printf("Are you a old user or a new user:\n");
    printf("1.Old User\n2.New User\n");
    scanf("%d",&user_type);
    switch (user_type)
    {
    case 2: 
            system("cls");
            printf("\nEnter New username :\n");
            scanf("%s",new_username);
            strcpy(new_username2,new_username);
            printf("\nEnter New Password :\n");
            scanf("%s",new_password);
        pass_verify:
            printf("\nConfirm New Password :\n");
            scanf("%s",comp_password);
            comp_res=strcmp(new_password,comp_password);
            
            if(comp_res==0)
            {   
                strcat(new_username2,new_password);
                strcat(new_username2,txt);
                printf("%s",new_username2);
                FILE *fptr3;
                fptr3=fopen(new_username2,"w");
                fprintf(fptr3,"%s",new_username);
                fprintf(fptr3,"%s",new_password);
                fclose(fptr3);
                strcpy(name,new_username);
                strcat(name,new_password);
                strcat(name,increment);
            }
            else
            {
                printf("Password doesnt match\n");
                goto pass_verify;
            }
            FILE *fptr;
            fptr = fopen(name, "w"); 
            if(fptr == NULL) 
            { 
                printf("Could not create file. Maybe locked or being used by another application?\n"); 
                exit(-1); 
            } 
            system("cls");
            printf("\nEnter your Name\n");
            scanf("%s",&d.name);
            printf("\nEnter your contact number:\n");
            scanf("%lf",&d.phno);
            printf("\nEnter your email address:\n");
            scanf("%s",&d.email);
            fprintf(fptr,"\nUSER DETAILS:\nUser's Name : %s\n User's Contact No. : %lf\n Users's Email address :%s\n",d.name,d.phno,d.email);
            fprintf(fptr,"NEW ENTRY :\n");
            system("cls");
            while(flag1!=-1)
            {   
                system("cls");
                printf("\nEnter your option :\n\t[1].Transaction History Input\n\t[2].Stock Prediction\n\t[3]Loan Calculator\n\t[4]Exit");
                scanf("%d",&choice2);
                system("cls");
                switch(choice2)
                {
                    case 1:sum=trans_history();
                        break;
                    case 2:      
                        amt_invest=stock_predict();
                        if(amt_invest!=-1)
                        {
                            fprintf(fptr,"%lf was invested\n",amt_invest);
                        }
                        break;
                    case 3:loan(&sum);
                        break;
                    case 4:flag1=-1;
                        break; 
                } 
            }
            
            for(i=0;i<=top1;i++)
            {   if(amount_trans[i]!=0)
                {
                    if(amount_trans[i]>0)
                    {
                        fprintf(fptr,"%lf was debited and sent on %lf  \n",amount_trans[i],date_trans[i]);
                    }
                    if(amount_trans[i]<0)
                    {
                        fprintf(fptr,"%lf was credited on %lf \n",amount_trans[i],date_trans[i]);
                    }
                }
            }
            if(sum!=0)
            {
                fprintf(fptr,"The NET of the transaction is : %lf\n",sum);
            }
            fclose(fptr);
            break;
    case 1:
        validating:
            printf("Enter Username and password without spaces:\n");
            scanf("%s",username);
            strcpy(username_dup,username);
            strcat(username,txt);
            FILE *fptr4;
            fptr4 = fopen(username,"r");
            fscanf(fptr4,"%s",comp_username);
            strcat(comp_username,txt);
            comp_res2=strcmp(comp_username,username);
            if(comp_res2==0)
            {   
                printf("Valid Username and password\n");
                goto validated;
            }
            else
            {
                printf("INVALID USERNAME AND PASSWORD\n");
                goto validating;
            }
            fclose(fptr4);
        validated:
            strcpy(name2,username_dup);
            strcat(name2,increment);
            printf("Detials in the file are :\n");
            FILE *fptr2;
            fptr2 = fopen(name2,"r");
             if(fptr2 == NULL) 
            { 
                printf("File not found\n"); 
                goto label;
            } 
            char c;
             c = fgetc(fptr2);
            while (c != EOF)
            {
                printf ("%c", c);
                c = fgetc(fptr2);
            }
            fclose(fptr2);
            break;
    default:
        printf("Please Enter valid input\n");
        goto label;   
        
    }
                    
    free(amount_trans);
    free(date_trans);
  
}