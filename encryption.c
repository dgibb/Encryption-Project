//David Gibb
//Lab0
//ECE353

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

char generateKeyByte(char S[]);
int getKeyLength();
void fillKeyArray(char key[], char T[], int kLength);
void genSArray(char S[]);
void permutation(char S[], char T[]);
void encryption(char S[]); 
void swap(char *a, char *b);
     
int main(void){

    int kLength;
    char S[256];
    char T[256];

     kLength = getKeyLength();
     assert(kLength<=256);
     char key[kLength];
     fillKeyArray(key, T, kLength);
     genSArray(S);
     permutation(S,T);
     encryption(S); 
     return 0;
     }
   
 
    
    int getKeyLength(){
    
      int x=0;
      char keyChar;
      FILE *keyFile;
      keyFile = fopen("./keyFile.txt", "r");
      assert(keyFile != NULL);
      
      while ((keyChar = fgetc(keyFile))!=EOF && x<256) {
        x++;
      }
      fclose(keyFile);
      return x;
    }
    
    
    
     void fillKeyArray(char key [], char T[], int kLength){
     
       int x;
       int y;
       FILE *keyFile;
       char keyChar;
       
       keyFile = fopen("./keyFile.txt", "r");
       assert(keyFile != NULL);
       
       for (x=0; x<kLength; x++) {
         key[x] = fgetc(keyFile);
       }
     
       x=0;
       for (x=0; x<256; x++) {
         y=x%kLength;
         T[x] = key[y];
       } 
       fclose(keyFile);
     }
     
     
     
     void genSArray(char S[]){
       int x=0;
       for (x=0; x<256; x++) {
         S[x]=x;
       }
     }  
     
     
     
     void permutation(char S[], char T[]){
     
       int x=0;
       int y=0;
       for (x=0; x<256; x++) {
         y = (y+S[x]+T[x])%256;
         swap(&(S[x]), &(S[y]));
       }
     }
     
     
    
     void encryption(char S[]){
     
       char keyChar;
       char plainChar;
       char encryptChar;
       FILE *plainText;
       FILE *encryptedText;
       
       plainText = fopen("./encryptedText.txt", "r");
       encryptedText = fopen("./plainText.txt", "w");
       assert(plainText != NULL);
       assert(encryptedText != NULL);
      
       while ((plainChar = fgetc(plainText))!=EOF) {
       
         keyChar = generateKeyByte(S);
         encryptChar = keyChar ^ plainChar;
         fputc(encryptChar, encryptedText);
       }
       fclose(plainText);
       fclose(encryptedText);    
     }
     
     
     
    char generateKeyByte(char S[]) {
  
      int t;
      int i=0;
      int j=0;
      i = (i+1)%256;
      j = (j+S[i])%256;
      swap(&(S[i]), &(S[j]));
      t = (S[i]+S[j])%256;
      return S[t];
    }
    
    
    
    void swap(char *a, char *b){
       char c = *a;
       *a = *b;
       *b = c;
    }
       
  
    
