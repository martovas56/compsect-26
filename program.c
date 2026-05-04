#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void md5_string(char *str, char *output){
  char command[100];
  char buffer[100];
  
    sprintf(command, "echo -n %s | md5sum", str);
    FILE *fp = popen(command, "r");
    
    if(fp == NULL) return;
    
    fgets(buffer, sizeof(buffer), fp);
    pclose(fp);
    
    strncpy(output, buffer, 32);
    output[32] = '\0';
  }


int main(){
  char target[]="e10adc3949ba59abbe56e057f20f883e";
  char candidate[10];
  char hash[33];
  
  strcpy(candidate, "pwd_");
  
  for(char a = 'a'; a <= 'z'; a++){
    for(char b = 'a'; b <= 'z'; b++){
      for(char c = 'a'; c <= 'z'; c++){
      
        candidate[4] = a;
        candidate[5] = b;
        candidate[6] = c;
        candidate[7] = '\0';
        
        md5_string(candidate, hash);
        
      if(strcmp(hash, target) == 0) {
        printf("Password found: %s\n", candidate);
        return 0;
      }
    }
  }
}

  printf("Password not found.\n");
  return 0;
} 
  
