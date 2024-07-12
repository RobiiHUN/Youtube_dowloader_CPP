#include "../headers/downloader.hpp"
    
    
    
    void download_video() {
    // YouTube URL input
    std::string url;
    std::cout << "YouTube URL: ";
    std::getline(std::cin, url);

    // Temporary file name for video
    std::string video_file = "video_temp.mp4.webm"; 


    // Command to download the video using yt-dlp
    std::string download_command = "yt-dlp -o " + video_file + " " + url;

    // Execute the download command
    std::cout << "Downloading video..." << std::endl;
    int download_result = system(download_command.c_str());
    if (download_result != 0) {
        std::cerr << "Failed to download video." << std::endl;
        return;
    }

}