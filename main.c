#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memLength 30000

int lengthOfString(char* n) {
  int counter = 0;
  while(n[counter] != 0 && n[counter] != -1) {
    ++counter;
  }
  return counter;
}

void arrcpy(int* arr1, int* arr2, int len) {
  for(int i = 0; i < len - 1; ++i) {
    arr1[i] = arr2[i];
  }
}

void evaluate(char* code, int len) {
  int b = 0;
  int i = -1;
  int memory[memLength] = {0};
  int memPointer = 0;


  int startsLength = 0;
  int* starts = malloc(startsLength * sizeof(int));

  while(i < len) {
    ++i;
    if(code[i] == '+') {
      ++memory[memPointer];
    } else if (code[i] == '-') {
      --memory[memPointer];
    } else if (code[i] == '>') {
      if(memPointer < memLength) {
        ++memPointer;
      } else {
        printf("Error: Index %i out of range\n", memPointer);
        exit(-1);
      }
    } else if (code[i] == '<') {
      if(memPointer > 0) {
        --memPointer;
      } else {
        printf("Error: Index %i out of range\n", memPointer);
        exit(-1);
      }
    } else if (code[i] == '[') {
      if(memory[memPointer] != 0) {
        int* temp = starts;
        ++startsLength;
        starts = malloc(startsLength * sizeof(int));
        arrcpy(starts, temp, startsLength);
        starts[startsLength - 1] = i;
      } else {
        b = 0;
        ++i;
        while(!(code[i] == ']' && b == 0)) {
          if(code[i] == ']') {
            --b;
          } else if (code[i] == '[') {
            ++b;
          }
          ++i;
        }
      }
    } else if (code[i] == ']') {
      if(memory[memPointer] != 0) {
        i = starts[startsLength - 1];
      } else {
        int* temp = starts;
        --startsLength;
        starts = malloc(startsLength * sizeof(int));
        arrcpy(starts, temp, startsLength + 1);
      }
    } else if (code[i] == '.') {
      printf("%c", memory[memPointer]);
    } else if (code[i] == ',') {
      system ("/bin/stty raw");
      memory[memPointer] = fgetc(stdin);
      system ("/bin/stty cooked");
    } else {
      // Do nothing
    }
  }
}


int main(int argc, char* argv[]) {
  FILE* code = fopen(argv[1], "r");
  char current = 'a';
  int length = 0;
  char* str = malloc(length * sizeof(char*));
  while(current != -1) {
    ++length;
    char* temp = str;
    str = malloc(length * sizeof(char*));
    strcpy(str, temp);
    current = fgetc(code);
    str[length - 1] = current;
  }
  fclose(code);
  int codeLength = lengthOfString(str);
  evaluate(str, codeLength);
  return 0;
}