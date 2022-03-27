#include "CLineNode.h"

int CLineNode::string_split_map(string source_string, string spacer, map<string, string>& key_values)
{

    while (true) {
        int pos = (int)source_string.find(spacer);
        if (pos < 0 && source_string.length() <= 0) {
            break;
        }
        int pos_next = pos + (int)spacer.size();
        string tmp = source_string.substr(0, pos);
        source_string = source_string.substr(pos_next);
        int mid = (int)tmp.find("=");
        string s1 = tmp.substr(0, mid);
        string s2 = tmp.substr(mid + 1);

        key_values.insert(std::pair<string, string>(s1, s2));
        if (tmp == source_string)
        {
            break;
        }
    }
    return (int)key_values.size();
}


void CLineNode::set_name(string n)
{
    this->name = n;
}

void CLineNode::parse_attribute(string attribute, map<string, string>& attribute_map)
{
    string_split_map(attribute, string(" "), this->get_attribute_map_ref());
}

string CLineNode::get_name()
{
    return name;
}

map<string, string>& CLineNode::get_attribute_map_ref()
{
    return this->attribute_map;
}

void CLineNode::to_string(string space)
{
    printf("%s", space.c_str());
    printf("<%s", name.c_str());
    map<string, string>::iterator it_bg = attribute_map.begin();
    map<string, string>::iterator it_ed = attribute_map.end();
    while (it_bg != it_ed)
    {
        printf(" %s=%s", (*it_bg).first.c_str(), (*it_bg).second.c_str());
        it_bg++;
    }
    printf("/>\r\n");
}
