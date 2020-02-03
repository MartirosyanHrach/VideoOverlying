#include "Overlayer.hpp" 


Video Overlayer::overlay_videos(const Video& subtracted_background,
                                const Video& moving_objects_video,
                                const Video& moving_objects_mask) {
                             
    auto min_frame_count = std::min(subtracted_background.m_frame_count, moving_objects_video.m_frame_count);
    
    Video output_video(
        subtracted_background.m_width,
        subtracted_background.m_height,
        min_frame_count,
        subtracted_background.m_fourcc,
        subtracted_background.m_frame_rate
    );

    cv::Mat tmpMoving, tmpBackground, inverseMask;
    for(int i = 0; i < min_frame_count; ++i) {
        cv::bitwise_not(moving_objects_mask.m_frames[i], inverseMask);
        tmpMoving = moving_objects_video.m_frames[i];
        tmpMoving.setTo(0, inverseMask);
        tmpBackground = subtracted_background.m_frames[i];
        tmpBackground.setTo(0, moving_objects_mask.m_frames[i]);
        output_video.m_frames[i] = tmpMoving + tmpBackground;
    }
    return output_video;
}