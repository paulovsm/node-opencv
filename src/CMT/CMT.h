#ifndef CMT_H

#define CMT_H

#include "common.h"
#include "Consensus.h"
#include "Fusion.h"
#include "Matcher.h"
#include "Tracker.h"
#include "../OpenCV.h"

#include <opencv2/features2d/features2d.hpp>

using cv::FeatureDetector;
using cv::DescriptorExtractor;
using cv::Ptr;
using cv::RotatedRect;
using cv::Size2f;

class CMT: public Nan::ObjectWrap
{
public:
    static Nan::Persistent<FunctionTemplate> constructor;
    static void Init(Local<Object> target);
    static NAN_METHOD(New);

    CMT(Mat image, Rect rect);
    JSFUNC(cmtTrack);

//    CMT() : str_detector("FAST"), str_descriptor("BRISK") {};
    void initialize(const Mat im_gray, const Rect rect);
    void processFrame(const Mat im_gray);

    Fusion fusion;
    Matcher matcher;
    Tracker tracker;
    Consensus consensus;

    string str_detector;
    string str_descriptor;

    vector<Point2f> points_active; //public for visualization purposes
    RotatedRect bb_rot;

private:
    Ptr<FeatureDetector> detector;
    Ptr<DescriptorExtractor> descriptor;

    Size2f size_initial;

    vector<int> classes_active;

    float theta;

    Mat im_prev;
    Point2f oCenter;
};

#endif /* end of include guard: CMT_H */