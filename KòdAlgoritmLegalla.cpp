#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.foretsecurite.org"); // Mete adrès forè a
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Sove done yo
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); // Sove done vizitè yo
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verifye ke sètifika a legal
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Verifye ke non an pa yon fo non

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "Erreur cURL: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Donnée reçue: " << readBuffer << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
