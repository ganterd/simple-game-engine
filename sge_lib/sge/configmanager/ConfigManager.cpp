#include "ConfigManager.hpp"

namespace SGE
{
	std::string ConfigManager::filePath("resources/configs/default.xml");
	std::map<std::string, std::string> ConfigManager::values;
	
	void ConfigManager::setConfigFile(std::string file)
	{
		ConfigManager::filePath = file;
	}
	
	bool ConfigManager::init()
	{
		if(ConfigManager::filePath == "")
		{
			filePath = "resources/configs/default.xml";
			LOG(DEBUG) << "Defaulted config file to " << filePath;			
		}

		/* Import the config text data */
		const char* text = Utils::readFile(filePath.c_str());
		if(text == NULL)
		{
			LOG(WARNING) << "Couldn't read config file: " << filePath;
			return false;
		}
		
		LOG(INFO) << "Initialising config from " << filePath;
		tinyxml2::XMLDocument doc;
		doc.Parse((char*)text);
		const tinyxml2::XMLElement* n = doc.FirstChildElement();
		if(n == NULL)
		{
			LOG(WARNING) << "Config is empty!";
			return false;
		}
		
		for(; n; n = n->NextSiblingElement())
				ConfigManager::recursiveParse("", n);
		
		LOG(DEBUG) << "Finished reading config";
		return true;
	}
	
	void ConfigManager::recursiveParse(std::string currentNodeName, const tinyxml2::XMLElement* n)
	{
		std::string name(currentNodeName);
		if(currentNodeName.length() > 0)
			name.append(".");
		name.append(n->Name());
		const tinyxml2::XMLElement* child = n->FirstChildElement();
		if(child)
		{
			while(child)
			{
				ConfigManager::recursiveParse(name, child);
				child = child->NextSiblingElement();
			}

		}
		else
		{
			LOG(DEBUG) << name << ": " << n->GetText();
			ConfigManager::values[name] = n->GetText();
		}
	}
	
	std::string ConfigManager::get(std::string prop)
	{
		if(ConfigManager::values.find(prop) == ConfigManager::values.end())
		{
			return "";
		}
		return ConfigManager::values[prop];
	}
}
