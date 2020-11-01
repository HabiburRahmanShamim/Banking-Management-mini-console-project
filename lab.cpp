#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>

FILE *fp, *ff;
// Set Delay
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
// Account Data Structure
struct node
{
    char name[20], birthday[20], address[20], today[20], age[3], nid[20], phone[15];
    int acnum;
    float amount;
    struct node *next, *prev;
}*nptr,*start, *last, *tptr;
// Hidden Method. Only for admin
void clearDatabase()
{
    fp = fopen("data_record.txt", "w");
    ff = fopen("countId.txt", "w");
    fprintf(ff, "0");
    fclose(ff);
    fclose(fp);
}
// Make a list of bank user's
void list_init()
{
    // Checking number of records are valid
    ff = fopen("data_record.txt", "r");
    start = NULL;
    fseek(ff, 0, SEEK_SET);
    int lines = 0;
    while (!feof(ff))
    {
        char c = fgetc(ff);
        if(c == '\n')lines++;
    }
    if(lines == 0 || lines%9 != 0)
    {
        printf("\n\t\tImproper Data In List\n");
        fclose(ff);
        return;
    }
    fclose(ff);
    // Scanning records
    fp = fopen("data_record.txt", "r");
    while(!feof(fp))
    {
        nptr = new(node);
        nptr->next = NULL;
        nptr->prev = NULL;
        // fscanf(fp, "%d %s %s %s %s %s %s %f %s\n", &nptr->acnum, nptr->name, nptr->birthday, nptr->age, nptr->address, nptr->nid, nptr->phone, &nptr->amount, nptr->today);
        fscanf(fp, "%d\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%f\n%[^\n]%*c\n", &nptr->acnum, nptr->name, nptr->birthday, nptr->age, nptr->address, nptr->nid, nptr->phone, &nptr->amount, nptr->today);
        if(start == NULL)
        {
            start = nptr;
            last = start;
        }
        else
        {
            last->next = nptr;
            nptr->prev = last;
            last = last->next;
        }
    }
    fclose(fp);
}
// Write account's info on file
void make_file()
{
    // list_init();
    fp = fopen("data_record.txt", "w");
    tptr = start;
    while(tptr!=NULL)
    {
        // fprintf(fp, "%d %s %s %s %s %s %s %f %s\n", tptr->acnum, tptr->name, tptr->birthday, tptr->age, tptr->address, tptr->nid, tptr->phone, tptr->amount, tptr->today);
        fprintf(fp, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n%s\n", tptr->acnum, tptr->name, tptr->birthday, tptr->age, tptr->address, tptr->nid, tptr->phone, tptr->amount, tptr->today);

        tptr = tptr->next;
    }
    fclose(fp);
}
// Display account info
void display()
{
    list_init();
    tptr = start;
    if(tptr == NULL){printf("\n\t\tAccount List Is Empty\n");}
    else 
    {
        // system("CLS");
        printf("\n\n\t\t\t\t\t\t\t\tUser Account List\n");
        int cnt = 1;
        printf("\t\t%2s  %10s %20s %12s %5s %15s %12s %14s %15s\n", "#", "ACC No", "Name", "DOB", "Age", "Address", "NID", "Phone", "Balance");
        while(tptr!=NULL)
        {
            printf("\t\t%2d. %10d %20s %12s %5s %15s %12s %14s %15.3f\n", cnt++, tptr->acnum, tptr->name, tptr->birthday, tptr->age, tptr->address, tptr->nid, tptr->phone, tptr->amount);
            tptr = tptr->next;
        }
    }
}
// Create a record and write it on file
int create_new()
{
    char user[30], bday[20], addr[40], tday[20], agee[3], idn[20], mobile[15];
    int id;
    float bdt;
    int valid = 0;
    printf("\n\t\t\t\t\t|||||ADD RECORDS|||||\n\n");
    printf("\t\tEnter today's date:");
    getchar();
    // if(scanf("%[^\n]%*c", tday))valid++;
    scanf("%[^\n]%*c", tday);
    // printf("\n\t\tEnter the account number:");
    // scanf("%d", &id);
    // getchar();
    printf("\n\t\tEnter the name:");
    scanf("%[^\n]%*c", user);
    // getchar();
    printf("\n\t\tEnter the date of birth(dd/mm/yy):");
    scanf("%[^\n]%*c", bday);
    // getchar();
    printf("\n\t\tEnter the age:");
    scanf("%[^\n]%*c", agee);
    // getchar();
    printf("\n\t\tEnter the address:");
    scanf("%[^\n]%*c", addr);
    // getchar();
    printf("\n\t\tEnter the NID number:");
    scanf("%[^\n]%*c", idn);
    // getchar();
    printf("\n\t\tEnter the phone number:");
    scanf("%[^\n]%*c", mobile);
    printf("\n\t\tEnter the amount:BDT ");
    scanf("%f", &bdt);
    printf("\n\n\t\tAccount created successfully...\n\n");


    fp = fopen("data_record.txt", "a");
    ff = fopen("countId.txt", "r");
    // Taking the value of max current id from file
    fscanf(ff, "%d", &id);
    // Increasing value of ID
    id += 1;
    // fprintf(fp, "%d %s %s %s %s %s %s %f %s\n", id, user, bday, agee, addr, idn, mobile, bdt, tday);
    fprintf(fp, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n%s\n", id, user, bday, agee, addr, idn, mobile, bdt, tday);
    fclose(fp);
    fclose(ff);
    // Writing updated Id value
    fp = fopen("countId.txt", "w");
    fprintf(fp, "%d", id);
    fclose(fp);

    printf("\t\tEnter 1 to go to the main menu and 0 to exit:");
    int t;
    scanf("%d", &t);
    return t;
}
// Change Account Info (Only Address and Contact No)
bool changeinfo_2()
{
    list_init();
    printf("Enter the account no. of the customer whose info you want to change:");
    int n;
    scanf("%d", &n);
    int c;
    if(start == NULL){
        printf("Data List Empty");
        goto END;
    }
    else
    {
        tptr = start;
        while(tptr!=NULL)
        {
            if(tptr->acnum == n)
            {
                printf("Welcome %s, Which information do you want to change:\n1.Address\n2.Phone\n\n", tptr->name);
                printf("Enter your choice(1 for address and 2 for phone):");
                int choice;
                scanf("%d", &choice);
                char addr[40], mobile[15];
                if(choice == 1)
                {
                    system("CLS");
                    printf("Enter the new address:");
                    scanf("%s", addr);
                    strcpy(tptr->address, addr);
                    printf("Change saved...\n\n");
                }
                else
                {
                    system("CLS");
                    printf("Enter the new phone number:");
                    scanf("%s", mobile);
                    strcpy(tptr->phone, mobile);
                    printf("Change saved...\n\n");
                }
                goto END;
            }
            tptr = tptr->next;
        }
    }
    if(tptr == NULL)
    {
        printf("\nData not found...");
        printf("\n\n\nEnter 2 to try again, 1 to go to the menu, 0 to exit:");
        scanf("%d", &c);
        if(c == 2){
            system("CLS");
            changeinfo_2();
        }
    }
    END:
        make_file();
        printf("\nEnter 1 to go to the menu and 0 to exit:");
        scanf("%d", &c);
    return c;
}
// Money Transaction
int transation_3()
{
    list_init();
    printf("\t\tEnter the account no. of the customer:");
    int ac, c, found = 0;
    scanf("%d", &ac);
    tptr = start;
    while(tptr!=NULL)
    {
        if(tptr->acnum == ac)
        {
            printf("\n\n\t\tWeelcome %s, Do you want to:\n\t\t1.Deposit\n\t\t2.Withdraw?\n\n\t\tEnter your choice(1 for deposit 2 for withdraw):", tptr->name);
            int choice;
            scanf("%d", &choice);
            found = 1;
            if(choice == 1)
            {
                printf("\n\t\tEnter the amount you want to deposit (BDT): ");
                float amo;
                scanf("%f", &amo);
                tptr->amount+=amo;
                printf("\n\n\t\tDeposit successful..");
                break;
            }
            else if(choice == 2)
            {
                printf("\n\t\tEnter the amount you want to withdraw (BDT): ");
                float witd;
                scanf("%f", &witd);
                while (witd > tptr->amount)
                {
                    printf("\n\t\t\tInsufficient Account!!!\n");
                    printf("\n\t\tEnter the amount you want to withdraw (BDT): ");
                    scanf("%f", &witd);
                }
                
                tptr->amount -= witd;
                printf("\n\n\t\tWithdrawal Successful..");
                break;
            }
        }
        tptr = tptr->next;
    }
    if(!found)
    {
        printf("\n\t\tData not found...");
        printf("\n\n\n\t\tEnter 2 to try again, 1 to go to the menu, 0 to exit:");
        scanf("%d", &c);
        if(c == 2){
            system("CLS");
            transation_3();
        }
    }
    else
    {
        make_file();
        printf("\n\t\tEnter 1 to go to the menu and 0 to exit:");
        scanf("%d", &c);
    }
    
    return c;
}
// Show details of an individual account
int details_4()
{
    list_init();
    int ac, c;
    printf("\t\tEnter the account number:");
    scanf("%d", &ac);
    tptr = start;
    while(tptr!=NULL)
    {
        if(tptr->acnum == ac)
        {
            printf("\n\t\tAccount No. :%d\n\t\tName:%s\n\t\tDOB:%s\n\t\tAge:%s\n\t\tAddress:%s\n\t\tNID No.:%s\n\t\tPhone Number:%s\n\t\tAmount Deposit:BDT %f\n\n", tptr->acnum, tptr->name, tptr->birthday, tptr->age, tptr->address, tptr->nid, tptr->phone, tptr->amount);
            break;
        }
        tptr = tptr->next;
    }
    if(tptr == NULL)
    {
        printf("\n\t\tData not found...");
        printf("\n\n\n\t\tEnter 2 to try again, 1 to go to the menu, 0 to exit:");
        scanf("%d", &c);
        if(c == 2){
            system("CLS");
            details_4();
        }
    }
    else
    {
        printf("\n\t\tEnter 1 to go to the menu and 0 to exit:");
        scanf("%d", &c);
    }
    
    return c;
}
// Delete an existing account
int deleteacc_5()
{
    list_init();
    //display();
    printf("\n\n");
    int ac, c, found = 0;
    printf("\t\tEnter the account number you want to delete:");
    scanf("%d", &ac);
    if(start==NULL)
    {
        printf("\n\t\tNo Account Available\n");
        goto END;
    }
    if(start->acnum == ac)
    {
        if(start->next == NULL)
        {
            free(start);
            start = NULL;
            printf("pp\n");
        }
        else
        {
            tptr = start;
            start = tptr->next;
            start->prev = NULL;
            free(tptr);
        }
        printf("\n\t\tDeleted Successfully...");
        goto END;
    }
    else
    {
        tptr = start;
        while(tptr!=NULL)
        {
            if(tptr->acnum==ac)
            {
                // int conf = 0;
                // while (conf != 1)
                // {
                //     printf("\n\t\tDear %s, Enter 1 to confirm delete..\n\n", tptr->name);
                //     scanf("%d", conf);
                //     printf("ppp\n");
                // }
                nptr->next = tptr->next;
                free(tptr);
                printf("\n\t\tDeleted Successfully...");
                goto END;
            }
            nptr = tptr;
            tptr = tptr->next;
        }
    }
    if(!found)
    {
        printf("\n\t\tData not found...");
        printf("\n\n\n\t\tEnter 2 to try again, 1 to go to the menu, 0 to exit:");
        scanf("%d", &c);
        if(c == 2){
            system("CLS");
            deleteacc_5();
        }
        else goto RETURN;
    }
    END:
        make_file();
        printf("\n\n\t\tEnter 1 to go to the menu and 0 to exit:");
        scanf("%d", &c);
    RETURN:
    return c;
}
// Show Account's List
int customers_list_6()
{
    // list_init();
    display();
    printf("\n\n\t\tBack to Main Menu Press 1 or 0 for exit: ");
    int choice;
    scanf("%d", &choice);
    return choice;
    /*int p;
    tptr = start;
    if(tptr == NULL){
        printf("\n\nNo Data Record..");
    }
    else
    {
        printf("\nACC. NO.\tNAME\t\tADDRESS\t\tPHONE\n\n");
        while(tptr!=NULL)
        {
            printf("%d\t%s\t\t%s\t\t%s\n", tptr->acnum, tptr->name, tptr->address, tptr->phone);
            //tptr = tptr->next;
        }
    }*/
}
int main()
{
    int n = 1, i;
    start = NULL, last = NULL;
    do
    {
        char pass[10];
        printf("\n\nEnter The Passward To Login:");
        scanf("%s", pass);
        if(strcasecmp(pass,"1")==0){
            printf("\n\nPassward Match!\n");
            printf("\nLoading");
            for(i = 1; i < 6; i++)
            {
                printf(".");
                delay(100);
            }
            break;
        }
        else
        {
            printf("\n\nWrong Passward!!\n");
            printf("Press 1 to try again, press 0 to exit:");
            scanf("%d", &n);
        }
        system("CLS");
    }while(n);
    if(n==0)goto END;
    int p;
    int choice;
    do
    {
        system("CLS");
        printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n\n");
        printf("\t\t\t|||||||| WELCOME TO THE MAIN MENU ||||||||");
        printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transaction\n\t\t4.Check the detail of existing account\n");
        printf("\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n");
        printf("\t\tEnter your choice:");
        // int choice;
        scanf("%d", &choice);
        if(choice == 1)
        {
            system("CLS");
            p = create_new();
            system("CLS");
            if(!p)break;
        }
        else if(choice == 2)
        {
            system("CLS");
            p = changeinfo_2();
            system("CLS");
        }
        else if(choice == 3)
        {
            system("CLS");
            p = transation_3();
            if(p==0)break;
            system("CLS");
        }
        else if(choice == 4)
        {
            system("CLS");
            p = details_4();
            if(p==0)break;
            system("CLS");
        }
        else if(choice == 5)
        {
            system("CLS");
            p = deleteacc_5();
            if(p==0)break;
            system("CLS");
        }
        else if(choice == 6)
        {
            system("CLS");
            int p = customers_list_6();
            system("CLS");
            if(p==0)break;
        }
        else if(choice == 7)
        {
            break;
        }
        else if(choice == 9)clearDatabase();
    }while(choice != 7);
    END:
        system("CLS");
        printf("\n\n\t\tThis programme developed by HABIBUR RAHMAN - 011 161 081\n\n");
        printf("%50s\n", "Thank You");
        getchar();
        getchar();
    return 0;
}

