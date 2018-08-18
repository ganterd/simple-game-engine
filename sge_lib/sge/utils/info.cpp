#include <sge/utils/utils.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/scenemanager.hpp>

namespace SGE
{
    class PrintSceneStructure
    {
    public:
        static void indent(int spaces)
        {
            for(int i = 0; i < spaces; ++i)
                std::cout << " ";
        }
        static void print(EntityComponent* c, int level)
        {
            indent(level + 1);
            std::cout << "|- Component" << std::endl;

            indent(level + 2);
            std::cout << "|- Drawable: " << c->isDrawable() << std::endl;
        }

        static void print(Entity* e, int level = 0)
        {
            for(int i = 0; i < level; ++i)
                std::cout << " ";
            if(level)
                std::cout << "|-";
            std::cout << "Entity: " << std::endl;

            std::vector<EntityComponent*> components = e->getComponents();
            for(EntityComponent* c : components)
            {
                print(c, level);
            }

            std::vector<Entity*> childEntities = e->getChildren();
            for(Entity* child : childEntities)
            {
                print(child, level + 1);
            }
        }

        static void print(Scene* s)
        {
            print(s->getRoot());
        }
    };

    void Utils::printSceneStructure()
    {
        PrintSceneStructure::print(SceneManager::getActiveScene());
    }
}
