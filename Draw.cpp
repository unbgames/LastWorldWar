#include "Draw.h"

Draw::Draw()
{
	
}

Uint32 Draw::getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) 
	{
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void Draw::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) 
	{
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else 
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;

		default:
			break;           /* shouldn't happen, but avoids warnings */
	}
}

void Draw::drawLine(SDL_Surface *surface, float x1, float y1, float x2, float y2, Uint32 pixel )
{
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
 
    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<maxX; x++)
    {
        if(steep)
        {
            putpixel(surface, y, x, pixel);
        }
        else
        {
            putpixel(surface, x, y, pixel);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

void Draw::drawRect(SDL_Surface *surface, float x, float y, float width, float height, Uint32 pixel )
{
	drawLine(surface, x, y, x + width, y, pixel);
	drawLine(surface, x, y, x, y + height, pixel);
	drawLine(surface, x + width, y + height, x + width, y, pixel);
	drawLine(surface, x + width, y + height, x, y + height, pixel);
}

void Draw::drawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel, bool in_Center = false)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
 
	if(!in_Center)
	{
		n_cx += radius;
		n_cy += radius;
	}

    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        putpixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        putpixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
        if (x != 0)
        {
            putpixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            putpixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
        if (y != 0)
        {
            putpixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            putpixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
        if (x != 0 && y != 0)
        {
            putpixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            putpixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }	
}

int Draw::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //retangulo para a posicao x,y
    SDL_Rect offset;

    //pegando as posicoes
    offset.x = x;
    offset.y = y;

    //Colagem da SDL_Surface na screen, com Blit
    return SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface* Draw::CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
	SDL_PixelFormat& fmt = *(display->format);
	return  SDL_CreateRGBSurface(flags,width,height,
			fmt.BitsPerPixel,
			fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}

SDL_Surface* Draw::MyFillRect(int width, int height, const SDL_Surface* display, Uint8 transparency = NULL)
{
	SDL_Surface* surface = (*this).CreateSurface(SDL_SWSURFACE, width, height, display);
	if(transparency != 0)
			SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, transparency);

	return surface;
}

