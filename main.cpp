#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

const double PI = 3.141592;
const double R = 0.57;
const double O = 45;
sf::Color treeColor = sf::Color::Blue;

void createTreeRecursive(sf::VertexArray &tree, sf::Vector2f point, float angle, float lenght)
{
    if (lenght < 3)

        return;

    tree.append(sf::Vertex(point, treeColor));
    float newX = point.x + (cos((2.f * PI / 360.f) * angle) * lenght);
    float newY = point.y - (sin((2.f * PI / 360.f) * angle) * lenght);
    sf::Vector2f nextPoint(newX, newY);

    tree.append(sf::Vertex(nextPoint, treeColor));

    createTreeRecursive(tree, nextPoint, angle + O, lenght * R);

    createTreeRecursive(tree, nextPoint, angle - O, lenght * R);
}

sf::VertexArray createTree()
{

    sf::VertexArray ret(sf::PrimitiveType::Lines);

    createTreeRecursive(ret, sf::Vector2f(250, 450), 90, 200);
    return ret;
}

int main()
{

    sf::RenderWindow window({800, 600}, "SFML Tree", sf::Style::Close);

    auto tree = createTree();

    while (window.isOpen())
    {
        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(tree);
        window.display();
    }
    return EXIT_SUCCESS;
}
