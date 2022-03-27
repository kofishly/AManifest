#ifndef CLineNode_hpp
#define CLineNode_hpp

#include <stdio.h>
#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

class CLineNode
{
    string name;
    map<string, string> attribute_map;
public:
    // 将属性分割成map
    // 先按空格切分，再按:(冒号)进行切分。
    int string_split_map(string source_string, string spacer, map<string, string>&/*out*/ key_values);
    
    // 设置行节点的名称
    void set_name(string n);

    void parse_attribute(string attribute, map<string, string>& attribute_map);

    string get_name();

    map<string, string>& get_attribute_map_ref();

    void to_string(string space);
};

#endif

