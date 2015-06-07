//
//  JsonStorage.h
//  HappyHero
//
//  Created by linyongxing on 14-6-10.
//
//

#ifndef __HappyHero__JsonStorage__
#define __HappyHero__JsonStorage__

#include "cocos2d.h"
#include "json/document.h"

class JsonStorage
{
public:
    static JsonStorage * GetInstance(std::string _fileName);
    
    void flush();

	bool		getBoolForKey(const std::string &key, bool defaultValue = false);
    int			getIntegerForKey(const std::string &key, int defaultValue = 0);
    double		getDoubleForKey(const std::string &key, float defaultValue = 0.0f);
	std::string getStringForKey(const std::string &key, const std::string & defaultValue = "");
    
	void	setBoolForKey(const std::string &key , bool value);
    void    setIntegerForKey(const std::string &key, int value);
	void    setDoubleForKey(const std::string &key, double value);
    void    setStringForKey(const std::string &key, const std::string &value);
	
protected:
	void parse();

	std::string _fileName;
    rapidjson::Document _json;
};

#endif /* defined(__HappyHero__JsonStorage__) */
