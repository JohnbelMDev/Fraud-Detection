#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Callback function to write data received by libcurl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Function to fetch webpage content
std::string fetchWebpage(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify the peer's SSL certificate
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Verify that the host name matches the certificate

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}

// Function to load the baseline content from a file
std::string loadBaseline(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to save the current content as the new baseline
void saveBaseline(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

// Function to compare two strings and detect changes
bool detectChanges(const std::string& oldContent, const std::string& newContent) {
    return oldContent != newContent;
}

int main() {
    const std::string url = "https://www.klinikpam.com/notre-clinique";
    const std::string baselineFile = "baseline.html";

    // Fetch the current content of the webpage
    std::string currentContent = fetchWebpage(url);

    // Load the baseline content
    std::string baselineContent = loadBaseline(baselineFile);

    // Compare the current content with the baseline
    if (detectChanges(baselineContent, currentContent)) {
        std::cout << "Changes detected on the webpage." << std::endl;
        // Save the current content as the new baseline
        saveBaseline(baselineFile, currentContent);
        // Implement notification logic here (e.g., send an email)
    } else {
        std::cout << "No changes detected." << std::endl;
    }

    return 0;
}
