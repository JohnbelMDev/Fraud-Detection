#include <iostream>
#include <string>
#include <curl/curl.h>
#include <chrono>

// Callback function to handle data received from the server
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    // Append the received data to the string
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to perform an HTTP GET request through a proxy
bool performRequest(const std::string& proxy, const std::string& url, long& response_code, double& total_time) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Set the proxy server
        curl_easy_setopt(curl, CURLOPT_PROXY, proxy.c_str());
        // Set the callback function to handle the response data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Set the user pointer to pass to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // Follow redirects if necessary
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();
        // Perform the request
        res = curl_easy_perform(curl);
        // Stop the timer
        auto end = std::chrono::high_resolution_clock::now();

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        // Get the HTTP response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        // Calculate the total time taken for the request
        total_time = std::chrono::duration<double>(end - start).count();

        // Clean up
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return true;
}

int main() {
    // Proxy server address (e.g., "http://proxy.example.com:8080")
    std::string proxy = "http://your.proxy.server:port";
    // Target URL to request through the proxy
    std::string url = "http://www.example.com";

    long response_code = 0;
    double total_time = 0.0;

    if(performRequest(proxy, url, response_code, total_time)) {
        std::cout << "HTTP Response Code: " << response_code << std::endl;
        std::cout << "Total Time Taken: " << total_time << " seconds" << std::endl;
    } else {
        std::cerr << "Failed to perform the request." << std::endl;
    }

    return 0;
}
