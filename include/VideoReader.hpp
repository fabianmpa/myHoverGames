
#pragma once


#include "IFrameReader.hpp"
#include <opencv2/opencv.hpp>

class VideoReader :
    public IFrameReader<cv::Mat>
{
public:
    /**
     * @brief Default constructor.
     *
     * Underlying open cv video capture object will be instantiated.
     */
    VideoReader() = default;

    ~VideoReader() override = default;

    /**
     *@brief Initialises reader to capture frames from video file.
     *
     * @param source path to the video file or image sequence.
     *
     * @throws std::runtime_error if init failed
     */
    void Init(const std::string& source);

    std::shared_ptr <cv::Mat> ReadFrame() override;

    bool IsExhausted(const std::shared_ptr <cv::Mat>& frame) const override;

    /**
     * Returns effective video frame width supported by the source/set by the user.
     * Must be called after Init method.
     * @return frame width
     */
    int GetSourceWidth() const;

    /**
     * Returns effective video frame height supported by the source/set by the user.
     * Must be called after Init method.
     * @return frame height
     */
    int GetSourceHeight() const;

    /**
     * Returns effective fps value supported by the source/set by the user.
     * @return fps value
     */
    double GetSourceFps() const;

    /**
     * Will query OpenCV to convert images to RGB
     * Copy is actually default behaviour, but the set function needs to be called
     * in order to know whether OpenCV supports conversion from our source format.
     * @return boolean,
     *     true:  OpenCV returns RGB
     *     false: OpenCV returns the fourcc format from GetSourceEncoding
     */
    bool ConvertToRGB();

    /**
     * Returns 4-character code of codec.
     * @return codec name
     */
    std::string GetSourceEncoding() const;

   /**
    * Get the fourcc int from its string name.
    * @return codec int
    */
    int GetSourceEncodingInt() const;

    int GetFrameCount() const;

    void Close();

private:
    cv::VideoCapture m_capture;

    void CheckIsOpen(const std::string& source);
};

class VideoReaderRgbWrapper :
        public IFrameReader<cv::Mat>
{
public:
    VideoReaderRgbWrapper() = delete;
    VideoReaderRgbWrapper(const VideoReaderRgbWrapper& o) = delete;
    VideoReaderRgbWrapper(VideoReaderRgbWrapper&& o) = delete;

    VideoReaderRgbWrapper(std::unique_ptr<VideoReader> reader);

    std::shared_ptr<cv::Mat> ReadFrame() override;

    bool IsExhausted(const std::shared_ptr<cv::Mat>& frame) const override;

private:
    std::unique_ptr<VideoReader> m_reader;
};