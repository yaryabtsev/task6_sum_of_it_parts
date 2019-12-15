#include <iostream>

using namespace std;

#include "parts.h"

void Part::describe(void)
{
    if (!dict.empty())
    {
        cout << name << " include :";

        for (map<Part *, int>::iterator it = dict.begin();
             it != dict.end(); cout << (((++it) == dict.end()) ? ' ' : ','))
            cout << ' ' << it->second << ' ' << it->first->name << ((it->second > 1) ? "(s)" : "");
    }
    else
        cout << name << "is empty";
    cout << '\n';
}

int Part::count_howmany(Part const* p)
{
    if (name == p->name)
        return 1;
    int count = 0;
    for (map<Part*, int>::iterator it = dict.begin(); it != dict.end(); ++it)
        count += it->first->count_howmany(p) * it->second;
    return count;
}

void Part::add(pair<Part*, int> const p)
{
    dict.insert(p);
}

Part* NameContainer::lookup(string const& name)
{
    if (name_map.find(name) == name_map.end())
        name_map.insert(pair<string, Part*>(name, new Part(name)));
    return name_map[name];
}

NameContainer::~NameContainer(void) = default;

void add_part(string const &x, int q, string const &y)
{
    partContainer.lookup(x)->add(pair<Part*, int>(partContainer.lookup(y), q));
}

NameContainer partContainer;

