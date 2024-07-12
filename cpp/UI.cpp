#include "../headers/UI.hpp"

UI::UI() {
    Downloader downloader;
    downloader.download_video();
    downloader.get_video_title();
    downloader.convert_to_mp3();
    downloader.rename_file();
    downloader.delete_video();
}