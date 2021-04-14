#include "map.h"

map::map()
{
}

map::map(int id)
{
    this->m_id=id;
    switch(id)
    {
    case 1:
    {
        this->m_img=":/image/map1.png";
        this->m_mes="这是一片尚未开发的古老森林，附件的城镇却在森林外围接连出现人员失踪，森林深处究竟隐藏着什么秘密，等待着调查";
        break;
    }
    default:
    {
        this->m_img=":/image/unknownmap.png";
        this->m_mes="未知";
        break;
    }
    }
}
