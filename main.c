#include <stdio.h>
#include <curl/curl.h>
#include <time.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("%.*s\n", size * nmemb, ptr);
    return size * nmemb;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char *response = NULL;
    char question[40];

    printf("\nType your question: ");
    fgets(question, 40, stdin);
    if (question[strlen(question) - 1] == '\n') {
        question[strlen(question) - 1] = '\0';
    }

    //printf("The question is %s\n", question);

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
    return 0;
}
