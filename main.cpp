#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int screen_size = 700;

class Star
{
    public:
    float x;
    float y;
    float z;
    int radius;
    float curr_x, curr_y;
    float prev_x, prev_y, prev_z;
    int r, g, b;
    int speed;

    Star()
    {
        x = rand() % (screen_size) + (-screen_size/2);
        y = rand() % (screen_size) + (-screen_size/2);
        z = rand() % screen_size;
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
        prev_z = z;
        speed = 30;
    }

    void update()
    {
        z -= speed;

        if(z < 1)
        {
            z = rand() % screen_size;
            prev_z = z;

            x = rand() % (screen_size) + (-screen_size/2);
            y = rand() % (screen_size) + (-screen_size/2);

            r = rand() % 255;
            g = rand() % 255;
            b = rand() % 255;

        }

    }

    void display(Mat screen)
    {

        curr_x = (x/z) * screen_size;
        curr_y = (y/z) * screen_size;
        
        curr_x = screen_size/2 + curr_x;
        curr_y = screen_size/2 - curr_y;
        
        prev_x = (x/prev_z) * screen_size;
        prev_y = (y/prev_z) * screen_size;
        
        prev_x = screen_size/2 + prev_x;
        prev_y = screen_size/2 - prev_y;

        if(abs(prev_x - curr_x) < 70 && abs(prev_y - curr_y) < 70)
        {
            line(screen, Point(prev_x, prev_y), Point(curr_x, curr_y), Scalar(b, g, r));

        }

        imshow("Starfield", screen);

    }
};

int main(int args, char* argv[])
{
    int size = 100;
    int i, key;

    Mat screen(screen_size, screen_size, CV_8UC3, Scalar(0, 0, 0));

    Star stars[size];
    
    while(true)
    {      
        for(i = 0; i < size; i++)
        {
            stars[i].update();
            stars[i].display(screen);
        }

        screen.setTo(Scalar(0, 0, 0));
        key = waitKey(1) & 0xFF;
        if(key == (int)'q')
        {   
            break;
        }

    }

    return 0;
}