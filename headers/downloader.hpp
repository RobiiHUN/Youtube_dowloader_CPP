#include "includes.h"



/* ========================================================================== */
//!                              YOUTUBE-DL CLASS                             //
/* ========================================================================== */

class Downloader {
    private:
        std::string video_file;
        std::string LINK;
        

    public:
        /* ------------------------------ CONSTRUKTORS ------------------------------ */
        Downloader();
        Downloader(std::string url);
        void basic_setup();

        /* ---------------------------- DOWNLOAD PROCESS ---------------------------- */
        void download_video();
        void convert_to_mp3();
        void delete_video();
        
};

