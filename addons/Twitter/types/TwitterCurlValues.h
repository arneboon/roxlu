#ifndef ROXLU_TWITTERCURLVALUESH
#define ROXLU_TWITTERCURLVALUESH

#include <vector>
#include <string>
#include "TwitterCurlValueTypeString.h"
#include "TwitterCurlValueTypeFile.h"

using std::vector;
using std::string;

namespace roxlu {

class TwitterCurlValueType;

class TwitterCurlValues {
public:
	TwitterCurlValues();
	~TwitterCurlValues();
	
	template<typename T>
	TwitterCurlValueTypeString* addString(const string& name, const T& value) {
		TwitterCurlValueTypeString* v = new TwitterCurlValueTypeString(name, value);
		values.push_back(v);
		return v;
	}
	
	
	TwitterCurlValueTypeFile* addFile(const string& name, const string& filePath);
	
	const vector<TwitterCurlValueType*>& getValues();
	vector<TwitterCurlValueType*> values;
};

inline const vector<TwitterCurlValueType*>& TwitterCurlValues::getValues() {
	return values;
}

}; // roxlu
#endif