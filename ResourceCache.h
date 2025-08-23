#pragma once
#include "Types.h"
#include "StringId.h"
#include "StringIdTable.h"
#include "Resource.h"

namespace Resources
{
	template <typename T>
	class ResourceCache
	{
	public:
		ResourceCache<T>(u32 capacity)
			: cache_(Common::StringIdTable<T>(capacity))
		{
			static_assert(std::is_base_of<Resource, T>::value);
		}

		const T& get(StringId resourceId) const
		{
			return *this->cache_.get(resourceId);
		}

		void add(StringId resourceId, T resource)
		{
			cache_.add(resourceId, std::move(resource));
		}

		void remove(StringId resourceId)
		{
			cache_.remove(resourceId);
		}
	
	private:
		Common::StringIdTable<T> cache_;
	};
}