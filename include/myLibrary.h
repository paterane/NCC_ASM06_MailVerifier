#ifndef MYLIBRARY_H
#define MYLIBRARY_H
#define true  1
#define false 0
int mapping(int number, int num_start, int num_end, int output_start, int output_end);
void wordUpper(char *word);
void wordLower(char *word);
int stringLen(const char *str); // note this function is only available for char array or string not for int array
int stringCmp(char *str1, char *str2);
void stringCopy(char *origin, char *buff);
int indexOf(char *str, char *idxStr);
char *subString(char *str, int idxA, int idxB);
int regExpress(char *str, char *pattern);

int mapping(int number, int num_start, int num_end, int output_start, int output_end){
    float rr = output_end - output_start;       // required range > rr 122-97
    float ar = num_end - num_start;             // actual range   > ar 122-0
    float mp = rr / ar;                         // mapping factor > mf > rr/ar
                                                // sample         > number
                                                // output         > number * mf
    int output = (number*mp)+output_start;      // b/t 97 & 122   > number * mf + output_start
    return output;
}

///************ String Upper Case to be modified ********///
void wordUpper(char *word){
    int i = 0;
    while(word[i] != '\0'){
        if(word[i] >= 97 && word[i] <= 122) word[i] -= 32;
        i++;
    }
}

///**************In case, lowercase to be used************///
void wordLower(char *word){
    int i = 0;
    while(word[i] != '\0'){
        if(word[i] >= 65 && word[i] <= 90) word[i] += 32;
        i++;
    }
}

/* Note: This func is only valid for char array, not for int array */
int stringLen(const char *str){
    int n=0;
    while(str[n++] != '\0');
    return n-1;
}

/* RETURN: -1 if not match , char count value if match*/
int stringCmp(char *str1, char *str2){
    int cnt=0;
    if(stringLen(str1) == stringLen(str2)){ //if length same, pass OR terminate func and return -1
        while(str1[cnt] != '\0'){
            if(str1[cnt] == str2[cnt])
                cnt++;
            else
                return -1;
        }
        return cnt;  //if every character is matched, return cnt
    }
    else
        return -1;
}

/*
 * Copy the content of origin to buff
 * */
void stringCopy(char *origin, char *buff){
    int len = stringLen(origin);
    for(int i=0; i<len; i++){
        buff[i] = origin[i];
    }
}

/*
 * let 'x' be length of str and 's' be length of idxStr
 * So, total numbers of available jumps is  'range = (x - s)+1'
 * Example, x = 5, s = 2
 * range=4 => so it jumps 4 times
 * */
// RETURN: -1 if indexString longer than the string or not found,and index position if found
// NOTE: this function will only work on first occurrence of the index.
int indexOf(char *str, char *idxStr){
    int cnt=0; int i=0; int found = false;
    if(stringLen(idxStr) < (stringLen(str))){
        int range = stringLen(str) - stringLen(idxStr) + 1;
        for(;cnt < range; cnt++){
            if(idxStr[i] == str[cnt]){
                found = true;
                if(i < stringLen(idxStr)-1)
                    i++;
                else{
                    break;
                }
            }
            else if(found){
                cnt--;
                i=0;
                found = false;
            }
        }
        if(found)
            return cnt-i;
        else
            return -1; // if not found
    }
    else{
        printf("Index length longer than the string!\n");
        return -1;
    }
}

/* continuous characters trimming in the string
 * continuous characters started from idxA upto idxB excluding character at idxB
 * RETURN: NULL if error indexing
 * */
char *subString(char *str, int idxA, int idxB){
    int length = stringLen(str); int x = 0;
    char *result = (char*)(malloc(length*sizeof(char)));
    if(idxA >= length || idxB > length || idxA >= idxB){
        printf("[ERROR!] indexing invalid!!!\n");
        return NULL;
    }
    for(int i=idxA; i<idxB; i++){
        result[x++] = str[i];
    }
    result[x] = '\0';
    return result;
}

/* "word Checker whether each character in the string existed in the patterns or not"
 * patterns => [start char] - [end char]
 * example  => a-z a,b,c,....,x,y,z
 * example  => 0-9 0,1,2,....,8,9
 * you can put any sequences from ascii table
 * RETURN: 1 if each character existed in patterns else 0
 * */
int regExpress(char *str, char *pattern){
    char pat_char[100] = {'\0'}; int pat_idx = 0;
    int pat_length = stringLen(pattern);
    int str_length = stringLen(str);
    for(int index=1; index < pat_length;){
        if(pattern[index] == '-'){
            if(index-1 <= index+1){
                for(char ch=pattern[index-1]; ch<=pattern[index+1]; ch++){
                    pat_char[pat_idx++] = ch;
                }
            }
            else
                printf("[-] Found pattern index error!!![pattern excluded]\n");
        }
        else{
            printf("[-] Found strange patter!!![pattern excluded]\n");
        }
        index += 3;
    }
    int i=0;
    int patChar_length = stringLen(pat_char);
    while(str[i] != '\0'){
        int found = false;
        for(int j=0; j<patChar_length; j++){
            if(str[i] == pat_char[j]){
                found = true;
                break;
            }
        }
        if(!found)
            return 0;
        i++;
    }
    return 1;
}
#endif