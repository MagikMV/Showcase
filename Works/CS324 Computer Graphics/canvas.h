/* canvas.h
 *
 * Miguel Villanueva
 * CS 324
 * February 12, 2022
 */

#include <vector>
#include <string>

using namespace std;

struct color
{
    uint8_t red, green, blue;
};

namespace colors
{
    constexpr color BLACK  {   0,   0,   0 };
    constexpr color WHITE  { 255, 225, 255 };
    constexpr color RED    { 255,   0,   0 };
    constexpr color GREEN  {   0, 255,   0 };
    constexpr color BLUE   {   0,   0, 255 };
    constexpr color ORANGE { 255, 165,   0 };
    constexpr color YELLOW { 255, 255,   0 };
}

struct pixel
{
    color c;
};

class Canvas
{
    public:
	Canvas(size_t w, size_t h, color background = colors::WHITE);

	void SetColor(size_t x, size_t y, color c);

	pixel GetPixel(size_t x, size_t y) const;
	void SetPixel(size_t x, size_t y, pixel c);

	void Clear();

	size_t Width() const { return width; }		// Getter function: width
	size_t Height() const { return height; }	// Getter function: height
    private:
	size_t width, height;
	vector<pixel> pixels;
	color background;
};

void Line(Canvas &c, int x1, int y1, int x2, int y2, color col);

void SaveCanvasToFile(Canvas const &canvas, string const &fileName);
