#pragma once

#include <map>
#include <memory>
#include <cassert>
#include <iostream>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
    std::map<Identifier, std::unique_ptr<Resource>> resources;
public:
    void load(Identifier id, const std::string& filename)
    {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename))
            std::cerr << "Error loading resource!\n";

        auto inserted = resources.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second);
    }

    Resource& get(Identifier id)
    {
        auto found = resources.find(id);
        assert(found != resources.end());

        return *found->second;
    }

    const Resource& get(Identifier id) const
    {
        auto found = resources.find(id);
        assert(found != resources.end());

        return *found->second;
    }

    const bool isLoaded(Identifier id) const
    {
        auto found = resources.find(id);
        if (found != resources.end())
            return true;
        return false;
    }
};

