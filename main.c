#include<stdio.h>
#include<string.h>

const int MIN = 8; // Minimum password caracters number
const char CYAN[8] = "\x1b[35m"; // Cyan color
const char RESET[7] = "\x1b[0m"; // reset color(to white)

/* 
This function search for a character val in a given string str.
It get string(str[]), caracter(val)
Return 1 if it exist , 0 otherwise.
*/
int searchTable(char str[], char val)
{
    for(int i = 0;i<strlen(str);i++)
    {
        if(str[i] == val) return 1;
    }
    return 0;
}

/* This function help validate each requirement ( it used to eleminate repetition and make code more clean) */
/*
It search each character of the password[] in the set of characters table[]
It get string(p[]), string(table[])
Return 1 if a character in the password exist in table[], 0 if no character of the password exist in table[].
*/
int validator(char p[], char table[])
{
    for (int i=0;i<strlen(p);i++)
    {
	    if(searchTable(table,p[i])) return 1;
    }
    return 0;
}

/*
Check pasword length requirement
It git password(p[]) , intger(min)
Return 1 if password length is greater or equal to min , 0 otherwise.
*/
int checkLength(char p[], int min)
{
    if (strlen(p) >= min) return 1;
    else return 0;
}

/*
Check if password has an uppercase
It git password(p[])
Return 1 if password has an uppercase, 0 otherwise.
*/
int hasUppercase(char p[])
{
    char upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return validator(p,upper);
}

/*
Check if password has a lowercase
It git password(p[])
Return 1 if password has a lowercase, 0 otherwise.
*/
int hasLowercase(char p[])
{
    char lower[26] = "abcdefghijklmnopqrstuvwxyz";
    return validator(p,lower);
}

/*
Check if password has a digit
It git password(p[])
Return 1 if password has a digit, 0 otherwise.
*/
int hasDigit(char p[])
{
    char digits[10] = "0123456789";
    return validator(p,digits);
}

/*
Check if passsword has a special character
It git password(p[])
Return 1 if password has a special chracter, 0 otherwise.
*/
int hasSpecialChar(char p[])
{
    char special[20] = "!#$%&*+-=?^_";
    return validator(p,special);
}

/*
Check if password has no spaces
It git password(p[])
Return 1 if password has no spaces , 0 otherwhise.
*/
int hasNoSpace(char p[])
{
    return !searchTable(p,' ');
}

/*
Calculate password strength
It git password(p[])
call each validator and calculate score
Return score.
*/
int calculateStrength(char p[])
{
    int score = checkLength(p,8) + hasLowercase(p) + hasUppercase(p) + hasDigit(p) + hasSpecialChar(p) + hasNoSpace(p);
    return score;
}

/*
Print the feedback
It git password(p[])
Call each validator and calculateStrength
Print the feedback
*/
void printFeedback(char p[])
{
    int score = calculateStrength(p);
    printf("Score: %s'%d/6'%s   ",CYAN,score,RESET);
    switch(score)
    {
        case 2:
        printf("[!] Weak - significant improvements needed.");
        break;
        case 3:
        printf("[ ] Fair - getting there, but not safe yet.");
        break;
        case 4:
        printf("[+] Good - a few tweaks and you are set.");
        break;
        case 5:
        printf("[!] Strong - almost perfect.");
        break;
        case 6:
        printf("[!] Very Strong - excellent password.");
        break;
        default:
        printf("[!] Very Weak - do not use this password.");
    }
    if(score<6){
        printf("\nMissing requirements:\n");
        if(!checkLength(p,MIN))
        {
            printf("  - At least 8 characters        (current: %d)\n",strlen(p));
        }
        if(!hasUppercase(p))
        {
            printf("  - At least one uppercase letter\n",strlen(p));
        }
        if(!hasLowercase(p))
        {
            printf("  - At least one lowercase letter\n",strlen(p));
        }
        if(!hasDigit(p))
        {
            printf("  - At least one digit\n",strlen(p));
        }
        if(!hasSpecialChar(p))
        {
            printf("  - At least one special character (!#$%&*+-=?^_)\n",strlen(p));
        }
        if(!hasNoSpace(p))
        {
            printf("  - Do not use spaces\n",strlen(p));
        }
    }
    else
    {
        printf("\nAll requirements satisfied.\n");
    }
}

int main()
{
    char p[20]; // password string
    char h; // helping character
    printf("Enter password (or %s'q'%s to quit): ",CYAN,RESET);
    scanf("%[^\n]",p);
    while(strcmp(p,"q"))
    {
        printFeedback(p);
        printf("Enter password (or %s'q'%s to quit): ",CYAN,RESET);
        scanf("%[\n]",&h); // Try comment it
		/* This scan is used to fix infinite loop cycle that happen because of new line character*/
        scanf("%[^\n]",p);
    }
}
