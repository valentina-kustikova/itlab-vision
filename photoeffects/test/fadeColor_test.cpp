#include "photoeffects.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace cv;

TEST(photoeffects, FadeColorInvalidImageFormat)
{
    Mat src(10, 20, CV_8UC2);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5, 5), Point(5, 10)));
}
TEST(photoeffects, FadeColorInvalidArgument)
{
    Mat src(10, 20, CV_8UC1);
    Mat dst;

    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(50,5), Point(5,10)));
    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5,5), Point(5,-10)));
    EXPECT_ERROR(CV_StsAssert, fadeColor(src, dst, Point(5,5), Point(5,5)));
}
TEST(photoeffects, FadeColorTest) {
    Mat imageWithOneChannel(100, 200, CV_8UC1);
    Mat imageWithThreeChannel(100, 200, CV_8UC3);
    Mat dst;
    EXPECT_EQ(0, fadeColor(imageWithOneChannel, dst, Point(5,5), Point(5,8)));
    EXPECT_EQ(0, fadeColor(imageWithThreeChannel, dst, Point(5,5), Point(5,8)));
}
TEST(photoeffects, FadeColorRegressionTest)
{
    string input ="fadeColor_test.png";
    string expectedOutput ="fadeColor_result.png";

    Mat image, dst, rightDst;
    image = imread(input, CV_LOAD_IMAGE_COLOR);
    rightDst = imread(expectedOutput, CV_LOAD_IMAGE_COLOR);

    if (image.empty())
        FAIL() << "Can't read " + input + " image";
    if (rightDst.empty())
        FAIL() << "Can't read " + expectedOutput + " image";

    EXPECT_EQ(0, fadeColor(image, dst, Point(100, 100), Point(1, 1)));

    for (int i=0; i<dst.rows; i++)
    {
        for (int j=0; j<dst.cols; j++)
        {
            for (int k=0; k<3; k++)
            {
                ASSERT_EQ(rightDst.at<Vec3b>(i, j)[k], dst.at<Vec3b>(i, j)[k]);
            }
        }
    }
}
