#include "headers/downloader.hpp"

int main() {

    Downloader downloader;
    downloader.download_video();
    downloader.convert_to_mp3();
    downloader.delete_video();

return 0;

}
