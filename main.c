/* CURRENTLY WORKING ONLY FOR ENGLISH AND GREEKLISH. May add Greek soon*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#define SIZE 30 //Max Size of a word in the dictionary

char **insert(char **table,int *number)
{
    int indexgreek,indexenglish,i;
    char **table2;
    char greek[SIZE],english[SIZE];
    printf("Type the greek word you want to add: ");
    gets(greek);
    indexgreek=search(table,*number,greek);
    changetolower(greek);
    printf("Type the english equivalent: ");
    gets(english);
    printf("\n");
    indexenglish=search(table,*number,english);
    changetolower(english);
    if (indexgreek!=-1 || indexenglish!=-1)
        printf("One of the two words you are trying to add, already exists in the dictionary.\n\n");
    else
    {
        table2=(char **)malloc((*number+2)*sizeof(char *));
        if (table2==NULL)
            printf("Not enough memory to allocate...Aborting\n\n");
        else
        {
            *(table2+(*number))=(char *)malloc((strlen(greek)+1)*sizeof(char));
            *(table2+(*number)+1)=(char *)malloc((strlen(english)+1)*sizeof(char));
            if (*(table+(*number))==NULL || *(table+(*number)+1)==NULL)
                printf("Not enough memory to allocate...Aborting\n\n");
            else
            {
                for (i=0;i<=*number-1;i++)
                    *(table2+i)=*(table+i);
                free(table);
                table=table2;
                strcpy(*(table+(*number)),greek);
                strcpy(*(table+(*number)+1),english);
                *number=*number+2;
            }
        }
    }
    return table;
}


int search(char **table,int number,char word[])
{
    int i,flag=1,index=-1;
    for (i=0;i<=number-1 && flag;)
        if (xstrcmp(*(table+i),word)==0)
        {
            index=i;
            flag=0;
        }
        else
            i++;
    return index;
}





void edit(char **table,int number)
{
    int index,index1,index2;
    char temp[SIZE],temp1[SIZE],temp2[SIZE],*point1,*point2,temp21[SIZE];
    printf("Insert the word you wish to edit: ");
    gets(temp);
    index=search(table,number,temp);
    if (index==-1)
    {

        index=search(table,number,temp);

    }
    if (index%2==1)
        index--;
    strcpy(temp,*(table+index));
    strcpy(temp21,*(table+index+1));
    strcpy(*(table+index),"0");
    strcpy(*(table+index+1),"1");
    printf("Greek word edit: ");
    gets(temp1);
    changetolower(temp1);
    printf("English word edit: ");
    gets(temp2);
    changetolower(temp2);
    printf("\n");
    index1=search(table,number,temp1);
    index2=search(table,number,temp2);
    if (index1!=-1 || index2!=-1)
    {
        printf("At least one word is already in the dictionary.\n\n");
        strcpy(*(table+index),temp);
        strcpy(*(table+index+1),temp21);
        return;
    }
    else
    {
        point1=(char *)realloc(*(table+index),(strlen(temp1)+1)*sizeof(char));
        point2=(char *)realloc(*(table+index+1),(strlen(temp2)+1)*sizeof(char));
        if (point1==NULL || point2==NULL)
        {

            printf("Could not allocate enough memory...\n\n");

            return;
        }
        else
        {
            free(*(table+index));
            free(*(table+index+1));
            *(table+index)=point1;
            *(table+index+1)=point2;
            strcpy(*(table+index),temp1);
            strcpy(*(table+index+1),temp2);
            return;
        }
    }
}

char **deleteword(char **table,int *number)
{
    int i,index;
    char temp[SIZE],*point1,*point2,**table2;
    printf("Type the word you wish to delete: ");
    gets(temp);
    index=search(table,*number,temp);

    if (index==-1)
    {
        printf("Word does not exist in the dictionary\n");
    }
    if (index%2==1)
        index--;
    point1=*(table+index);
    point2=*(table+index+1);
    *(table+index)=(char *)realloc(*(table+index),(strlen(*(table+(*number)-2))+1)*sizeof(char));
    *(table+index+1)=(char *)realloc(*(table+index+1),(strlen(*(table+(*number)-1))+1)*sizeof(char));
    if (*(table+index)==NULL || *(table+index+1)==NULL)
    {
        printf("Not enough memory to allocate\n\n");
        *(table+index)=point1;
        *(table+index+1)=point2;
        return table;
    }
    else
    {
        strcpy(*(table+index),*(table+(*number)-2));
        strcpy(*(table+index+1),*(table+(*number)-1));
        *number=*number-2;
        table2=(char **)malloc((*number)*sizeof(char *));
        if (table2==NULL)
        {
            printf("Not enough memory...\n\n");
            return table;
        }
        else
        {
            for (i=0;i<=*number-1;i++)
                *(table2+i)=*(table+i);
            free(*(table+(*number)));
            free(*(table+(*number)+1));
            free(table);
            return table2;
        }
    }
}
/* TRANSLATIONS AHEAD */

char *trans(char **table,int number,char word[])
{
    int index;
    char temp[SIZE];
    strcpy(temp,word);
    index=search(table,number,temp);
    if (index==-1)
    {

        printf("Word does not exist in the dictionary.\n");
    }
    if (index%2==0)
        return *(table+index+1);
    else
        return *(table+index-1);
}


char *transSentenceHelper(char **table,int number,char word[])
{
    int index;
    index=search(table,number,word);
    if (index==-1)
        return NULL;
    else
    {
        if (index%2==0)
            return *(table+index+1);
        else
            return *(table+index-1);
    }
}


void translA(char **table,int number)
{
    char temp1[SIZE],*temp2;
    int index;
    printf("Type the word to be translated: ");
    gets(temp1);
    temp2=trans(table,number,temp1);
    if (temp2!=NULL)
    {
        index=search(table,number,temp2);
        if (index%2==0)
            strcpy(temp1,*(table+index+1));
        else
            strcpy(temp1,*(table+index-1));
        printf("Translation: %s is %s\n\n",temp1,temp2);
    }
    return;
}

void translsentence(char **table,int number)
{
    char temp[SIZE]="0",*point,c;
    int count=0,i;
    printf("Type the sentence you wish to be translated:\n");
    fflush(stdin);
    do
    {
        i=0;
        do
        {
            scanf("%c",&c);
            if (c!=10 && c!=32 && c!=9)
            {
                temp[i]=c;
                i++;
            }
        }
        while(c!=10 && c!=32 && c!=9);
        temp[i]='\0';
        point=transSentenceHelper(table,number,temp);

        if (point==NULL)
        {
            printf("%s ",temp);
            count++;
        }
        else
            printf("%s ",point);
    }
    while(c!=10);
    printf("\n\n");
    if (count!=0)
        printf("%d word(s) could not be translated. Sorry about that...\n\n",count);
    return;
}


void changetolower(char L[])        //inserting words on lower case so we don't have to deal with that
{
    int i;
    for (i=0;L[i]!='\0';i++)
        L[i]=tolower(L[i]);
}

int xstrcmp(char L[],char K[])      //compares disregarding upper or lower case
{
    int i;
    for (i=0;L[i]!='\0' || K[i]!='\0';i++)
        if (toupper(L[i])>toupper(K[i]))
            return 1;
        else if (toupper(L[i])<toupper(K[i]))
            return -1;
    return 0;
}


int main()
{
    FILE *read,*write;
    int number,i,flag;
    char **table;
    char k,temp[SIZE];
    read=fopen("dict.txt","r");
    if (read==NULL)
    {
        printf("Could not read from file...\n\n");
        fclose(read);
    }
    else
    {
        printf("LOADING... ");
        fscanf(read,"%d\n",&number);
        table=(char **)malloc(number*sizeof(char *));
        if (table==NULL)
        {
            printf("Could not read from file. Aborting...\n\n");
            fclose(read);
        }
        else
        {
            flag=1;
            for (i=0;i<=number-1 && flag;i++)
            {
                    fscanf(read,"%s\n",temp);
                    *(table+i)=(char *)malloc((strlen(temp)+1)*sizeof(char));
                    if (*(table+i)!=NULL)
                        strcpy(*(table+i),temp);
                    else
                        flag=0;
            }
            if (flag==0)
            {
                printf("Not enough memory\n");
                fclose(read);
            }
            else
            {
                if (ferror(read)==0)
                    printf("Good to go.\n");
                else
                    printf("There may be an error.Program may crash.\n\n");
                fclose(read);
                do
                {
                    printf("1. Insert word\n"
                           "2. Edit word\n"
                           "3. Delete word\n"
                           "4. Translate word\n"
                           "5. Translate sentence\n"
                           "6. Exit\n"
                           "You wish to: ");
                    do
                        k=getch();
                    while (k!='1' && k!='2' && k!='3' && k!='4' && k!='5' && k!='6');
                    printf("%c\n\n",k);
                    switch(k)
                    {
                        case '1':
                            table=insert(table,&number);
                            break;
                        case '2':
                            edit(table,number);
                            break;
                        case '3':
                            if (number>0)
                                table=deleteword(table,&number);
                            else
                                printf("Word does not exist.\n");
                            break;
                        case '4':
                            translA(table,number);
                            break;
                        case '5':
                            translsentence(table,number);
                            break;
                    }
                }
                while(k!='6');
                printf("Do you wish to save changes to your dictionary? Y/N  ");
                do
                    k=getch();
                while(k!='N' && k!='Y' && k!='n' && k!='y');
                printf("%c\n\n",tolower(k));
                if (k=='y' || k=='Y')
                {
                    write=fopen("dict.txt","w");
                    if (write==NULL)
                        printf("Error writing to file.\n");
                    else
                    {
                        fprintf(write,"%d\n",number);
                        for (i=0;i<=number-1;i++)
                            fprintf(write,"%s\n",*(table+i));
                    }
                    if (ferror(write)==0)
                        printf("Save succesfull.\n");
                    else
                        printf("Error saving file. \n");
                    fclose(write);
                }
            }
        }
    }
    system("PAUSE");
    return 0;
}
