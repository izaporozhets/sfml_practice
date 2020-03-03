
#ifndef SFML_SHAPE_HPP
#define SFML_SHAPE_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>


namespace sf
{
class SFML_GRAPHICS_API Shape : public Drawable, public Transformable
{
public:

    virtual ~Shape();

    void setFillColor(const Color& color);

	//virtual const Color& getFillColor() const;

    virtual std::size_t getPointCount() const = 0;

    virtual Vector2f getPoint(std::size_t index) const = 0;

    FloatRect getLocalBounds() const;

    FloatRect getGlobalBounds() const;

	virtual Shape* clone() = 0;

	virtual void setToDefault() = 0;



protected:
    Shape();

    void update();

private:

    virtual void draw(RenderTarget& target, RenderStates states) const;

    void updateFillColors();

    void updateTexCoords();

    void updateOutline();

    void updateOutlineColors();

private:

    const Texture* m_texture;          ///< Texture of the shape
    IntRect        m_textureRect;      ///< Rectangle defining the area of the source texture to display
    Color          m_fillColor;        ///< Fill color
    Color          m_outlineColor;     ///< Outline color
    float          m_outlineThickness; ///< Thickness of the shape's outline
    VertexArray    m_vertices;         ///< Vertex array containing the fill geometry
    VertexArray    m_outlineVertices;  ///< Vertex array containing the outline geometry
    FloatRect      m_insideBounds;     ///< Bounding rectangle of the inside (fill)
    FloatRect      m_bounds;           ///< Bounding rectangle of the whole shape (outline + fill)
};

}


#endif 
