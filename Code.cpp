#include <stdio.h>
#include <string.h>
double enqcount=0.0,autocount=0.0,cngcount=0.0,evcount=0.0,healthcount=0.0,autoev=0.0,fuelcount=0.0;
void savedatafiles(double healthcount,double autopercent,double cngpercent,double electricratio,double autoev );

struct cardata
{
    int healthoption;
    char transmission[10], seat[10], bodytype[10], fueltype[10], healthflag[10];
};
void showcars(struct cardata c1);


void enquiry()
{
    struct cardata c1;
    printf("Enter the transmission type automatic / manual\n--------------------------------\n");
    scanf("%s",c1.transmission);
    //While loop and strcmp method to check for wrong input and prompt user again
    while(strcmp("automatic",c1.transmission)!=0&&strcmp("manual",c1.transmission)!=0)
    {
        printf("Enter a valid option for transmission type automatic / manual\n--------------------------------\n");
        scanf("%s",c1.transmission);
    }
    //Using pointers to access the global variable by address and increment it
    double *autocnt;
    autocnt = &autocount;
    if(strcmp("automatic",c1.transmission)==0)
        ++*autocnt;

    printf("Enter the seating capacity five / seven / eight\n--------------------------------\n");
    scanf("%s",c1.seat);
    while(strcmp("five",c1.seat)!=0&&strcmp("seven",c1.seat)!=0&&strcmp("eight",c1.seat)!=0)
    {
        printf("Enter a valid option for seating capacity five / seven / eight\n--------------------------------\n");
        scanf("%s",c1.seat);
    }
    printf("Enter the body type sedan / suv\n--------------------------------\n");
    scanf("%s",c1.bodytype);
    while(strcmp("sedan",c1.bodytype)!=0&&strcmp("suv",c1.bodytype)!=0)
    {
        printf("Enter a valid option for body type sedan / suv\n--------------------------------\n");
        scanf("%s",c1.bodytype);
    }
    printf("Enter the fuel type petrol / diesel / cng / electric\n--------------------------------\n");
    scanf("%s",c1.fueltype);
    while(strcmp("petrol",c1.fueltype)!=0&&strcmp("diesel",c1.fueltype)!=0&&strcmp("cng",c1.fueltype)!=0&&strcmp("electric",c1.fueltype)!=0)
    {
        printf("Enter a valid option for fuel type petrol / diesel / cng / electric\n--------------------------------\n");
        scanf("%s",c1.fueltype);
    }

    double *ev;
    double *cng;
    double *fc;
    fc=&fuelcount;
    cng = &cngcount;
    ev=&evcount;
    if(strcmp("electric",c1.fueltype)!=0)
    {
        ++*fc;
    }
    if(strcmp("cng",c1.fueltype)==0)
    {
        ++*cng;
    }
    else if(strcmp("electric",c1.fueltype)==0)
    {
        ++*ev;
    }
    printf("Do you want to access health based features? (Type) yes / no\n--------------------------------\n");
    {
        scanf("%s",c1.healthflag);
    }
    while(strcmp("yes",c1.healthflag)!=0&&strcmp("no",c1.healthflag)!=0)
    {
        printf("Enter a valid option for access to health based features? (Type) yes / no\n--------------------------------\n");
        scanf("%s",c1.healthflag);
    }
    double *health;
    health = &healthcount;
    if(strcmp("yes",c1.healthflag)==0)
    {
        printf("(Use Numbers) 1. In-built sanitisation 2.Enhanced air purification system 3.Anti-bacterial System\n--------------------------------\n");
        scanf("%d",&c1.healthoption);
        ++*health;
    }
    else if(strcmp("no",c1.healthflag)==0)
    {
        printf("Proceeding to save data...");
    }
    double *enqc;
    enqc = &enqcount;
    ++*enqc;
    double *autev;
    autev = &autoev;
    if(strcmp("automatic",c1.transmission)==0&&strcmp("electric",c1.fueltype)==0)
    {
        ++*autev;
    }
    showcars(c1);
}


void accessdata(){
    int choice;
    char next;
    double electricratio,autopercent,cngpercent;
    do{
        if(enqcount==0)
        {
            printf("No data recorded\n");
            break;
        }
        printf("Select an option Below\n--------------------------------\n");
        autopercent=(autocount/enqcount)*100.0;
        cngpercent=(cngcount/enqcount)*100;
        //Using ternary operator to avoid 0/0(infinite value)
        electricratio=(evcount!=0)?(evcount/fuelcount):0;
        printf("(Use numbers)\n"
               "1.Customer enquiries on personal health based features\n"
               "2.Percentage of enquiries about automatic cars\n"
               "3.Percentage of CNG vehicles enquired by customers\n"
               "4.Demand of electric cars compared to other cars\n"
               "5.Combination of enquiries made about automatic and electric cars\n"
               "6.No.of enquiries made in the site\n--------------------------------\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1: printf("There were %f enquiries on personal health based features\n--------------------------------\n",healthcount);
                break;
            case 2:
                printf("%lf %% of the people enquired about Automatic cars\n--------------------------------\n",autopercent);
                break;
            case 3:
                printf("%f %% of the people inquired about CNG cars\n--------------------------------\n",cngpercent);
                break;
            case 4:
                printf("For every Car sold %f electric cars are sold\n--------------------------------\n",electricratio);
                break;
            case 5:
                printf("The enquires made for combination of Electric and Automatic cars is %f\n--------------------------------\n",autoev);
                break;
            case 6:
                printf("The total no.of enquires made for the site is %f\n--------------------------------\n",enqcount);
                break;
            default: printf("Invalid choice\n--------------------------------\n");
                break;
        }
        printf("Saving data to a file\n--------------------------------\n");
        savedatafiles(healthcount,autopercent,cngpercent,electricratio,autoev);
        printf("Do you want to go back to the main menu? (Press y/n)\n");
        scanf("%s",&next);
    }while(next=='n');
}

void savedatafiles(double healthcount,double autopercent,double cngpercent,double electricratio,double autoev)
{
    printf("A report is being generated as a text file\n");
    //creates and open a file in write mode
    FILE *fp=fopen ("data.txt", "w");
    //writing to the file using fprintf method
    fprintf(fp,"No.of enquiries made in the site = %f\n",enqcount);
    fprintf(fp,"Percentage of enquiries about automatic cars =  %f\n",autopercent);
    fprintf(fp,"Percentage of CNG vehicles enquired by customers = %f\n",cngpercent);
    fprintf(fp,"Customer enquiries on personal health based features is %f\n",healthcount);
    fprintf(fp,"Enquires made about a automatic electric vehicle = %f\n",autoev);
    fprintf(fp,"For every other car enquired %f electric vehicles are enquired\n",electricratio);
    //saving and closing the file
    fclose(fp);
}

int main(){
    int choice;
    char next;
    printf("Hello!! Find your desired car here!\n");
    do
    {
        //switch case for menu driven program
        printf("Select an option Below\n--------------------------------\n");
        printf("(Use numbers) 1:Enquiry 2:Access admin data\n--------------------------------\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1: printf("Entering enquiry mode\n--------------------------------\n");
                enquiry();
                break;
            case 2: printf("Entering admin mode\n--------------------------------\n");
                accessdata();
                break;
            default: printf("Invalid choice\n--------------------------------\n");
                break;
        }
        printf("Do you want to continue? (Press y / n)\n--------------------------------\n");
        scanf("%s",&next);
    }while(next=='y');
}
