#include <iostream>
#include <cstdlib>
#include <string>

int main() {
    // YouTube URL
    std::string url;
    std::cout << "Enter the YouTube URL: ";
    std::getline(std::cin, url);

    // Temporary file name for video
    std::string video_file = "video_temp.mp4.webm"; // Update this to match the yt-dlp output
    // Output MP3 file name
    std::string audio_file = "output.mp3";

    // Command to download the video using yt-dlp
    std::string download_command = "yt-dlp -o " + video_file + " " + url;
    // Command to convert the video to mp3 using ffmpeg
    std::string convert_command = "ffmpeg -i " + video_file + " -q:a 0 -map a " + audio_file;

    // Execute the download command
    std::cout << "Downloading video..." << std::endl;
    int download_result = system(download_command.c_str());
    if (download_result != 0) {
        std::cerr << "Failed to download video." << std::endl;
        return 1;
    }

    // Execute the convert command
    std::cout << "Converting video to MP3..." << std::endl;
    int convert_result = system(convert_command.c_str());
    if (convert_result != 0) {
        std::cerr << "Failed to convert video to MP3." << std::endl;
        return 1;
    }

    // Remove the temporary video file
    std::remove(video_file.c_str());

    std::cout << "MP3 file created successfully: " << audio_file << std::endl;
    return 0;
}
