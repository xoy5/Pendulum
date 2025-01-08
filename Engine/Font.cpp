#include "Font.h"
#include <cassert>

Font::Font(const std::string& fileName, Color chroma)
	:
	chroma(chroma),
	surface(fileName),
	glyphWidth(surface.GetWidth() / nColumns),
	glyphHeight(surface.GetHeight() / nRows)
{
	assert(glyphWidth * nColumns == surface.GetWidth());
	assert(glyphHeight * nRows == surface.GetHeight());
}

void Font::DrawText(const std::string text, const Vei2& pos, Color color, Graphics& gfx) const
{
	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx)const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};

	Substitution e{ chroma, color };
	Vei2 curPos = pos;
	for (auto c : text)
	{
		if (c == '\n')
		{
			curPos.x = pos.x;
			curPos.y += glyphHeight;
			continue;
		}
		else if (firstChar <= (c + 1) && c <= lastChar)
		{
			gfx.DrawSprite(curPos.x, curPos.y, MapGlyphRect(c), surface, e);
		}
		curPos.x += glyphWidth;
	}
}

RectI Font::MapGlyphRect(char c) const
{
	assert(firstChar <= c && c <= lastChar);
	const int glyphIndex = c - firstChar;
	const int xGlyph = glyphIndex % nColumns;
	const int yGlyph = glyphIndex / nColumns;
	return RectI(
		{ xGlyph * glyphWidth, yGlyph * glyphHeight },
		glyphWidth, glyphHeight
	);
}
