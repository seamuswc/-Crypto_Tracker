
#include "api.h"

//TEST
void test_api_returns_number(float (*func)(), const char* testName){
  float result = func();
  if( (result > 0)  && (result < 1000000) ){
    printf("\nPASSED %s", testName);
  }
  else{
    printf("\nFAILED %s ", testName);
  }
}
//TEST END

size_t writecallback(char *buffer, size_t itemsize, size_t nitems, struct memory* chunk) {

    size_t bytes = itemsize * nitems;

    chunk->memory = realloc(chunk->memory, chunk->size + bytes + 1);
    memcpy(&chunk->memory[chunk->size], buffer, bytes);
    chunk->size += bytes;
    chunk->memory[chunk->size] = 0;

    return bytes;
}

float api() {

    // if (test_wifi() != 0) {
    //     printf("NO WIFI\n");
    //     return 1;
    // }

    CURL *curl;
    CURLcode res; 

    struct memory chunk;
    chunk.memory = NULL;
    chunk.size = 0;
             
    curl = curl_easy_init();
            
    if(!curl) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        return 1;
    }

    char url[55];
    int url_length = snprintf ( url, 55, "https://api.coinbase.com/v2/prices/%s-USD/buy", coin );

    if(url_length > 55) {
            fprintf(stderr, "%s", "Input too Big\n");
            return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    res = curl_easy_perform(curl);

    float price;                                        
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        price = -1;
    } else {
        price = json_price(&chunk);
    }
    free(chunk.memory);
    curl_easy_cleanup(curl); 
    return price;
}


//{"data":{"base":"BTC","currency":"USD","amount":"41792.31"}} 
float json_price(struct memory *chunk) {

    //this makes sure that the returned data is not error data that would crash the program
    char * needle;
    needle = strstr(chunk->memory, "amount");
    if(needle == NULL) {
        fprintf(stderr, "Coin does not exist, or API failed");
        return -1;
    }

    char *ret;
    ret = strstr(chunk->memory, "amount") + 9;
    ret[strlen(ret)-3] = '\0';
    return atof(ret); //This adds multiple decimal places because C is dumb
}



int test_wifi() {

    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    //https port # are 443
    server_address.sin_port = htons(443);
    //google's IP
    server_address.sin_addr.s_addr = inet_addr("8.8.8.8");

    int connection_status = 
        connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
   
    close(network_socket);
    
    return connection_status;
}