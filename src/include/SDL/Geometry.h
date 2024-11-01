#pragma once

class Geometry
{
    public: 
        /**
         * A Point struct containing coordinates of a point
         */
        struct Point
        {
            int x;  // the x coordinate
            int y;  // the y coordinate
        };

        /**
         * Line Struct containing two Points
         */
        struct Line
        {
            Point start; // Start of the line
            Point end;  // End of the line
        };
};