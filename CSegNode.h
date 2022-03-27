#ifndef CSegNode_hpp
#define CSegNode_hpp

#include "CLineNode.h"
class CSegNode :
    public CLineNode
{
    list<CSegNode*> list_seg_node;
    list<CLineNode*> list_line_node;
public:
    list<CSegNode*>& get_seg_node_list();

    list<CLineNode*>& get_line_node_list();

    void parse_inner_data(string& content, list<CLineNode*>& line_node_list, list<CSegNode*>& seg_node_list);

    void to_string(string space);
};
#endif
