#ifndef I_MODEL
#define I_MODEL

#include <string>

class IModel {
	public:
        virtual std::string toString() const = 0;
};

#endif /* I_MODEL */
