#include <sge/utils/utils.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/scenemanager.hpp>

namespace SGE
{
    class PrintSceneStructure
    {
    public:
        static std::string indent(int spaces)
        {
            std::string spacesString = "";
            for(int i = 0; i < spaces; ++i)
                spacesString.append(" ");
            return spacesString;
        }
        static void print(EntityComponent* c, int level)
        {
            LOG(INFO) << indent(level + 1) << "|- Component";

            LOG(INFO) << indent(level + 2) << "|- Drawable: " << c->isDrawable();
        }

        static void print(Entity* e, int level = 0)
        {

            if(level)
                LOG(INFO) << indent(level) << "|- Entity";
            else
                LOG(INFO) << "Scene Root Node";

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
