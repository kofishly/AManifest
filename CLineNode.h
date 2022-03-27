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
    // �����Էָ��map
    // �Ȱ��ո��з֣��ٰ�:(ð��)�����з֡�
    int string_split_map(string source_string, string spacer, map<string, string>&/*out*/ key_values);
    
    // �����нڵ������
    void set_name(string n);

    void parse_attribute(string attribute, map<string, string>& attribute_map);

    string get_name();

    map<string, string>& get_attribute_map_ref();

    void to_string(string space);
};

#endif

