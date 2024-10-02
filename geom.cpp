#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std;

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
int signed_area2D(point2d a, point2d b, point2d c)
{
  int Ax = b.x - a.x;
  int Ay = b.y - a.y;
  int Bx = c.x - a.x;
  int By = c.y - a.y;

  return Ax * By - Ay * Bx;
}

/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2d p, point2d q, point2d r)
{
  return signed_area2D(p, q, r) == 0;
}

/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
int left_strictly(point2d a, point2d b, point2d c)
{
  return signed_area2D(a, b, c) > 0;
}

/* return 1 if c is left of ab or on ab; 0 otherwise */
int left_on(point2d a, point2d b, point2d c)
{
  return signed_area2D(a, b, c) >= 0;
}

// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d> &pts, vector<point2d> &hull)
{
  printf("hull2d (graham scan): start\n");
  hull.clear(); // should be empty, but clear it to be safe

  if (pts.size() == 1)
  {
    hull.push_back(pts[0]);
    return;
  }

  // find rightmost lowest point
  point2d p = pts[0];
  for (int i = 1; i < pts.size(); i++)
  {
    if (pts[i].y < p.y)
    {
      p = pts[i];
    }
    else if (pts[i].y == p.y)
    {
      if (pts[i].x > p.x)
      {
        p = pts[i];
      }
    }
  }
  // add p to the hull
  hull.push_back(p);

  // sort the points by polar angle with p using left predicate
  auto cmp = [p](point2d a, point2d b)
  {
    int area = signed_area2D(p, a, b);
    if (area == 0)
    {
      return (a.x - p.x) * (a.x - p.x) + (a.y - p.y) * (a.y - p.y) <
             (b.x - p.x) * (b.x - p.x) + (b.y - p.y) * (b.y - p.y);
    }
    return area > 0;
  };
  sort(pts.begin(), pts.end(), cmp);

  // add first point to the right of p
  hull.push_back(pts[1]);

  for (int i = 2; i < pts.size(); i++)
  {
    point2d b = hull.back();
    hull.pop_back(); // remove b
    point2d a = hull.back();

    while (!left_strictly(a, b, pts[i]))
    {
      b = a;
      hull.pop_back(); // remove a
      // ensure the first point is not removed
      if (hull.size() == 0)
      {
        break;
      }
      a = hull.back();
    }

    hull.push_back(b);
    hull.push_back(pts[i]);
  }

  printf("hull2d (graham scan): end\n");
  return;
}
