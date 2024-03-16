
#include <curl/curl.h>
#include <iostream>
#include <string>


// Callback function to write received data into a string buffer
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        // Replace "YOUR_API_KEY" with your actual Polygon.io API key
        // and adjust the URL to the specific API endpoint you need
        std::string url = "https://api.polygon.io/vX/reference/tickers?apiKey=jBRJtO_p2IL77FIrsS34JL4neTKxH6FC";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request, and check for errors
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Print the response for demonstration purposes
            std::cout << readBuffer << std::endl;
        }
        // Always cleanup
        curl_easy_cleanup(curl);
    }
    // Cleanup libcurl
    curl_global_cleanup();
    return 0;
}
