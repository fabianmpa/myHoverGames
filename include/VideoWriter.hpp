#pragma once
#include <opencv2/opencv.hpp>

class Video_Writer
{
public:
    /**
     * @brief Default constructor.
     *
     * Underlying open cv video writer object will be instantiated.
     */
    Video_Writer() = default;

    ~Video_Writer()= default;

    /**
     * @brief Initialises video file writer.
     *
     * Opens opencv writer with given params. FFMPEG backend is used.
     *
     * @param outputVideo path to the video file.
     * @param encoding cv::CAP_PROP_FOURCC code.
     * @param fps target frame rate.
     * @param width target frame width.
     * @param height target frame height.
     *
     */
    void Init(const std::string& outputVideo,double fps, int width, int height);

    /**
     * Writes frame to the file using opencv writer.
     *
     * @param frame data to write.
     */
    void WriteFrame(std::shared_ptr<cv::Mat>& frame);

    /**
     * Releases opencv writer.
     */
    void Close();

    /**
     * Checks if opencv writer was successfully opened.
     * @return true is underlying writer is ready to be used, false otherwise.
     */
    bool IsReady() const;


private:
    cv::VideoWriter m_cvWriter{};
    bool m_ready = false;
    void CheckIsOpen();
};
