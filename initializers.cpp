#include "geom.h"
#include "rtimer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <strings.h>

// to compile on both apple and unix platform
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
using namespace std;

// window size for the graphics window
const int WINDOWSIZE = 500;

/* ****************************** */
/* Initializes pts with n points on two circles.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/
void initialize_points_circle(vector<point2d> &pts, int n)
{

    printf("\ninitialize points circle\n");
    // clear the vector just to be safe
    pts.clear();

    n = n / 2; // we'll generaate two circles, n/2 points each
    double step = 2 * M_PI / n;
    int radius = 100;

    point2d p;
    for (int i = 0; i < n; i++)
    {
        p.x = WINDOWSIZE / 2 + radius * cos(i * step);
        p.y = WINDOWSIZE / 2 + radius * sin(i * step);
        pts.push_back(p);
    }

    radius /= 2;
    for (int i = 0; i < n; i++)
    {
        p.x = WINDOWSIZE / 2 + radius * cos(i * step);
        p.y = WINDOWSIZE / 2 + radius * sin(i * step);
        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n points on a line.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/
void initialize_points_horizontal_line(vector<point2d> &pts, int n)
{

    printf("\ninitialize points line\n");
    // clear the vector just to be safe
    pts.clear();

    point2d p;
    for (int i = 0; i < n; i++)
    {
        p.x = (int)(.3 * WINDOWSIZE) / 2 + random() % ((int)(.7 * WINDOWSIZE));
        p.y = WINDOWSIZE / 2;
        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n random points.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/
void initialize_points_random(vector<point2d> &pts, int n)
{

    printf("\ninitialize points random\n");
    // clear the vector just to be safe
    pts.clear();

    point2d p;
    for (int i = 0; i < n; i++)
    {
        p.x = (int)(.3 * WINDOWSIZE) / 2 + random() % ((int)(.7 * WINDOWSIZE));
        p.y = (int)(.3 * WINDOWSIZE) / 2 + random() % ((int)(.7 * WINDOWSIZE));
        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n points on a cross-like shape.  The points are
   in the range (0,0) to (WINSIZE,WINSIZE).
*/
void initialize_points_cross(vector<point2d> &pts, int n)
{

    printf("\ninitialize points cross\n");
    // clear the vector just to be safe
    pts.clear();

    point2d p;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {

            p.x = (int)(.3 * WINDOWSIZE) / 2 + random() % ((int)(.7 * WINDOWSIZE));
            p.y = random() % ((int)(.7 * WINDOWSIZE)) / 5;
            p.y += (int)((1 - .7 / 5) * WINDOWSIZE / 2);
        };
        if (i % 2 == 1)
        {

            p.x = random() % ((int)(.7 * WINDOWSIZE)) / 5;
            p.x += (int)((1 - .7 / 5) * WINDOWSIZE / 2);
            p.y = (int)(.3 * WINDOWSIZE) / 2 + random() % ((int)(.7 * WINDOWSIZE));
        }

        pts.push_back(p);

    } // for i
}

/* ****************************** */
/* Initializes pts with n points on a tic-tac-toe board outline shape.  The points are
   in the range (0,0) to (WINSIZE,WINSIZE).
*/
void initialize_points_tic_tac_toe(vector<point2d> &pts, int n)
{
    printf("\ninitialize points tic-tac-toe\n");
    // clear the vector just to be safe
    pts.clear();

    point2d p;
    int step = WINDOWSIZE / 3;
    int border = WINDOWSIZE / 10;

    // vertical lines
    for (int i = 0; i < n / 4; i++)
    {
        // first vertical line
        p.x = step;
        p.y = border + (WINDOWSIZE - 2 * border) * i / (n / 4 - 1);
        pts.push_back(p);

        // second vertical line
        p.x = 2 * step;
        pts.push_back(p);
    }

    // horizontal lines
    for (int i = 0; i < n / 4; i++)
    {
        // first horizontal line
        p.x = border + (WINDOWSIZE - 2 * border) * i / (n / 4 - 1);
        p.y = step;
        pts.push_back(p);

        // second horizontal line
        p.y = 2 * step;
        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n points on a honeycomb outline shape.  The points are
   in the range (0,0) to (WINSIZE,WINSIZE).
*/
void initialize_points_honeycomb(vector<point2d> &pts, int n)
{
    printf("\ninitialize points honeycomb\n");
    // clear the vector just to be safe
    pts.clear();

    if (n < 6)
    {
        printf("n must be at least 6\n");
        return;
    }

    point2d p;
    int step = WINDOWSIZE / 3;

    // center of the honeycomb
    double centerX = WINDOWSIZE / 2;
    double centerY = WINDOWSIZE / 2;

    // generate points for the hexagon
    for (int i = 0; i < n; i++)
    {
        double angle = 2 * M_PI * i / n;

        if (i % (n / 6) == 0)
        {
            // Corner points
            p.x = centerX + step * cos(angle);
            p.y = centerY + step * sin(angle);
        }
        else
        {
            // points along the edges
            double t = (i % (n / 6)) / (double)(n / 6);
            int corner = i / (n / 6);
            double x1 = centerX + step * cos(2 * M_PI * corner / 6);
            double y1 = centerY + step * sin(2 * M_PI * corner / 6);
            double x2 = centerX + step * cos(2 * M_PI * (corner + 1) / 6);
            double y2 = centerY + step * sin(2 * M_PI * (corner + 1) / 6);
            p.x = x1 + t * (x2 - x1);
            p.y = y1 + t * (y2 - y1);
        }

        pts.push_back(p);
    }
}

// Function to initialize points in a wave shape based on the sine function
// By Jack and Manny
void initialize_points_wave(vector<point2d> &pts, int n)
{
    printf("\ninitialize points wave\n");
    // clear the vector just to be safe
    pts.clear();
    double step = (double)WINDOWSIZE / n;
    double amplitude = 100; // Height of the wave
    double frequency = 0.1; // Controls the number of waves
    point2d p;
    for (int i = 0; i < n; ++i)
    {
        p.x = i * step;
        p.y = WINDOWSIZE / 2 + amplitude * sin(frequency * p.x);
        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n points forming a spiral shape.
   The points are in the range [0, WINSIZE] x [0, WINSIZE].
   By David Gelinas
*/
void initialize_points_spiral(vector<point2d> &pts, int n)
{
    printf("\ninitialize points spiral\n");
    pts.clear();

    double centerX = WINDOWSIZE / 2; // center of circle
    double centerY = WINDOWSIZE / 2; // center of circle

    double theta_increment = 1 / M_PI;                 // angle increment for the spiral
    double max_radius = WINDOWSIZE / 2.5;              // maximum radius to keep the spiral within bounds
    double radius_increment = max_radius / (n / 10.0); // increment based on number of points

    for (int i = 0; i < n; i++)
    {
        double theta = i * theta_increment * 0.5;   // angle increases as i increases
        double radius = radius_increment * i * 0.1; // scale the radius to keep it spiral-like
        radius = fmin(radius, max_radius);          // ensures the radius doesn't exceed the boundary

        point2d p;
        p.x = centerX + radius * cos(theta);
        p.y = centerY + radius * sin(theta);

        pts.push_back(p);
    }
}

/* ****************************** */
/* Initializes pts with n points on a heart. The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
   By Leah Dichter
*/
void initialize_points_heart(vector<point2d> &pts, int n)
{
    printf("\ninitialize points heart\n");
    pts.clear();
    double step = WINDOWSIZE / n;

    point2d p;
    for (int i = 0; i < n; i++)
    {
        float t = step * i;
        p.x = (16 * pow(sin(t), 3)) * WINDOWSIZE / 50 + WINDOWSIZE / 2;
        p.y = (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) * WINDOWSIZE / 50 + WINDOWSIZE / 2;
        pts.push_back(p);
    }
}

// By Tom Han
void initialize_points_1(vector<point2d> &pts, int n)
{
    printf("\ninitialize points 1\n");
    pts.clear();
    assert(pts.size() == 0);

    point2d p;
    int pos, pos2;
    for (int i = 0; i < n; i++)
    {
        switch (i % 7)
        {
        case 0:
        case 1:
            // Base
            p.y = random() % (int)(.1 * WINDOWSIZE);
            p.y += (int)(0.15 * WINDOWSIZE);
            p.x = random() % (int)(0.3 * WINDOWSIZE);
            p.x += (int)(0.35 * WINDOWSIZE);
            break;
        case 2:
            pos = random() % (int)(0.1 * WINDOWSIZE);
            p.x = pos;
            p.y = pos;
            p.x += (int)(0.4 * WINDOWSIZE);
            p.y += (int)(0.7 * WINDOWSIZE);
            pos2 = random() % (int)(0.05 * WINDOWSIZE);
            p.x -= pos2;
            p.y += pos2;
            break;
        case 3:
            // Colinear case
            p.x = (int)(0.25 * WINDOWSIZE) + random() % ((int)(0.5 * WINDOWSIZE));
            p.y = (int)(0.10 * WINDOWSIZE);
            break;
        default:
            // stem
            p.y = (int)(0.25 * WINDOWSIZE);
            p.y += random() % (int)(0.6 * WINDOWSIZE);
            p.x = (int)(0.45 * WINDOWSIZE);
            p.x += random() % (int)(0.1 * WINDOWSIZE);
            break;
        }
        pts.push_back(p);
    }
}

// by Tom Han
void initialize_points_2(vector<point2d> &pts, int n)
{
    printf("\ninitialize points 2\n");
    pts.clear();
    assert(pts.size() == 0);

    point2d p;
    int x_noise, y_noise;
    int pos, pos2;
    for (int i = 0; i < n; i++)
    {
        switch (i % 3)
        {
        case 0:
            p.x = (int)(0.25 * WINDOWSIZE) + random() % ((int)(0.5 * WINDOWSIZE));
            p.y = (int)(0.15 * WINDOWSIZE);
            break;
        case 1:
            pos = random() % (int)(0.5 * WINDOWSIZE);
            p.x = pos;
            p.y = pos;
            p.x += (int)(0.25 * WINDOWSIZE);
            p.y += (int)(0.15 * WINDOWSIZE);
            break;
        case 2:
            pos2 = random() % 180;
            p.x = (int)(0.5 * WINDOWSIZE) + (int)((0.25 * WINDOWSIZE) * cos((M_PI * pos2) / 180));
            p.y = (int)(0.65 * WINDOWSIZE) + (int)((0.25 * WINDOWSIZE) * sin((M_PI * pos2) / 180));
            break;
        }
        x_noise = random() % ((int)(0.05 * WINDOWSIZE));
        y_noise = random() % ((int)(0.05 * WINDOWSIZE));
        p.x += x_noise;
        p.y += y_noise;
        pts.push_back(p);
    }
}
