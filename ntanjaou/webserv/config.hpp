#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <iostream>

#define  str std::string

typedef struct s_location
{
    str autoindex;
    str index;
    str allow_methods;
    str fast_cgi_pass;
} t_location;


class ConfigFile{
public:
    str Listen;
    str host;
    str server_name;
    int max_body_size;
    str root;
    t_location location;
    ConfigFile();
    void Set_Cfile(str l, str h, str sn, int mbs, str r, t_location loc);
};

std::ostream & operator<< (std::ostream &out, ConfigFile const &cf);

#endif