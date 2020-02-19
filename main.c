/* *********************************************************************
                        MEAL MANAGEMENT SYSTEM
                     DEVELOPED BY: S.R. SHUVA DEV
                        MOBILE NO: 01883661903
************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>
#define DAY 32

void displayWelCome(void);
void createMealTable(void);
int login(void);
void loadLoginInfo(void);
void writeLoginFile(void);
void displayMainMenu(void);
int matchId(void);
//Member section function goes here...
void displayMemberScreen(void);
void addNewMember(void);
void readMembersInfo(FILE *);
void readCostInfo(FILE *);
void writeMembersInfo(void);
void writeCostInfo(void);
void displayMembers(void);
void deleteMember(void);
void searchMember(void);
int totalMealById(int[]);
void addBalance(void);
// Daily task section function goes here...
void dailyTaskScreen(void);
void updateMeal(void);
bool checkMealUpdated(int);
void updateCost(void);
bool checkCostUpdated(int);
// Check Report Function Goes Here...
void checkReportScreen(void);
void monthlyLog(void);
void memberMealByDate(void);
int searchMealByName(char *,int);
void viewFullReport(void);
double totalBalance(void);
double toalCost(void);
double mealRate(void);
int totalMeal(void);
int generateFile(void);
// This MonthName and Password for createMealTable function...
char MonthName[50][50];
char Password[50][50];
int monthCount=0;
// This loginMonth and loginPassword for login function..
char loginMonth[50];
char loginPassword[50];
// Time component goes here..
struct time{
    WORD wYear;
    WORD wMonth;
    WORD wWeekOfDay;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliSecond;
};
typedef struct time Times;
char timeString[100];
char weekOfDay[10];
Times getTime(void);
char * getTimeString(Times);
char * getWeekOfDay(int);
struct member{
    char name[50];
    double pay;
    int meal[DAY];
};
typedef struct member Members;
struct lists{
    Members info;
    struct lists *next;
};
typedef struct lists MemberLists;
double costTable[DAY];
/* Linked list for store all member information... */
int listsize=0;
MemberLists *head=NULL;
int createNode(char *,double,int[]);
int insertAtLast(MemberLists *);
void reset(void);
int main()
{
    int menu,chklogin,submenu,m_menu,d_task,chk_report;
    loadLoginInfo();
    do{
        displayWelCome();
        printf("\n%35s"," ");
        printf("Enter your choice:%5s"," ");
        scanf("%d",&menu);
        switch(menu)
        {
        case 0:
            writeLoginFile();
            printf("Exiting...!\n");
            break;
        case 1:
            chklogin=login();
            if(chklogin)
            {
                do{
                    displayMainMenu();
                    scanf("%d",&submenu);
                    switch(submenu)
                    {
                    case 0:
                        writeMembersInfo();
                        writeCostInfo();
                        reset();
                        break;
                    case 1:
                        do{
                            displayMemberScreen();
                            scanf("%d",&m_menu);
                            switch(m_menu)
                            {
                            case 0:
                                break;
                            case 1:
                                addNewMember();
                                break;
                            case 2:
                                deleteMember();
                                break;
                            case 3:
                                searchMember();
                                break;
                            case 4:
                                displayMembers();
                                break;
                            case 5:
                                addBalance();
                                break;
                            }
                        }while(m_menu!=0);
                        break;
                    case 2:
                        dailyTaskScreen();
                        scanf("%d",&d_task);
                        switch(d_task)
                        {
                        case 0:
                            break;
                        case 1:
                            updateMeal();
                            break;
                        case 2:
                            updateCost();
                            break;
                        }
                        break;
                    case 3:
                        do{
                            checkReportScreen();
                            scanf("%d",&chk_report);
                            switch(chk_report)
                            {
                            case 0:
                                break;
                            case 1:
                                viewFullReport();
                                break;
                            case 2:
                                memberMealByDate();
                                break;
                            case 3:
                                monthlyLog();
                                break;
                            case 4:
                                generateFile();
                                printf("\n%35sFile Generated Successfully!\n\n"," ");
                                system("pause");
                                break;
                            }
                        }while(chk_report!=0);
                        break;
                    }
                }while(submenu!=0);
            }
            break;
        case 2:
            createMealTable();
            break;
        }
    }while(menu!=0);
    printf("\n");
    system("pause");
    return 0;
}
/*
*************************************
            Welcome Section
*************************************
*/
void displayWelCome()
{
    system("cls");
    printf("\n\n%30s"," ");
    for(int i=1;i<=50;i++)
    {
        printf("-");
    }
    printf("\n\n%38s%s"," ","Welcome To Meal Management System\n");
    printf("%38s%s"," ","  Developed By: S.R. Shuva Dev\n");
    printf("\n%30s"," ");
    for(int i=1;i<=50;i++)
    {
        printf("-");
    }
    printf("\n\n\n%30s[ 1 ]%10sLogin To Meal Table\n"," "," ");
    printf("\n%30s[ 2 ]%10sCreate New Meal Table\n"," "," ");
    printf("\n%30s[ 0 ]%10sExit From The System\n\n"," "," ");
    printf("%30s"," ");
    for(int i=1;i<=50;i++)
    {
        printf("-");
    }
}
void createMealTable(void)
{
    system("cls");
    printf("\n\n\n\n%30s"," ");
    printf("FILL THE FORM BELOW\n");
    printf("%30s%s"," ","-------------------\n");
    printf("\n\n\n%30s%s%10s"," ","Enter month name:"," ");
    scanf(" %[^\n]s",MonthName[monthCount]);
    printf("\n\n%30sEnter your password:%7s"," "," ");
    scanf(" %[^\n]s",Password[monthCount]);
    printf("\n\n\n\n%25sYour Account Successfully Created...!\n\n"," ");
    printf("%25sYou Can Now Login To System\n\n"," ");
    system("pause");
    monthCount++;
}
int login()
{
    system("cls");
    printf("\n\n\n\n%30sLogin To Meal Management System\n\n"," ");
    printf("%30sEnter Month Name And Password Correctly\n\n"," ");
    printf("%25s"," ");
    for(int i=1;i<=50;i++)
    {
        printf("-");
    }
    printf("\n\n\n%30s"," ");
    printf("Month Name:%10s"," ");
    scanf(" %[^\n]s",loginMonth);
    printf("\n\n%30sPassword:%12s"," "," ");
    scanf(" %[^\n]s",loginPassword);

    if(!matchId())
    {
        printf("\n\n\n%32s"," ");
        printf("Month And Password Not Match\n");
        printf("%32sPlease Try Again With Proper Password\n\n"," ");
        printf("%32sIf You Don't have Registered Yet, Please Create An Table First\n"," ");
        system("pause");
        return 0;
    }else{
        FILE *fp;
        char MonthFile[50];
        char MonthCostFile[50];
        strcpy(MonthFile,loginMonth);
        strcat(MonthFile,".dat");
        fp=fopen(MonthFile,"r");
        if(fp==NULL)
        {
            fp=fopen(MonthFile,"w+");
        }
        readMembersInfo(fp);
        strcpy(MonthCostFile,loginMonth);
        strcat(MonthCostFile,"costs.dat");
        fp=fopen(MonthCostFile,"r+");
        if(fp==NULL)
        {
            fp=fopen(MonthCostFile,"w+");
        }
        readCostInfo(fp);
        fclose(fp);
        return 1;
    }
    system("pause");
}
int matchId()
{
    int flag=0;
    // Check inputed password are valid or not..
    for(int i=0;i<monthCount;i++)
    {
        if((strcmp(MonthName[i],loginMonth)==0) && (strcmp(Password[i],loginPassword)==0))
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        return 1;
    }else{
        return 0;
    }
}
void loadLoginInfo()
{
    FILE *fp=fopen("login.dat","r+");
    if(fp==NULL)
    {
        fp=fopen("login.dat","w+");
    }
    while(!feof(fp))
    {
        fscanf(fp,"%s",MonthName[monthCount]);
        fscanf(fp,"%s ",Password[monthCount]);
        monthCount++;
    }
    fclose(fp);
}
void writeLoginFile()
{
    FILE *fp=fopen("login.dat","w");
    if(fp==NULL)
    {
        perror("File opening failed: ");
        exit(0);
    }
    for(int i=0;i<monthCount;i++)
    {
        fprintf(fp,"%s %s\n",MonthName[i],Password[i]);
    }
    fclose(fp);
}
void displayMainMenu()
{
    system("cls");
    printf("\n\n\n\n%40s"," ");
    printf("Meal Management System\n");
    printf("%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n%35s[ 1 ]%10sMEMBERS\n"," "," ");
    printf("%35s[ 2 ]%10sDAILY TASK\n"," "," ");
    printf("%35s[ 3 ]%10sCHECK REPORT\n"," "," ");
    printf("%35s[ 0 ]%10sLOGOUT\n"," "," ");
    printf("\n%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n\n%35sENTER YOUR CHOICE :%5s"," "," ");
}
/*
**********************************
          Member Section
**********************************
*/
void displayMemberScreen()
{
    system("cls");
    printf("\n\n\n\n%45s"," ");
    printf("Member Section\n");
    printf("%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n%35s[ 1 ]%10sAdd New Member\n"," "," ");
    printf("%35s[ 2 ]%10sDelete Member\n"," "," ");
    printf("%35s[ 3 ]%10sSearch Member\n"," "," ");
    printf("%35s[ 4 ]%10sView All Member\n"," "," ");
    printf("%35s[ 5 ]%10sAdd Balance\n"," "," ");
    printf("%35s[ 0 ]%10sBack To Main Menu\n"," "," ");
    printf("\n%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n\n%35sENTER YOUR CHOICE :%5s"," "," ");
}
void addNewMember()
{
    char MemberName[51];
    double amount;
    int meal[DAY];
    system("cls");
    printf("\n\n\n\n%35sFill The Following Section Correctly\n%30s"," "," ");
    for(int i=1;i<=46;i++)
        printf("-");
    printf("\n\n\n%38sEnter The Name :%5s"," "," ");
    scanf(" %[^\n]s",MemberName);
    printf("\n\n\n%38sEnter The Amount :%3s"," "," ");
    scanf("%lf",&amount);
    // Initial all meal with -1 for new member...
    for(int i=1;i<DAY;i++)
    {
         meal[i]=-1;
    }
    if(createNode(MemberName,amount,meal))
        printf("\n\n\n%35sMember created successfully!\n"," ");
    else
        printf("\n\n\n%35sMember created failed!\n"," ");
    system("pause");
}
// Read all member info from file...
void readMembersInfo(FILE *fp)
{
    int i;
    char memberName[50];
    double amount;
    int meal[DAY];
    if(fgetc(fp)==EOF)
    {
        return;
    }else{
        fseek(fp,0,SEEK_SET);
        while(!feof(fp))
        {
            fscanf(fp,"%[^\n]s",memberName);
            fscanf(fp,"%lf",&amount);
            for(i=1;i<DAY;i++)
            {
                fscanf(fp,"%d ",&meal[i]);
            }
            createNode(memberName,amount,meal);
        }
    }
}
void readCostInfo(FILE *fp)
{
    if(fgetc(fp)==EOF)
    {
        memset(costTable,0.00,sizeof(costTable));
        fseek(fp,0,SEEK_SET);
    }else{
        while(!feof(fp))
        {
            for(int i=1;i<DAY;i++)
                fscanf(fp,"%lf",&costTable[i]);
        }
    }
}
void writeMembersInfo()
{
    FILE *fp;
    MemberLists *myList=head;
    char fileName[20];
    strcpy(fileName,loginMonth);
    strcat(fileName,".dat");
    fp=fopen(fileName,"r+");
    if(fp==NULL)
    {
        perror("File opening failed:");
        exit(0);
    }
    while(myList)
    {
        fprintf(fp,"%s\n",myList->info.name);
        fprintf(fp,"%.2lf\n",myList->info.pay);
        for(int i=1;i<DAY;i++)
        {
            fprintf(fp,"%d ",myList->info.meal[i]);
        }
        fprintf(fp,"\n");
        myList=myList->next;
    }
    fclose(fp);
}
void writeCostInfo()
{
    FILE *fp;
    char fileName[20];
    strcpy(fileName,loginMonth);
    strcat(fileName,"costs.dat");
    fp=fopen(fileName,"r+");
    if(fp==NULL)
    {
        perror("File opening failed:");
        exit(0);
    }
    for(int i=1;i<DAY;i++)
    {
        fprintf(fp,"%.2lf\n",costTable[i]);
    }
    fclose(fp);
}
void displayMembers()
{
    int i=0;
    system("cls");
    MemberLists *myList=head;
    printf("\n\n%50sDisplaying All Members\n"," ");
    printf("\n\n\n%53sMember List\n"," ");
    printf("%38s"," ");
    for(int i=1;i<=40;i++)
        printf("-");
    printf("\n\n\n");
    printf("%45sIndex%11sName%4sAmount\n"," "," "," ");
    if(myList==NULL)
    {
        printf("\n%40sThere Is No Member\n\n"," ");
    }
    while(myList)
    {
        printf("\n%40s", " ");
        printf("%10d%15s%10.2lf\n", i++,  myList->info.name, myList->info.pay);
        myList=myList->next;
    }
    system("pause");
}
void deleteMember()
{
    int i=0,index,confirm;
    system("cls");
    MemberLists *myList=head;
    printf("\n\n%35sSelect Index From Below To Delete (-1 for cancel)\n"," ");
    printf("\n\n%53sMember List\n"," ");
    printf("%38s"," ");
    for(int j=1;j<=40;j++)
        printf("-");
    printf("\n\n\n");
    printf("%45sIndex%11sName%4sAmount\n"," "," "," ");
    if(myList==NULL)
    {
        printf("\n%40sThere Is No Member To Delete!\n\n"," ");
    }else{
        while(myList)
        {
            printf("\n%40s", " ");
            printf("%10d%15s%10.2lf\n", i++,  myList->info.name, myList->info.pay);
            myList=myList->next;
        }
        myList=head;
        MemberLists *previous=myList;
        printf("\n%40sEnter Index : "," ");
        scanf("%d",&index);
        i=0;
        if(index==0)
        {
            printf("\n\n%40sAre Your Sure ? (1/0) : "," ");
            scanf("%d",&confirm);
            if(confirm==1)
            {
                head=head->next;
                myList=head;
                previous=head;
                printf("\n\n\n%40sMember Deleted Successfully\n"," ");
                listsize--;
            }else{
                printf("\n\n\n%40sCancel Deleting\n"," ");
            }
        }else if(index==-1){
            printf("\n\n\n%40sCancel Deleting\n"," ");
        }else if(index>=listsize)
        {
            printf("\n\n\n%40sInvalid Index!\n"," ");
        }
        else{
            while(myList)
            {
                if(i==index)
                {
                    printf("\n\n%40sAre Your Sure ? (1/0) : "," ");
                    scanf("%d",&confirm);
                    if(confirm==1)
                    {
                        previous->next=myList->next;
                        listsize--;
                        printf("\n\n\n%40sMember Deleted Successfully\n"," ");
                        break;
                    }else{
                        printf("\n\n\n%40sCancel Deleting\n"," ");
                    }
                }
                i++;
                previous=myList;
                myList=myList->next;
            }
        }
    }
    system("pause");
}
void searchMember()
{
    system("cls");
    int flag=0;
    MemberLists *myList=head;
    char name[50];
    printf("\n\n%48sSearch Member Info\n"," ");
    printf("%38s"," ");
    for(int i=1;i<=40;i++)
        printf("-");
    printf("\n\n\n%43sEnter Name To Search : "," ");
    scanf(" %s[^\n]s%*c",name);
    if(head==NULL)
    {
        printf("\n\n%43sMembers not found !\n\n"," ");
    }
    else{
        while(myList)
        {
            if(strcmp(name,myList->info.name)==0)
            {
                flag=1;
                break;
            }
            myList=myList->next;
        }
        if(flag==0)
        {
            printf("\n\n%43sMembers not found !\n\n"," ");
        }else if(flag==1)
        {
            printf("\n\n%43sMembers found !\n\n\n\n"," ");
            printf("%45sName : %s\n\n"," ",name);
            printf("%45sPaid : %.2lf\n\n"," ",myList->info.pay);
            printf("%45sMeal : %d\n\n"," ",totalMealById(myList->info.meal));
        }
    }
    system("pause");
}
// This function is for calculate total meal by give address...
int totalMealById(int meal[])
{
    int totalmeal=0;
    for(int i=1;i<DAY;i++)
    {
        if(meal[i]!=-1)
        {
            totalmeal=totalmeal+meal[i];
        }
    }
    return totalmeal;
}
void addBalance()
{
    system("cls");
    int flag=0,confirm;
    double amount;
    MemberLists *myList=head;
    char name[50];
    printf("\n\n%48sSearch Member Info\n"," ");
    printf("%38s"," ");
    for(int i=1;i<=40;i++)
        printf("-");
    printf("\n\n\n%43sEnter Name To Search : "," ");
    scanf(" %s[^\n]s%*c",name);
    if(head==NULL)
    {
        printf("\n\n%43sMembers not found !\n\n"," ");
    }
    else{
        while(myList)
        {
            if(strcmp(name,myList->info.name)==0)
            {
                flag=1;
                break;
            }
            myList=myList->next;
        }
        if(flag==0)
        {
            printf("\n\n%43sMembers not found !\n\n"," ");
        }else if(flag==1)
        {
            printf("\n\n%43sMembers found !\n\n\n\n"," ");
            printf("%45sName : %s\n\n"," ",name);
            printf("%45sPaid : %.2lf\n\n"," ",myList->info.pay);
            printf("%45sMeal : %d\n\n\n\n\n"," ",totalMealById(myList->info.meal));
            printf("%43sTotal Amount : "," ");
            scanf("%lf",&amount);
            printf("\n\n\n%43sAre You Sure?(1/0) : "," ");
            scanf("%d",&confirm);
            if(confirm==1)
            {
                myList->info.pay=myList->info.pay+amount;
                printf("\n\n%43sAmount Updated Successfully...\n"," ");
            }else{
                printf("\n\n%43sUpdate canceled!\n"," ");
            }
        }
    }
    system("pause");
}
/* ************************************************************
                        Daily Task Section
***************************************************************/
void dailyTaskScreen()
{
    system("cls");
    printf("\n\n\n\n%45s"," ");
    printf("Member Section\n");
    printf("%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n%35s[ 1 ]%10sUpdate Meal\n"," "," ");
    printf("%35s[ 2 ]%10sUpdate Cost\n"," "," ");
    printf("%35s[ 0 ]%10sBack To Main Menu\n"," "," ");
    printf("\n\n%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n\n%35sENTER YOUR CHOICE :%5s"," "," ");
}
void updateMeal()
{
    system("cls");
    int meal,flag=0;
    char c,pass[50];
    Times tm=getTime();
    MemberLists *myList=head;
    printf("\n\n\n%45sUpdate Daily Meal\n"," ");
    printf("%30s"," ");
    for(int i=1;i<=50;i++)
        printf("-");
    printf("\n\n%37sToday is : %s\n"," ",getTimeString(tm));
    if(myList==NULL)
    {
        printf("\n%37sThere are no members available!\n"," ");
        system("pause");
        return;
    }
    if(checkMealUpdated(tm.wDay))
    {
        printf("\n%37sAlready Updated\n"," ");
        printf("\n%37sOnly Admin Can Change Data After Edited Once\n\n"," ");
        printf("\n%37sPress (e) to Edit Or (c) to Cancel : "," ");
        scanf(" %c",&c);
        if(c=='e')
        {
            printf("\n%37sEnter Password : "," ");
            scanf(" %[^\n]s",pass);
            if(strcmp(loginPassword,pass)==0)
            {
                printf("\n%37sEnter Meals : \n"," ");
                while(myList)
                {
                    printf("\n%40s"," ");
                    printf("Name :%15s   Meal :%8s",myList->info.name," ");
                    scanf("%d",&meal);
                    myList->info.meal[tm.wDay]=meal;
                    flag+=1;
                    myList=myList->next;
                }
                if(flag==listsize)
                {
                    printf("\n%37sMeal Successfully Updated...\n"," ");
                }else{
                    printf("\n%37sMeal Updated Failed...\n"," ");
                }
                system("pause");
                return;
            }else{
                printf("\n%37sInvalid Password!\n"," ");
                system("pause");
                return;
            }
        }
        else
        {
            printf("\n%37sUpdate Canceled..\n"," ");
            system("pause");
            return;
        }

    }else{
        printf("\n%37sEnter Meals : \n"," ");
    }
    while(myList)
    {
        printf("\n%40s"," ");
        printf("Name :%15s   Meal :%8s",myList->info.name," ");
        scanf("%d",&meal);
        myList->info.meal[tm.wDay]=meal;
        flag+=1;
        myList=myList->next;
    }
    if(flag==listsize)
    {
        printf("\n%37sMeal Successfully Updated...\n"," ");
    }else{
        printf("\n%37sMeal Updated Failed...\n"," ");
    }
    system("pause");
}
bool checkMealUpdated(int day)
{
    MemberLists *myList=head;
    if(myList->info.meal[day]<0)
    {
        return false;
    }else{
        return true;
    }
}
void updateCost()
{
    system("cls");
    char c,pass[50];
    double cost;
    Times tm=getTime();
    printf("\n\n%45sUpdate Daily Cost\n"," ");
    printf("%30s"," ");
    for(int i=1;i<=50;i++)
        printf("-");
    printf("\n\n%37sToday is : %s\n"," ",getTimeString(tm));
    if(head==NULL)
    {
        printf("\n%37sThere is No Member Available. So You Can't Update Cost\n"," ");
        system("pause");
        return;
    }
    if(checkCostUpdated(tm.wDay))
    {
        printf("\n%37sAlready Updated\n"," ");
        printf("\n%37sOnly Admin Can Change Cost After Edited Once\n\n"," ");
        printf("\n%37sPress (e) to Edit Or (c) to Cancel : "," ");
        scanf(" %c",&c);
        if(c=='e')
        {
            printf("\n%37sEnter Password : "," ");
            scanf(" %[^\n]s",pass);
            if(strcmp(loginPassword,pass)==0)
            {
                printf("\n%37sToday Cost is : "," ");
                scanf(" %lf",&cost);
                costTable[tm.wDay]=cost;
                printf("\n%37sCost Updated Successfully!\n"," ");
                system("pause");
                return;
            }else{
                printf("\n%37sInvalid Password!\n"," ");
                system("pause");
                return;
            }
        }
        else
        {
            printf("\n%37sUpdate Canceled..\n"," ");
            system("pause");
            return;
        }

    }else{
        printf("\n%37sToday Cost is : "," ");
        scanf(" %lf",&cost);
        costTable[tm.wDay]=cost;
        printf("\n%37sCost Updated Successfully!\n"," ");
    }
    system("pause");
}
bool checkCostUpdated(int day)
{
    if(costTable[day]<=0)
    {
        return false;
    }else{
        return true;
    }
}
/* **************************************************************
                    Check Report Function
****************************************************************/
void checkReportScreen()
{
    system("cls");
    printf("\n\n\n\n%40s"," ");
    printf("Meal Management System\n");
    printf("%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n%35s[ 1 ]%10sView FUll Report\n"," "," ");
    printf("%35s[ 2 ]%10sMembers Meal By Date\n"," "," ");
    printf("%35s[ 3 ]%10sMonthly Log\n"," "," ");
    printf("%35s[ 4 ]%10sMake A File\n"," "," ");
    printf("%35s[ 0 ]%10sBack To Main Menu\n"," "," ");
    printf("\n\n%30s"," ");
    for(int i=1;i<=42;i++)
    {
        printf("-");
    }
    printf("\n\n\n%35sENTER YOUR CHOICE :%5s"," "," ");
}
void monthlyLog()
{
    Times tm=getTime();
    int day=tm.wDay;
    MemberLists *myList=head;
    system("cls");
    printf("\n\n%3sMonthly Meal Log\n"," ");
    printf("%2s------------------\n\n"," ");
    if(head==NULL)
    {
        printf("\n\n%5sNo members available!\n"," ");
    }else{
        printf(" DAY");
        while(myList)
        {
            printf("%10s",myList->info.name);
            myList=myList->next;
        }
        myList=head;
        for(int i=1;i<=day;i++)
        {
            printf("\n%4d",i);
            while(myList)
            {
                printf("%10d",myList->info.meal[i]);
                myList=myList->next;
            }
            myList=head;
        }
        printf("\n\n");
    }
    system("pause");
}
void memberMealByDate()
{
    system("cls");
    int day;
    char c,name[50];
    printf("\n\n%40sEnter Member Name And Day to See\n"," ");
    printf("%40sMembers Meal Of a Particular Day.\n\n\n"," ");
    printf("%40sPress 'e' For Enter Or 'c' for Cancel : "," ");
    scanf(" %c",&c);
    if(c=='c')
    {
        system("pause");
        return;
    }else if(c=='e')
    {
        printf("\n%40sName : "," ");
        scanf(" %[^\n]s%*c",name);
        printf("\n%40sDay(1 to 31) : "," ");
        scanf("%d",&day);
        if(day>=1 && day<=31)
        {
            int found=searchMealByName(name,day);
            if(found==0)
            {
                printf("\n\n%40sNo member found!\n"," ");
            }else{
                printf("\n\n%40s%s Have %d Meal On day %d!\n"," ",name,found,day);
            }
        }else{
            printf("\n\n%40sInvalid Date!\n"," ");
        }
    }else{
        printf("\n\n%40sInvalid Command!\n"," ");
    }
    system("pause");
}
int searchMealByName(char *name,int day)
{
    int flag=0;
    MemberLists *myList=head;
    while(myList)
    {
        if(strcmp(myList->info.name,name)==0)
        {
            flag=1;
            return myList->info.meal[day];
        }
        myList=myList->next;
    }
    if(flag==0)
    {
        return 0;
    }
}
void viewFullReport()
{
    Times tm=getTime();
    MemberLists *myList=head;
    int t_m=0;
    char *time=getTimeString(tm);
    system("cls");
    printf("\n%45sMONTHLY REPORT"," ");
    printf("\n%32s"," ");
    for(int i=1;i<=42;i++)
        printf("-");
    printf("\n");
    printf("%53s%s\n","Date : ",time);
    printf("%53s%.2lf\n","Account Balance : ",totalBalance());
    while(myList)
    {
        t_m=t_m+totalMealById(myList->info.meal);
        myList=myList->next;
    }
    printf("%53s%d\n","Total Meal : ",t_m);
    printf("%53s%.2lf\n","Total Cost : ",toalCost());
    double AB=totalBalance()-toalCost();
    printf("%53s%.2lf\n","Available Balance : ",AB);
    printf("%53s%.2lf\n\n","Meal Rate : ",toalCost()/t_m);
    printf("\n%32s"," ");
    for(int i=1;i<=42;i++)
        printf("=");
    printf("\n\n\n%25s"," ");
    printf("NAME%11sTOTAL MEAL%5sTOTAL PAID%5sTOTAL COST%5sTOTAL DUE\n"," "," "," "," ");
    printf("%20s"," ");
    for(int i=1;i<=80;i++)
        printf("-");
    printf("\n");
    myList=head;
    while(myList)
    {
        printf("%25s"," ");
        printf("%-15s",myList->info.name);
        t_m=totalMealById(myList->info.meal);
        printf("%-15d",t_m);
        printf("%-15.2lf",myList->info.pay);
        printf("%-15.2lf",t_m*mealRate());
        printf("%-15.2lf",myList->info.pay-t_m*mealRate());
        printf("\n");
        myList=myList->next;
    }
    printf("%20s"," ");
    for(int i=1;i<=80;i++)
        printf("-");
    printf("\n\n");
    system("pause");
}
double totalBalance()
{
    MemberLists *myList=head;
    double t_bal=0;
    while(myList)
    {
        t_bal+=myList->info.pay;
        myList=myList->next;
    }
    return t_bal;
}
double toalCost()
{
    double t_cost=0;
    for(int i=1;i<DAY;i++)
    {
        t_cost=t_cost+costTable[i];
    }
    return t_cost;
}
double mealRate()
{
    double tc=toalCost();
    int total_meal=totalMeal();
    double meal_rate=tc/total_meal;
    return meal_rate;
}
// This function make for calculate total meal of all member..
int totalMeal()
{
    int total_meal=0;
    MemberLists *myList=head;
    while(myList)
    {
        total_meal+=totalMealById(myList->info.meal);
        myList=myList->next;
    }
    return total_meal;
}
int generateFile()
{
    int t_m;
    Times tm=getTime();
    MemberLists *myList=head;
    char *time=getTimeString(tm);
    char filename[50];
    strcpy(filename,loginMonth);
    filename[0]=toupper(filename[0]);
    strcat(filename,"Report.txt");
    FILE *fp=fopen(filename,"w+");
    fprintf(fp,"%36s"," ");
    fprintf(fp,"MONTHLY REPORT\n");
    fprintf(fp,"%22s"," ");
    for(int i=1;i<=42;i++)
        fprintf(fp,"-");
    fprintf(fp,"\n");
    fprintf(fp,"%42s%s\n","Date : ",time);
    fprintf(fp,"%42s%.2lf\n","Account Balance : ",totalBalance());
    fprintf(fp,"%42s%d\n","Total Meal : ",totalMeal());
    fprintf(fp,"%42s%.2lf\n","Total Cost : ",toalCost());
    fprintf(fp,"%42s%.2lf\n","Available Balance : ",totalBalance()-toalCost());
    fprintf(fp,"%42s%.2lf\n","Meal Rate : ",mealRate());
    fprintf(fp,"%22s"," ");
    for(int i=1;i<=42;i++)
        fprintf(fp,"=");
    fprintf(fp,"\n\n");
    fprintf(fp,"%5s%10s%21s%15s%15s%15s\n%5s"," ","NAME","TOTAL MEAL","TOTAL PAID","TOTAL COST","TOTAL DUE"," ");
    for(int i=1;i<=81;i++)
        fprintf(fp,"-");
    fprintf(fp,"\n");
    while(myList)
    {
        fprintf(fp,"%11s"," ");
        fprintf(fp,"%-15s",myList->info.name);
        t_m=totalMealById(myList->info.meal);
        fprintf(fp,"%-15d",t_m);
        fprintf(fp,"%-15.2lf",myList->info.pay);
        fprintf(fp,"%-15.2lf",t_m*mealRate());
        fprintf(fp,"%-12.2lf",myList->info.pay-t_m*mealRate());
        fprintf(fp,"\n");
        myList=myList->next;
    }
    fprintf(fp,"%5s"," ");
    for(int i=1;i<=81;i++)
        fprintf(fp,"-");
    fclose(fp);
}
/* **************************************************************
                    Time Function Goes Here
****************************************************************/
Times getTime()
{
    Times tm;
    GetLocalTime(&tm);
    return tm;
}
char * getTimeString(Times tm)
{
    sprintf(timeString,"%d/%d/%d %s",tm.wDay,tm.wMonth,tm.wYear,getWeekOfDay(tm.wWeekOfDay));
    return timeString;
}
char * getWeekOfDay(int day)
{
    switch(day)
    {
    case 0:
        strcpy(weekOfDay,"SUN");
        break;
    case 1:
        strcpy(weekOfDay,"MON");
        break;
    case 2:
        strcpy(weekOfDay,"TUE");
        break;
    case 3:
        strcpy(weekOfDay,"WED");
        break;
    case 4:
        strcpy(weekOfDay,"THU");
        break;
    case 5:
        strcpy(weekOfDay,"FRI");
        break;
    case 6:
        strcpy(weekOfDay,"SAT");
        break;
    }
    return weekOfDay;
}
/* **************************************************************
        Create Linked List For Store Member Information
****************************************************************/
// This function allocate and store information in allocated memory..
int createNode(char *name,double amount,int Meal[])
{
    MemberLists *newNode;
    newNode=(MemberLists *)malloc(sizeof(MemberLists));
    if(newNode==NULL)
    {
        printf("Memory allocation failed!\n");
        exit(0);
    }
    newNode->next=NULL;
    strcpy(newNode->info.name,name);
    newNode->info.pay=amount;
    for(int i=1;i<DAY;i++)
    {
        newNode->info.meal[i]=Meal[i];
    }
    if(insertAtLast(newNode)){ return 1;}
}
// This function do insert in last position...
int insertAtLast(MemberLists *node)
{
    MemberLists *myList=head;
    MemberLists *previous=NULL;
    if(head==NULL)
    {
        head=node;
    }else{
        while(myList!=NULL)
        {
            previous=myList;
            myList=myList->next;
        }
        previous->next=node;
    }
    listsize++;
    return 1;
}
// If user click logout then reset function will be called..
void reset()
{
    head=NULL;
    listsize=0;
    loginMonth[0]='\0';
    loginPassword[0]='\0';
    for(int i=0; i<DAY; i++)
    {
        costTable[i] = 0.0;
    }
}
