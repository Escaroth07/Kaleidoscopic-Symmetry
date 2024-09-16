#include <graphics.h>
#include <math.h>
#include <conio.h>

void drawKaleidoscope(int cx, int cy, int radius, int angle, int reflections, int width, int height) {
    int step = 360 / reflections;

    for (int i = 0; i < reflections; i++) {
        int x = cx + radius * cos((angle + i * step) * M_PI / 180);
        int y = cy + radius * sin((angle + i * step) * M_PI / 180);
        int colorGradient = i * 16;

        setcolor(COLOR((colorGradient) % 255, (colorGradient * 2) % 255, (colorGradient * 3) % 255));
        setfillstyle(SOLID_FILL, COLOR((colorGradient) % 255, (colorGradient * 2) % 255, (colorGradient * 3) % 255));

        int ellipseSize = 10 + (5 * cos((angle + i * step) * M_PI / 180));

        fillellipse(x, y, ellipseSize, ellipseSize);
        fillellipse(width - x, y, ellipseSize, ellipseSize);
        fillellipse(x, height - y, ellipseSize, ellipseSize);
        fillellipse(width - x, height - y, ellipseSize, ellipseSize);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    int width = getmaxx();
    int height = getmaxy();
    int cx = width / 2;
    int cy = height / 2;

    int angle = 0;
    int radius = 100;
    int reflections = 12;
    int rotationSpeed = 8;

    while (true) {
        if (kbhit()) {
            char key = getch();

            if (key == 27) break;  // Exit on 'ESC'
            else if (key == 72) reflections += 2;   // Up arrow to increase reflections
            else if (key == 80 && reflections > 2) reflections -= 2;  // Down arrow to decrease reflections
            else if (key == 75 && rotationSpeed > 2) rotationSpeed -= 2;  // Left arrow to slow down
            else if (key == 77) rotationSpeed += 2;  // Right arrow to speed up
            else if (key == '+') radius += 10;  // '+' to increase radius
            else if (key == '-') radius -= 10;  // '-' to decrease radius
        }

        cleardevice();
        drawKaleidoscope(cx, cy, radius, angle, reflections, width, height);

        angle = (angle + rotationSpeed) % 360;

        delay(20);
    }

    closegraph();
    return 0;
}
