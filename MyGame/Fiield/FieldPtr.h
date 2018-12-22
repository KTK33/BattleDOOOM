#ifndef FIELD_PTR_H_
#define FIELD_PTR_H_

#include <memory>

//
class Field;
using FieldPtr = std::shared_ptr<Field>;

//
template<class T, class... Args>
inline FieldPtr new_field(Args&&... args) {
	return std::make_shared<T>(args...);
}
#endif // !FIELD_PTR_H_
