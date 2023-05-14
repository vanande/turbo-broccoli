#include <stdio.h>
#include <curl/curl.h>
#include <time.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("%.*s\n", size * nmemb, ptr);
    return size * nmemb;
}


void showNum(char *s){
    int i = 0;
    while(s[i] != '\0'){
        printf("\n%c = %d", s[i], s[i]);
        i++;
    }
}

char* replaceSpecialChar(char *str) {
    int specialCharInt[] = {-126, -118, -123, -105}; // é, è, à, ù
    char replaceCharInt[] = {101, 101, 97, 117}; // e, e, a, u

    int i,j = 0;

    while (str[i] != '\0') {
        for (j = 0; j < 4; j++) {
            if (str[i] == specialCharInt[j]) {
                str[i] = replaceCharInt[j];
            }
        }
        i++;
    }
    return str;
}

int main(int argc, char ** argv) {
    CURL *curl;
    CURLcode res;
    char *response = NULL;
    char question[40];


    printf("Welcome to the FAQ system. Ask your question and we will try to answer it.\n");
    do {


        printf("\nType your question: ");
        fgets(question, 40, stdin);
        if (question[strlen(question) - 1] == '\n') {
            question[strlen(question) - 1] = '\0';
        }

        //showNum(question);
        //printf("\nQuestion old : %s", question);

        strcpy(replaceSpecialChar(question), question);
        //printf("\nQuestion new : %s", question);


        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9000/faq");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, question);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);

        }
    } while (strcmp(question, "exit") != 0);
    return 0;
}