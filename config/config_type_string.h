#ifndef	CONFIG_TYPE_STRING_H
#define	CONFIG_TYPE_STRING_H

#include <map>

#include <config/config_type.h>

struct ConfigValue;

class ConfigTypeString : public ConfigType {
	std::map<ConfigValue *, std::string> strings_;
public:
	ConfigTypeString(void)
	: ConfigType("string"),
	  strings_()
	{ }

	~ConfigTypeString()
	{
		strings_.clear();
	}

	bool get(ConfigValue *cv, std::string *strp)
	{
		if (strings_.find(cv) == strings_.end()) {
			ERROR("/config/type/string") << "Value not set.";
			return (false);
		}
		*strp = strings_[cv];
		return (true);
	}

	bool set(ConfigValue *cv, const std::string& vstr)
	{
		if (strings_.find(cv) != strings_.end()) {
			ERROR("/config/type/string") << "Value already set.";
			return (false);
		}

		if (*vstr.begin() != '"') {
			ERROR("/config/type/string") << "String does not begin with '\"'.";
			return (false);
		}
		if (*vstr.rbegin() != '"') {
			ERROR("/config/type/string") << "String does not end with '\"'.";
			return (false);
		}

		std::string str(vstr.begin() + 1, vstr.end() - 1);
		if (std::find(str.begin(), str.end(), '"') != str.end()) {
			ERROR("/config/type/string") << "String has '\"' other than at beginning or end.";
			return (false);
		}

		strings_[cv] = str;
		return (true);
	}
};

extern ConfigTypeString config_type_string;

#endif /* !CONFIG_TYPE_STRING_H */
