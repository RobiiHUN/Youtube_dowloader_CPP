#include "../headers/downloader.hpp"
    
    

/* ========================================================================== */
//!                              YOUTUBE-DL CLASS                             //
/* ========================================================================== */


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

/* --------------------------- CONVERTING PROCESS --------------------------- */

void Downloader::convert_to_mp3() {
    std::string mp3_file = video_file + ".mp3";
    std::string convert_command = "ffmpeg -i " + video_file + ".mp4" + " -vn -ar 44100 -ac 2 -ab 192k -f mp3 " + mp3_file;
    // Execute the convert command
    std::cout << "Converting video to mp3..." << std::endl;
    int convert_result = system(convert_command.c_str());
    if (convert_result != 0) {
        std::cerr << "Failed to convert video to mp3." << std::endl;
        return;
    }
    std::cout << "Video successfully converted to mp3." << std::endl;
}

/* ---------------------------- DELETE PROCESS ---------------------------- */
void Downloader::delete_video() {
    std::string delete_command = "rm " + video_file + ".mp4";
    

    std::cout << "Deleting video..." << std::endl;
    
    int delete_result = system(delete_command.c_str());
    if (delete_result != 0) {
        std::cerr << "Failed to delete video." << std::endl;
        return;
    }
    
}