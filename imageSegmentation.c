/* Including Header Files */
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
/* Defining The Value Of MAXX */
#define MAXX 1000

/* Function To Insert The Matrix Manually */ 
void insert(void) {
    FILE *p;
    int i,j,n,max_row,max_colm;
    p=fopen("Source.txt","w");
    printf("\n Enter Size Of Row ");
    scanf("%d",&max_row);
    printf("\n Enter Size Of Column ");
    scanf("%d",&max_colm);
    for(i=0;i<max_row;i++) {
        printf("\n Enter %d row : ",i+1);
        for(j=0;j<max_colm;j++) {
            scanf("%d",&n);
            fprintf(p,"%d",n);
        }  
        fprintf(p,"\n");
    }
    fclose(p);
} 

/* Function To Obtain The No Of Rows And Colms From The Source Matrix */
int getmax(void) {
    FILE *p;
    int c=0;
    char ch;
    p=fopen("Source.txt","r");
    if(p==NULL) {
        printf("\n Sorry, Source File Not Found !");
        getch();
        exit(0);
    }
    do {
        ch=getc(p);
        if(ch=='0'||ch=='1') {
            c++;
        }
    } while(ch!='\n');
    return c;
}

/* Main Function */
void main() {
    FILE *fp,*fp1;
    int *a[MAXX],max_row,max_colm;
    int i=0,j=0,k=-1,prev=0,new=0,flag,l,pos,x,choice;
    char ch,fname[20],no[5]="0",temp[5];
    clrscr();
    
    printf("\n \n Word Segmentation Program \n \n");
    printf("\n Do You Want To Insert Your Own Matrix Or Go With The Pre-Created Source File \n");
    printf("\n Press 1. To Insert Your Own Matrix \n Press 2. To Go With The Pre-Created Matrix \n\n ");
    scanf("%d",&choice); 
    
    switch(choice) {
        case 1:
            insert();
            break;
        case 2:
        default:
            break;
    }
    max_colm=getmax();
    fp=fopen("source.txt","r");
    a[i]=(int *)malloc(max_colm*sizeof(int));
    
    do {
        ch=fgetc(fp);
        if(ch!='0'&&ch!='1'&&ch!=' '&&ch!='\n'&&ch!=EOF) {
            printf("\n Source file error !");
            getch();
            return;
        } 
        switch(ch) { 
            case '0':
                *(a[i]+j)=0;
                j++;
                break;
            case '1':
                *(a[i]+j)=1;
                j++;
                break;
            case '\n':
                i++;
                a[i]=(int *)malloc(max_colm*sizeof(int));
                j=0;
                break;
            default:
                break;
        };
    } while(ch!=EOF);
    
    max_row=i;
    fclose(fp);
    printf("\n Source File Read Succssfully\n");
    printf("\n\n Starting Segmentation...\n");
    /* Starting Segmentation */
    for(j=0;j<max_colm;j++) {
        flag=0;
        for(i=0;i<max_row;i++) {
            if(*(a[i]+j)==1) {
                prev=new;
                new=1;
                flag=1;
                break;
            }
        }
        if(flag==0) {
            prev=new;
            new=0;
        }
        if(prev==0&&new==1) {
            /* Creating Part Files Or Segmented Files */
            k++;
            strcpy(fname,"Part ");
            l=strlen(no);
            step:
            if(no[l-1]=='9') {
                no[l-1]='0';
                if(l==1) {
                    strcpy(temp,no);
                    strcpy(no,"1");
                    strcat(no,temp);
                }
                if(no[l-2]=='9') {
                    l--;
                    goto step;
                }
                else
                    no[l-2]++;
            }
            else
                no[l-1]++;
            strcat(fname,no);
            strcat(fname,".txt");
            remove(fname);
            pos=j;
        }
        if(((new==0)&&(prev==1))||((j==max_colm-1)&&(new==1))) {
            fp1=fopen(fname,"w");
            /* Writing Into The Segmented Files Previously Created */
            for(i=0;i<max_row;i++) {
                for(x=pos;x<j+new;x++) {
                    fprintf(fp1,"%d",*(a[i]+x));
                }
                fprintf(fp1,"\n");
            }
            fclose(fp1);
            printf("\n %s File Created \n",fname);
        }
    }
    printf("\n\n %d Total Part File(s) Created Successfully\n",k+1);
    printf("\n\n To View The Segmented Files \n Go To The Same Location Where The .exe
    File Of The Program Is Saved\n",k+1);
    printf("\n\n Thank You !\n",k+1);
    getch();
}
