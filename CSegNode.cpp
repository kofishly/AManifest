#include "CSegNode.h"

list<CSegNode*>& CSegNode::get_seg_node_list()
{
    return list_seg_node;
}

list<CLineNode*>& CSegNode::get_line_node_list()
{
    return list_line_node;
}

void CSegNode::parse_inner_data(string& content, list<CLineNode*>& line_node_list, list<CSegNode*>& seg_node_list)
{
    int index_start_flag = (int)content.find("<");
    while (index_start_flag >= 0)
    {
        int index_line = (int)content.find("/>");
        int index_seg = (int)content.find(">");
        if (-1 == index_line && index_seg != -1)
        {
            //return false;
        }

        if (index_seg - index_line > 0)
        {
            CLineNode* p_line_node = new CLineNode();
            // 取内容
            string line = content.substr(index_start_flag+1, index_line-(index_start_flag + 1));
            // 去除内容
            content = content.substr(index_line+2/*/>的长度*/);
            int right = (int)line.find(" ");
            string name = line.substr(0, right);
            p_line_node->set_name(name);
            // 截取数据
            string attr = line.substr(1 + name.size());
            while (attr.at(0) == ' ')
            {
                attr = attr.substr(1);
            }
            while (attr.at(attr.size() - 1) == ' ')
            {
                attr = attr.substr(0, attr.size() - 1 - 1);
            }
            p_line_node->parse_attribute(attr, p_line_node->get_attribute_map_ref());
            line_node_list.push_back(p_line_node);
        } 
        else if (index_line - index_seg > 0)
        {
            /**解析:<name></name>*/
            int end_attr = (int)content.find(">");
            string attr = content.substr(index_start_flag+1, end_attr - (index_start_flag+1));
            // 内容数据去除属性
            content = content.substr(end_attr + 1);
            // 提取属性中的名字，可以知道是application、activity、service等
            string segment_name = attr.substr(0, attr.find(" "));
            // 属性去除已经解析的部分
            attr = attr.substr(attr.find(" ") + 1);
            // 获取数据
            string end_sign = "</" + segment_name + ">";
            int end_sign_lenth = (int)end_sign.size();
            int end_segment = (int)content.find(end_sign);
            string data = content.substr(0, end_segment);
            //去除数据部分内容
            content = content.substr(end_segment + end_sign_lenth);

            CSegNode* p_segment = new CSegNode();
            p_segment->set_name(segment_name);
            p_segment->parse_attribute(attr, this->get_attribute_map_ref());
            p_segment->parse_inner_data(data, p_segment->get_line_node_list(), p_segment->get_seg_node_list());
            this->get_seg_node_list().push_back(p_segment);
        }

        // 更新起始位置
        index_start_flag = (int)content.find("<");
        if (index_start_flag > 0) {
            content = content.substr(index_start_flag);
            index_start_flag = (int)content.find("<");
        }
    }
    int i;
    while ((i = (int)content.find("\r")) >= 0) {
        content = content.replace(i, 1, "");
    }
    while ((i = (int)content.find("\n")) >= 0) {
        content = content.replace(i, 1, "");
    }
    while ((i = (int)content.find(" ")) >= 0) {
        content = content.replace(i, 1, "");
    }
    if (content.length() > 0) {
        //return false;
    }
    //return true;
}

void CSegNode::to_string(string space)
{
    printf("%s", space.c_str());
    printf("<%s", get_name().c_str());
    map<string, string>::iterator it_bg = get_attribute_map_ref().begin();
    map<string, string>::iterator it_ed = get_attribute_map_ref().end();
    while (it_bg != it_ed)
    {
        printf(" %s=%s", (*it_bg).first.c_str(), (*it_bg).second.c_str());
        it_bg++;
    }
    printf(">\r\n");

    list<CLineNode*>::iterator ln_bg = get_line_node_list().begin();
    list<CLineNode*>::iterator ln_ed = get_line_node_list().end();
    for (; ln_bg != ln_ed; ln_bg++)
    {
        (*ln_bg)->to_string(space + "    ");
    }

    list<CSegNode*>::iterator sn_bg = get_seg_node_list().begin();
    list<CSegNode*>::iterator sn_ed = get_seg_node_list().end();
    for (; sn_bg != sn_ed; sn_bg++)
    {
        (*sn_bg)->to_string(space + "    ");
    }
    printf("%s</%s>\r\n", space.c_str(), get_name().c_str());
}
