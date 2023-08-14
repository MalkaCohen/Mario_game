#include "Graphics.h"
#include <algorithm>

using namespace cv;
using namespace std;

//////////////////////////////////////////////////

SingleAnimationGraphics::SingleAnimationGraphics(AnimationPtr animPtr, bool isCyclic)
    :_animation(animPtr), _currFrameIdx(0)
    , _isCyclic(isCyclic)
{    
}


cv::Mat SingleAnimationGraphics::getCollisionMask()
{
    return _animation->getFrame(_currFrameIdx).mask;
}

void SingleAnimationGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    drawFrame(_animation->getFrame(_currFrameIdx), canvas, topLeft);
}

void SingleAnimationGraphics::reset(int code)
{
    _currFrameIdx = 0;
}

bool SingleAnimationGraphics::update()
{
    bool hasFinished = (_currFrameIdx == _animation->numFrames() - 1);
    if (_isCyclic)
        _currFrameIdx = (_currFrameIdx + 1) % _animation->numFrames();
    else 
        _currFrameIdx = min<int>(_currFrameIdx + 1, (int)_animation->numFrames() - 1);

    return hasFinished;
}

//////////////////////////////////////////////////
LivesGraphics::LivesGraphics(Frame& frame ) :_singleLife(frame)
{
    reset(5);
}
void LivesGraphics::reset(int code)
{
    _livesCount = code;
}
bool LivesGraphics::update()
{
    reset(_livesCount--);
    return _livesCount;
}
void LivesGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    Point curr_topLeft = topLeft;
    for (int i = 0; i < _livesCount; i++)
    {
        curr_topLeft.x -= _singleLife.image.cols*1.2;
        drawFrame(_singleLife, canvas, curr_topLeft);
    }
}
cv::Mat LivesGraphics::getCollisionMask()
{
    return _singleLife.mask;
}





//////////////////////////////////////////////////
ScoresGraphics::ScoresGraphics(float fontScale,int fontFace)
{
    _fontScale = fontScale;
    _fontFace = fontFace;
    reset();
}
 
void ScoresGraphics::reset(int code )
{
    _score = code;
}

void ScoresGraphics::draw(cv::Mat& canvas, cv::Point const& topLeft)
{
    string text = "score: ";
    text =text + to_string(_score);

    Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255);
    int thickness = 2;
    int lineType = FILLED;
    putText(canvas, text, topLeft, _fontFace, _fontScale, color, thickness, lineType);
    imshow("test", canvas);

}


cv::Mat ScoresGraphics::getCollisionMask()
{
    return Mat();
}
bool ScoresGraphics:: update()
{
    return false;
}


//////////////////////////////////////////////////

void exampleOfPutText()
{
    Mat image = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);
    string text = "score: ";
    int score = 465;
    string moreText = to_string(score);
    text = text + moreText;
    Point topLeft(50, 50);
    int fontFace = FONT_HERSHEY_SIMPLEX; // normal size sans - serif font
    // other options for fontFace:
    FONT_HERSHEY_PLAIN;// small size sans - serif font
    FONT_HERSHEY_DUPLEX;// normal size sans - serif font(more complex than FONT_HERSHEY_SIMPLEX)
    FONT_HERSHEY_COMPLEX; // normal size serif font
    FONT_HERSHEY_TRIPLEX; //normal size serif font(more complex than FONT_HERSHEY_COMPLEX)
    FONT_HERSHEY_COMPLEX_SMALL; //smaller version of FONT_HERSHEY_COMPLEX
    FONT_HERSHEY_SCRIPT_SIMPLEX; //hand - writing style font
    FONT_HERSHEY_SCRIPT_COMPLEX;// more complex variant of FONT_HERSHEY_SCRIPT_SIMPLEX
    double fontScale = 2; // Font scale factor that is multiplied by the font-specific base size.
    Scalar color(/*Blue between 0...255 =*/0,/*Green between 0...255 =*/0,/*Red between 0...255 =*/255); 
    int thickness = 2;
    int lineType = FILLED;
    // other options for line type:
    LINE_4; LINE_8; LINE_AA;

    // finally:
    putText(image, text, topLeft, fontFace, fontScale, color, thickness, lineType);
    
    imshow("test", image);
    waitKey();//waiting forever till some key is hit.
}