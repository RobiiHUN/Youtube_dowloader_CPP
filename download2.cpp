#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <fstream>
#include "nlohmann/json.hpp" 

using json = nlohmann::json;

std::string escapeShellArg(const std::string &arg) {
    std::string escaped = "'";
    for (char c : arg) {
        if (c == '\'') {
            escaped += "'\\''";  // escape single quotes
        } else {
            escaped += c;
        }
    }
    escaped += "'";
    return escaped;
}

std::string getVideoTitle(const std::string &url) {
    std::string json_file = "video_info.json";
    std::string command = "yt-dlp --print-json " + escapeShellArg(url) + " > " + json_file;

    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to retrieve video info." << std::endl;
        return "";
    }

    std::ifstream ifs(json_file);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return "";
    }

    json j;
    ifs >> j;
    ifs.close();

    std::remove(json_file.c_str()); // Remove the temporary JSON file

    std::string title = j["title"];
    std::replace(title.begin(), title.end(), ' ', '_'); // Replace spaces with underscores
    return title;
}

int main() {
    // YouTube URL
    std::string url;
    std::cout << "Enter the YouTube URL: ";
    std::getline(std::cin, url);

    // Temporary file name for video
    std::string temp_video_file = "temp_video.webm";
    // Temporary file name for audio
    std::string temp_audio_file = "temp_audio.mp3";

    // Command to download the video using yt-dlp
    std::string download_command = "yt-dlp -o " + escapeShellArg(temp_video_file) + " " + escapeShellArg(url);

    // Execute the download command
    std::cout << "Downloading video..." << std::endl;
    int download_result = system(download_command.c_str());
    if (download_result != 0) {
        std::cerr << "Failed to download video." << std::endl;
        return 1;
    }

    // Command to convert the video to mp3 using ffmpeg
    std::string convert_command = "ffmpeg -i " + escapeShellArg(temp_video_file) + " -q:a 0 -map a " + escapeShellArg(temp_audio_file);

    // Execute the convert command
    std::cout << "Converting video to MP3..." << std::endl;
    int convert_result = system(convert_command.c_str());
    if (convert_result != 0) {
        std::cerr << "Failed to convert video to MP3." << std::endl;
        return 1;
    }

    // Get video title
    std::string title = getVideoTitle(url);
    if (title.empty()) {
        return 1;
    }

    // Final MP3 file name
    std::string final_audio_file = title + ".mp3";

    // Rename the temporary audio file to the final name
    std::string rename_command = "mv " + escapeShellArg(temp_audio_file) + " " + escapeShellArg(final_audio_file);
    int rename_result = system(rename_command.c_str());
    if (rename_result != 0) {
        std::cerr << "Failed to rename audio file." << std::endl;
        return 1;
    }

    // Remove the temporary video file
    std::remove(temp_video_file.c_str());

    std::cout << "MP3 file created successfully: " << final_audio_file << std::endl;
    return 0;
}
