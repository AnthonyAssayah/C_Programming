#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define TXT 1024
#define WORD 30
int Gematria(char str1[]); 
int valueOf(char ch);
void functionA(char txt[], char word[]);
char* Atbash(char str1[]);
char* revstr(char *str1);
void functionB(char txt[], char word[]);
int functionB1(char txt[], char word[]);
void functionB2(char txt[], char word[]);
int functionC(char txt[], char word[]);



int Gematria(char str1[]) {

    int num = 0;
    // loop over the text, check if the char[i] is valid, assign value
    for ( int i = 0; i < strlen(str1); i++ ) {
        num += valueOf(str1[i]);
    }
    return num;
}
int valueOf(char ch) {
    int num = 0;
    if (ch >= 'A' && ch <= 'Z')
        num = ch - 'A' + 1;
    else if (ch >= 'a' && ch <= 'z')
        num = ch - 'a' + 1;
    return num;
}

void functionA(char txt[], char word[]) {

    const int sum = Gematria(word);
    int first = 1;
    printf("Gematria Sequences: %s", "");

    for(int i = 0; i < strlen(txt) - 1; i++) {

        for(int j = i + 1 ; j < strlen(txt); j++) {

            char txtsub[TXT];
            strcpy(txtsub, "");
            memcpy(txtsub, &txt[i], j - i);
            txtsub[j - i] = '\0';
            char firstchar = txtsub[0];
      
            if (Gematria((char[1]){txtsub[(int)(strlen(txtsub) - 1)]}) == 0) {
                continue;
            }
            if (valueOf(firstchar) == 0 || Gematria(txtsub) > sum) {
                break;
            }
            if (sum == Gematria(txtsub))
            {
                if (first){
                    printf("%s", txtsub);
                    first = 0;
                }
                else {
                    printf("~%s", txtsub);
                }
                break;
            }
        }
    }
    printf("%s\n", "");
}




char* Atbash(char str1[]) {

    char* c;
    c = malloc(sizeof(char)*strlen(str1));
    // loop over the text, check if the char[i] is valid, assign value
    for ( int i = 0; i < strlen(str1); i++ ) {

        if (str1[i] >= 'A' && str1[i] <= 'Z') {
            c[i] = 'Z' - (str1[i] - 'A') ;
        }
        else if (str1[i] >= 'a' && str1[i] <= 'z') {
            c[i] = 'z' - (str1[i] - 'a') ;
        }
   }
   return c;
}

char* revstr(char *str1)  
{  
    int len = strlen(str1);
    char* c;
    c = malloc(sizeof(char)*len);  
   
    for (int i = 0; i < len/2; i++)  
    {  
        c[i] = str1[len - i - 1];  
        c[len - i - 1] = str1[i];  
    }  
    return c;
}

void functionB(char txt[], char word[]) {

    printf("%s", "Atbash Sequences: ");
    int printed = functionB1(txt, revstr(Atbash(word)));

    if (printed) {
        printf("%s", "~");
    }
    functionB1(txt, Atbash(word)); 
    printf("%c", '\n');
}

int functionB1(char txt[], char word[]) {
    int success = 0;
    int j = 0, k = 0;
    char savedWord[TXT] = "";
    int first = 1;
    for(int i = 0; i < strlen(txt); i++) {
        if (txt[i] == word[j]) {
            savedWord[k] = txt[i];
            k++;
            j++;
        }
        else if (txt[i] == ' ' || txt[i] == '\n' || txt[i] == '\t') {
            savedWord[k] = txt[i];
            k++;
        }
        else {
            j = 0;
            strcpy(savedWord, "");
            k =0;
        }
        if (j == strlen(word)) {
            if (first) {
                printf("%s",savedWord);
                first = 0;
                success = 1;
            }
            else {
                printf("%s",savedWord);
                success = 1;
            }
            j = 0;
             strcpy(savedWord, "");
        }
    }
    return success;
}
int iszero(int arr[], int size) {
    for (int i = 0 ; i < size ; i++) {
        if (arr[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void arr_copy(int word[], int txt[],int size) {
    for(int i =  0; i < size ; i++ ){
        word[i] = txt[i];
    }
}

int valid_word(char word[]) {
    int flag = 0;
    for (int i = 0;i < strlen(word); i++) {
        if(valueOf(word[0]) == 0 || valueOf(word[strlen(word) - 1]) == 0) {
            return flag;
        }
        flag = 1;
    }
    return flag;
}

int functionC(char txt[], char word[]) {

    int value[TXT];
    int temp[TXT];
    int k = 0;
    int first = 1, success = 0;
    char savedWord[TXT] = "";
    printf("%s", "Anagram Sequences: ");
    // zero out the values array
    for(int i = 0; i < TXT; i++) {
        value[i] = 0;
    }
    // fill the array with the contents of the word
    for (int i = 0 ; i < strlen(word) ; i++) {
        value[(int)word[i]]++;
    }
    arr_copy(temp, value, TXT);
    for (int i = 0 ; i < strlen(txt) - strlen(word) ; i++) {
        for (int j = i; j < strlen(txt) ; j++) {
            if (temp[(int)txt[j]] > 0) {
                temp[(int)txt[j]]--;
                savedWord[k] = txt[j];
                //printf("-%s-", savedWord);
                k++;
            }
            else if (valueOf(txt[j]) != 0 && temp[(int)txt[j]] <= 0) {
                strcpy(savedWord, "");
                k = 0;
                arr_copy(temp, value, TXT);
                break;
            }
            else if ((txt[j] == ' ' || txt[j] == '\n' || txt[j] == '\t') && k != 0) {
                temp[(int)txt[j]]--;
                savedWord[k] = txt[j];
                k++;
            }
            else if (valueOf(txt[j]) == 0) {
                strcpy(savedWord, "");
                k = 0;
                arr_copy(temp, value, TXT);
                break;
            }
            if (iszero(temp, 256)) {
                if (first) {
                    printf("%s", savedWord);
                    first = 0;
                }
                else {
                    printf("~%s", savedWord);
                }
                  strcpy(savedWord, "");
                break;          
            }
        }
    }
    if (!first) {
        success = 1;
    }
    return success;
}



int main() {

    char word[WORD];
    char str1[TXT];

    scanf("%s", word);
    int i = 0;
    char c;
    while ( c < TXT) {
        scanf("%c", &c);
        if ( c == '~') {
            break;
        }
        str1[i] = c;
        i++;    
    }
   

    functionA(str1,word);
    functionB(str1,word);
    functionC(str1,word);
   
    return 0;
}
