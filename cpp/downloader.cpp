#include "../headers/downloader.hpp"
    
    

/* ---------------------------- DEFAULT SETTINNGS --------------------------- */
void Downloader::basic_setup(){
    video_file = "video_temp";
    
}

/* --------------------------- DEFAULT CONSTRUKTOR -------------------------- */
Downloader::Downloader() {
    basic_setup();

    std::cout << "YouTube URL: ";
    std::getline(std::cin, LINK);
}

/* ------------------------ CONSTRUKTOR W PARAMETERS ------------------------ */

Downloader::Downloader(std::string url) {
    basic_setup();
    LINK = url;
}


/* ---------------------------- DOWNLOAD PROCESS ---------------------------- */

void Downloader::download_video() {
    // YouTube URL input
        

    std::string download_command = "yt-dlp -o " + video_file + " " + LINK;
    // Execute the download command
    std::cout << "Downloading video..." << std::endl;
    
    int download_result = system(download_command.c_str());
    
    if (download_result != 0) {
        std::cerr << "Failed to download video." << std::endl;
        return;
    }

}